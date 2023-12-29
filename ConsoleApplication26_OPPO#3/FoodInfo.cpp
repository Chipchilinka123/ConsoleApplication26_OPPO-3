#include "pch.h"
#include "FoodInfo.h"
#include "Date.h"
#include <iostream>

// �������� ����������� �������, ����� static

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
        throw std::runtime_error("�������� ������ FoodInfo � �����.");
    }

    return food;
}

// ��������� ����� ������ �� �������� �������
bool FoodInfo::isValidFoodNumber(const std::string& number) {
    if (number.length() != 6) {
        return false;
    }

    // ������ ������ - �����
    if (!std::isalpha(number[0])) {
        return false;
    }

    // ��������� 3 ������� - �����
    for (int i = 1; i <= 3; i++) {
        if (!std::isdigit(number[i])) {
            return false;
        }
    }

    // ��������� 2 ������� - �����
    if (!std::isalpha(number[4]) || !std::isalpha(number[5])) {
        return false;
    }

    return true;
}

bool FoodInfo::isValid() const
{
    return date.isValid() && isValidFoodNumber(foodNumber);
}