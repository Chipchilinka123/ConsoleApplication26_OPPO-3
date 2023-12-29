#include "pch.h"
#include "FoodInfo.h"
#include "Date.h"
#include <iostream>

// Обновить определение функции, убрав static

void FoodInfo::printFoodInfo(std::ostream& out) const {
    out << "Date: ";
    date.print(out);
    out << ", Food number: " << foodNumber << std::endl;
}
FoodInfo FoodInfo::readFoodInfoFromFile(std::istream& inputFile) {
    FoodInfo food;

    food.date = Date::create_from_stream(inputFile);
    inputFile >> food.foodNumber;

    if (!food.isValid()) {
        throw std::runtime_error("Неверные данные FoodInfo в файле.");
    }

    return food;
}

// Исправить номер машины на название фруктов
bool FoodInfo::isValidFoodNumber(const std::string& number) {
    if (number.length() != 6) {
        return false;
    }

    // Первый символ - буква
    if (!std::isalpha(number[0])) {
        return false;
    }

    // Следующие 3 символа - числа
    for (int i = 1; i <= 3; i++) {
        if (!std::isdigit(number[i])) {
            return false;
        }
    }

    // Последние 2 символа - буквы
    if (!std::isalpha(number[4]) || !std::isalpha(number[5])) {
        return false;
    }

    return true;
}

bool FoodInfo::isValid() const
{
    return date.isValid() && isValidFoodNumber(foodNumber);
}