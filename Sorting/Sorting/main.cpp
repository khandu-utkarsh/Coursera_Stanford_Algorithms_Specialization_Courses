//
//  main.cpp
//  Sorting_Algorithms_Learning
//
//  Created by Utkarsh Khandelwal on 04/01/20.
//  Copyright © 2020 Utkarsh_DS_Algo. All rights reserved.
//

#include <iostream>
#include<vector>
#include<string>
#include<sstream>
#include "insertSort.hpp"
#include"auxiliaryFunctions.hpp"
using std::cout;
using std::cin;
int main(int argc, const char * argv[])
{
    cout << "Enter numbers you want to sort: " << std::endl;
    std::string inputString;
    //std::getline(cin, inputString);
    std::vector<int> inputData;
    //std::string filePath = " /Users/utkarsh/Library/Developer/Xcode/DerivedData/Sorting-bqujqonjxmfjqjdmfgwlpjqwpwbm/Build/Products/Debug/inputData.txt";
    std::string filePath = "inputData.txt";
    bool parsingSuccess = Helpers::ParseDataFromFile(filePath, inputData);
    //bool parsingSuccess = Helpers::ParseStringFromConsolesIntoAndIntegerArray(inputString, inputData);
    if(parsingSuccess)
    {
        InsertionSort insertSort(inputData);
        std::vector<int> sortedArray = insertSort.SortArray();
        if(sortedArray.size())
        {
            Helpers::PrintDataOnConsole(sortedArray);
        }
    }
    return 0;
}

