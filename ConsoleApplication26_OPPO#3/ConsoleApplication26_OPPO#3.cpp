#include <locale>
#include "reader.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "FoodInfo.h"  

using namespace std;

int main() {
    setlocale(0, "");
    std::vector<FoodInfo> foodList;

    std::ifstream inputFile("vkusnyashka.txt");
    if (!inputFile.is_open()) {
        std::cerr << "Ошибка открытия файла." << std::endl;
        exit(1);
    }
    
    try {
        readFoodInfo(inputFile, foodList);
    }
    catch (const std::exception& e) {
        std::cerr << "Ошибка при чтении FoodInfo из файла: " << e.what() << std::endl;
        // Перехват исключения или обработка по необходимости
    }

    displayFoodInfo(foodList, std::cout);
    return 0;
}