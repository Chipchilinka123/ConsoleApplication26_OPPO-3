#include "pch.h"
#include "reader.h"
#include <iostream>

// stringstream


void readFoodInfo(std::istream& inputFile,  std::vector<FoodInfo>& foodList) {
    while (!inputFile.eof()) {
        FoodInfo food = FoodInfo::readFoodInfoFromFile(inputFile);
        foodList.push_back(food);
    }
}

void displayFoodInfo(const std::vector<FoodInfo>& foodList, std::ostream& out) {
    for (const FoodInfo& food : foodList) {
        food.printFoodInfo(out);
    }
}