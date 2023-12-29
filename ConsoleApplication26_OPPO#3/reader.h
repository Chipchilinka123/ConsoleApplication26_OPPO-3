#pragma once
#ifndef DATA_H
#define DATA_H

#include <vector>
#include <fstream>
#include "FoodInfo.h"

// Объявление функций
void readFoodInfo(std::istream& inputFile, std::vector<FoodInfo>& foodList);
void displayFoodInfo(const std::vector<FoodInfo>& foodList, std::ostream& out);

#endif // DATA_H