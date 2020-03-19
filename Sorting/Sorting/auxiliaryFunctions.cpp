//
//  auxiliaryFunctions.cpp
//  Sorting
//
//  Created by Utkarsh Khandelwal on 07/01/20.
//  Copyright © 2020 Utk_Sort. All rights reserved.
//
#include "auxiliaryFunctions.hpp"
#include<sstream>
#include<iostream>
#include<fstream>
using namespace std;
bool Helpers::ParseStringFromConsolesIntoAndIntegerArray(std::string &input, std::vector<int> &output)
{
    std::stringstream stream(input);
    int number;
    while(stream >> number)
    {
        output.push_back(number);
    }
    return true;
}

bool Helpers::ParseDataFromFile(std::string filePath, std::vector<int> &inputData)
{
    std::ifstream ifs(filePath);
    assert(ifs);
    if(ifs.good() && ifs.is_open())
    {
        string line;
        while(std::getline(ifs, line))
        {
            ParseStringFromConsolesIntoAndIntegerArray(line, inputData);
        }
    }
    return true;
}

bool Helpers::PrintDataOnConsole(std::vector<int> &outputData)
{
    std::cout << std::endl  <<" Values are:" << std::endl;
    for(auto & currNumber : outputData)
    {
        std::cout << currNumber << ' ';
    }
    std::cout << std::endl;
    return true;
}

