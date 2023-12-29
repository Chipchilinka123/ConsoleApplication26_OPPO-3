#pragma once
#include "Date.h"

#include <fstream>
#include <string>

struct FoodInfo {
    Date date;
    std::string foodNumber;

    bool isValid() const;
    static bool isValidFoodNumber(const std::string& number);

    static FoodInfo readFoodInfoFromFile(std::istream& inputFile);
    void printFoodInfo(std::ostream& out) const;
};