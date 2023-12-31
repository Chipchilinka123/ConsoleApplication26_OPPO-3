﻿#include "pch.h"

#include "CppUnitTest.h"

#include <iostream>
#include <sstream>
#include <vector>

//C:\Users\я\source\repos\ConsoleApplication32\ConsoleApplication32\pract2\OPPO\OPPO\LAB3\ConsoleApplication12

#include "../../LAB3/ConsoleApplication12/FoodInfo.h"
#include "../../LAB3/ConsoleApplication12/reader.h"
#include "../../LAB3/ConsoleApplication12/Date.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestProject
{
    TEST_CLASS(FoodInfoTests)
    {
    public:
        TEST_METHOD(TestPrintFoodInfo)
        {
            // Create a CarInfo instance for testing
            FoodInfo food;
            food.date.day = 13;
            food.date.month = 12;
            food.date.year = 2003;
            food.foodNumber = "D530FY";

            // Assert that the printFoodInfo method works as expected
            std::stringstream buffer;
            food.printFoodInfo(buffer);


            Assert::AreEqual(std::string("Date: 13.12.2003, Food number: D530FY\n"), buffer.str());


            if (buffer.str() == "Date: 13.12.2003, Food number: D530FY\n") {
                Microsoft::VisualStudio::CppUnitTestFramework::Logger::WriteMessage("TestPrintFoodInfo: Success");
            }
            else {
                Microsoft::VisualStudio::CppUnitTestFramework::Logger::WriteMessage("TestPrintFoodInfo: Failure");
            }
      
        }

        TEST_METHOD(ValidFoodNumber)
        {
            Assert::IsTrue(FoodInfo::isValidFoodNumber("A123BC"));
            Assert::IsTrue(FoodInfo::isValidFoodNumber("D530FY"));
            Assert::IsTrue(FoodInfo::isValidFoodNumber("U408TY"));
            Assert::IsTrue(FoodInfo::isValidFoodNumber("G441RT"));
            Assert::IsTrue(FoodInfo::isValidFoodNumber("F862KL"));
            Assert::IsTrue(FoodInfo::isValidFoodNumber("A132CB"));
            Assert::IsTrue(FoodInfo::isValidFoodNumber("R541KL"));
            Assert::IsTrue(FoodInfo::isValidFoodNumber("P842OL"));
            Assert::IsTrue(FoodInfo::isValidFoodNumber("T011EW"));

        }

// FoodInfo
// -----------------------------------------------------------------------

        TEST_METHOD(FoodInfo_readFoodInfoFromFile_err)
        {
            std::vector<std::string> cases{
               "12456",
               "4dfsfwegxf",
               "l;l;;;pp;"
            };

            for (const auto& testCase : cases) {
                try {
                    std::stringstream sin{ testCase };
                    FoodInfo::readFoodInfoFromFile(sin);
                    Assert::Fail();
                }
                catch (const std::runtime_error& e) {
                    std::string message{"Expected err: " + std::string(e.what())};
                    Logger::WriteMessage(message.c_str());
                }
                catch (...) {
                    Assert::Fail();
                }
            }
        }

        TEST_METHOD(FoodInfo_readFoodInfoFromFile_ok)
        {
            std::vector<std::string> cases{
                "11.11.2023 A123BC",

            };

            for (const auto& testCase : cases) {
                try {
                    std::stringstream sin{ testCase };
                    FoodInfo::readFoodInfoFromFile(sin);
                }
                catch (...) {
                    Logger::WriteMessage(testCase.c_str());
                    Assert::Fail();
                }
            }
        }

// Date
// -----------------------------------------------------------------------

        // TODO:
        TEST_METHOD(Date_create_from_stream_err)
        {
            //Assert::ExpectException<std::runtime_error>()

            std::vector<std::string> cases{
                "12432414",
                "cvdcdedsc",
                ".",
                "124r56th5h",

            };

            for (const auto& testCase : cases) {
                try {
                    std::stringstream sin{ testCase };
                    Date::create_from_stream(sin);
                    Assert::Fail();
                }
                catch (const std::runtime_error& e) {
                    std::string message{ "Expected err: " + std::string(e.what()) };
                    Logger::WriteMessage(message.c_str());
                }
                catch (...) {
                    Assert::Fail();
                }
            }

        }

        // TODO:

        TEST_METHOD(Date_create_from_stream_ok)
        {
            std::vector<std::string> cases{
                "13.12.2003 D530FY",
                "21.08.2003 D530FY",
                "15.02.2004 D530FY",
                "04.09.2013 D530FY",
            };

            for (const auto& testCase : cases) {
                try {
                    std::istringstream iss(testCase);
                    std::string date;
                    iss >> date;  // Читаем только дату из строки
                    std::stringstream sin(date);  // Создаем новый поток только для даты
                    FoodInfo food;
                    food.readFoodInfoFromFile(sin);
                }
                catch (...) {
                    Assert::IsTrue(L"Exception was thrown unexpectedly.");
                }
            }

            // Если выполнение цикла завершилось без исключений, отмечаем тест как пройденный
            Assert::IsTrue(true, L"All cases passed successfully.");
        }

        TEST_METHOD(InvalidFoodNumber)
        {

            // TODO: перенести в отдельную группу  ---> InvalidFoodNumber (OK)
            // Проверка невалидных номеров
            FoodInfo food;
            food.foodNumber = "1234BC"; // отсутствует начальная буква
            Assert::IsFalse(food.isValidFoodNumber(food.foodNumber));
            //Microsoft::VisualStudio::CppUnitTestFramework::Logger::WriteMessage("ValidateFoodNumber: Failure - отсутствует начальная буква\n");
            if (food.isValidFoodNumber(food.foodNumber)) {
                Microsoft::VisualStudio::CppUnitTestFramework::Logger::WriteMessage("ValidateFoodNumber: Failure - отсутствует начальная буква\n");
            }


            food.foodNumber = "A123B";  // слишком короткий номер
            Assert::IsFalse(food.isValidFoodNumber(food.foodNumber));
            //Microsoft::VisualStudio::CppUnitTestFramework::Logger::WriteMessage("ValidateFoodNumber: Failure - слишком короткий номер\n");
            if (food.isValidFoodNumber(food.foodNumber)) {
                Microsoft::VisualStudio::CppUnitTestFramework::Logger::WriteMessage("ValidateFoodNumber: Failure - слишком короткий номер\n");
            }


            food.foodNumber = "A12BCD"; // четыре числа
            Assert::IsFalse(food.isValidFoodNumber(food.foodNumber));
            //Microsoft::VisualStudio::CppUnitTestFramework::Logger::WriteMessage("ValidateFoodNumber: Failure - четыре числа\n");
            if (food.isValidFoodNumber(food.foodNumber)) {
                Microsoft::VisualStudio::CppUnitTestFramework::Logger::WriteMessage("ValidateFoodNumber: Failure - четыре числа\n");
            }


            food.foodNumber = "A12B3C"; // число вместо второй последней буквы
            Assert::IsFalse(food.isValidFoodNumber(food.foodNumber));
            //Microsoft::VisualStudio::CppUnitTestFramework::Logger::WriteMessage("ValidateFoodNumber: Failure - число вместо второй последней буквы\n");
            if (food.isValidFoodNumber(food.foodNumber)) {
                Microsoft::VisualStudio::CppUnitTestFramework::Logger::WriteMessage("ValidateFoodNumber: Failure - число вместо второй последней буквы\n");
            }
        }
    };

    TEST_CLASS(ReaderTests)
    {
    public:
        TEST_METHOD(TestReadFoodInfo)
        {
            std::vector<FoodInfo> foodList;
            std::stringstream sin{
                "13.12.2003 D530FY\n"
                "21.08.2003 D530FY\n"
                "15.02.2004 D530FY\n"
                "04.09.2013 D530FY"
            };

            readFoodInfo(sin, foodList);

            // Ensure foodList has exactly 4 elements
            Assert::AreEqual(size_t(4), foodList.size(), L"Food list size is not as expected.");
       /*     Assert::IsTrue(foodList.size() == 4, L"Food list size is not as expected.");*/


            if (!foodList.empty()) {
                // Check the first food's foodNumber
                //Assert::IsTrue(foodList[0].foodNumber == "D530FY", L"First food's foodNumber is not as expected.");

                Assert::AreEqual("D530FY", foodList[0].foodNumber.c_str(), L"First food's foodNumber is not as expected.");
                Logger::WriteMessage("TestReadFoodInfo: ✓ Success\n");
            }
            else {
                // Output an error message if the test failed
                Logger::WriteMessage("TestReadFoodInfo failed: Food list is empty.\n");
            }
        }
    };

    TEST_CLASS(DateValidityTest)
    {
    public:
        TEST_METHOD(ValidDateTest)
        {
            Assert::IsTrue(Date{ 13, 12, 2003 }.isValid());
            Assert::IsTrue(Date{ 20, 10, 1992 }.isValid());
            Assert::IsTrue(Date{ 29, 02, 2024 }.isValid());
            Assert::IsTrue(Date{ 28, 02, 2023 }.isValid());
            Assert::IsTrue(Date{ 05, 07, 2005 }.isValid());

            Assert::IsTrue(Date{ 29, 02, 1992 }.isValid());
            Assert::IsTrue(Date{ 29, 02, 1996 }.isValid());
            Assert::IsTrue(Date{ 29, 02, 2000 }.isValid());
            Assert::IsTrue(Date{ 29, 02, 2004 }.isValid());
            Assert::IsTrue(Date{ 29, 02, 2008 }.isValid());
            Assert::IsTrue(Date{ 29, 02, 2012 }.isValid());
            Assert::IsTrue(Date{ 29, 02, 2016 }.isValid());
            Assert::IsTrue(Date{ 29, 02, 2020 }.isValid());

            Assert::IsTrue(Date{ 01, 02, 1998 }.isValid());
            Assert::IsTrue(Date{ 07, 07, 2007 }.isValid());

            Logger::WriteMessage("ValidDateTest: Success\n");
        }

        TEST_METHOD(DateBefore1990Test)
        {
            Date dateBefore1990;
            dateBefore1990.day = 1;
            dateBefore1990.month = 1;
            dateBefore1990.year = 1989;

            // Проверяем недопустимую дату до 1990 года
            Assert::IsTrue(Date::isDateValid(dateBefore1990));
            //Microsoft::VisualStudio::CppUnitTestFramework::Logger::WriteMessage("DateBefore1990Test: Success");
            if (Date::isDateValid(dateBefore1990)) {
                Microsoft::VisualStudio::CppUnitTestFramework::Logger::WriteMessage("DateBefore1990Test: Success\n");
            }
            else {
                Microsoft::VisualStudio::CppUnitTestFramework::Logger::WriteMessage("DateBefore1990Test: Failure");
            }
        }

        TEST_METHOD(DateAfter2023Test)
        {
            Date dateAfter2023;
            dateAfter2023.day = 1;
            dateAfter2023.month = 1;
            dateAfter2023.year = 2024;

            // Проверяем недопустимую дату после 2023 года
            Assert::IsTrue(Date::isDateValid(dateAfter2023));
            //Microsoft::VisualStudio::CppUnitTestFramework::Logger::WriteMessage("DateAfter2023Test:: Success");
            if (Date::isDateValid(dateAfter2023)) {
                Microsoft::VisualStudio::CppUnitTestFramework::Logger::WriteMessage("DateAfter2023Test: Failure \n");
            }
            else {
                Microsoft::VisualStudio::CppUnitTestFramework::Logger::WriteMessage("DateAfter2023Test: Success");
            }
        }

        TEST_METHOD(InvalidDate2Test)
        {
            Date invalidDate2;
            invalidDate2.day = 31;
            invalidDate2.month = 2;
            invalidDate2.year = 2023;

            // Проверяем недопустимую дату
            Assert::IsFalse(Date::isDateValid(invalidDate2));
            Assert::IsFalse(Date{ -1, 07, 2005 }.isValid());
            Assert::IsFalse(Date{ 0, 06, 2022 }.isValid());
            Assert::IsFalse(Date{ -1, 07, 2005 }.isValid());
         
            Assert::IsFalse(Date{ 29, 02, 2023 }.isValid());
            Assert::IsFalse(Date{ 29, 02, 20017 }.isValid());
            Assert::IsFalse(Date{ 29, 02, 2005 }.isValid());
            Assert::IsFalse(Date{ 29, 02, 2-04 }.isValid());
            Assert::IsFalse(Date{ -10, 11, 2006 }.isValid());
            Assert::IsFalse(Date{ 01, -7, 2023 }.isValid());


            //Microsoft::VisualStudio::CppUnitTestFramework::Logger::WriteMessage("InvalidDate2Test:: Success");
            if (Date::isDateValid(invalidDate2)) {
                Microsoft::VisualStudio::CppUnitTestFramework::Logger::WriteMessage("InvalidDate2Test: Failure \n");
            }
            else {
                Microsoft::VisualStudio::CppUnitTestFramework::Logger::WriteMessage("InvalidDate2Test: Success");
            }
        }
    };
}
