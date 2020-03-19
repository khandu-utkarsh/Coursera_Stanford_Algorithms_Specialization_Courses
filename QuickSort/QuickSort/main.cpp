//
//  main.cpp
//  QuickSort
//
//  Created by Utkarsh Khandelwal on 15/02/20.
//  Copyright © 2020 Utk_Sort. All rights reserved.
//

#include <iostream>
#include <vector>
#include "quickSort.h"
using namespace std;
int main(int argc, const char * argv[]) {
    
    //vector<int> testVector {3, 5, 7, 9, -2, 56, 1};
    
    //vector<int> testVector {4, 5,2334, -234, 678, 2315, 0, 3421, 6457, 2983, 98, 912};
    vector<int> testVector;
    string inputFileName("/Users/utkarsh/Downloads/_32387ba40b36359a38625cbb397eee65_QuickSort.txt");
    
    int dataCountRead = IO_Interface::ReadInputFromFile(inputFileName.c_str(), testVector);
    //PIVOT_CHOICE_METHOD choice = PIVOT_CHOICE_METHOD::FIRST_METHOD;
    //PIVOT_CHOICE_METHOD choice = PIVOT_CHOICE_METHOD::END_METHOD;
    PIVOT_CHOICE_METHOD choice = PIVOT_CHOICE_METHOD::MEDIAN_METHOD;
    Sort sortingObj(testVector, choice);
    sortingObj.SortInput(0, static_cast<unsigned int>(testVector.size()) - 1);

    //Print result to console;
    //IO_Interface::PrintOnConsole(testVector);
    IO_Interface::PrintComparisonsMadeCount(sortingObj.GetComparisonsMade());
    return 0;
}
