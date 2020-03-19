//
//  quickSort.h
//  QuickSort
//
//  Created by Utkarsh Khandelwal on 15/02/20.
//  Copyright © 2020 Utk_Sort. All rights reserved.
//

#ifndef quickSort_h
#define quickSort_h
#include<vector>
using namespace std;

enum PIVOT_CHOICE_METHOD
{
    FIRST_METHOD = 1,
    END_METHOD = 2,
    MEDIAN_METHOD = 3
};

class Sort
{

public:
    
    Sort() = delete;
    Sort(vector<int> &inputVector, PIVOT_CHOICE_METHOD choice);
    Sort(const Sort &sortObj) = delete;
    unsigned int ChoosePivot(unsigned int startIndex, unsigned int endIndex);
    void SwapElements(unsigned int to, unsigned int from);
    
    //Returns 1 if firstValue is greater than secondValue
    //else returns -1 (when secondValue greater than firstValue)
    // if equal return 0
    int CompareValuesAtIndices(unsigned int first, unsigned second);
    
    bool CreatePartition(unsigned int inputStartIndex,
                         unsigned int inputEndIndex,
                         unsigned int &pivotIndex,
                         unsigned int &lessStartIndex,
                         unsigned int &lessEndIndex,
                         unsigned int &moreStartIndex,
                         unsigned int &moreEndIndex);

    bool SortInput(unsigned int inputStartIndex, unsigned int inputEndIndex);
    unsigned long long GetComparisonsMade();
private:
    vector<int> &m_vectorToSort;
    unsigned long long m_totalComparisons;
    PIVOT_CHOICE_METHOD m_choice;
    
};


class IO_Interface
{
public:
    static int ReadInputFromFile(const char * filePath, std::vector<int> &readInput);
    
    static void ReadFromConsole(std::vector<int> &readInput);
    static void PrintOnConsole(std::vector<int> &inputVector);
    static void PrintComparisonsMadeCount(unsigned long long comparisonsMade);
};

#endif /* quickSort_h */
