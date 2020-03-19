//
//  quickSort.cpp
//  QuickSort
//
//  Created by Utkarsh Khandelwal on 15/02/20.
//  Copyright © 2020 Utk_Sort. All rights reserved.
//
#include"quickSort.h"
#include<assert.h>
#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <string>
#include <fstream>
Sort::Sort(vector<int> &inputVector, PIVOT_CHOICE_METHOD choice) : m_vectorToSort(inputVector)
{
    m_totalComparisons = 0;
    m_choice = choice;
}
    
//Sort::Sort(const Sort &sortObj) : m_vectorToSort(sortObj.m_vectorToSort)
//{
//    m_totalComparisons = sortObj.m_totalComparisons;
//}

unsigned int Sort::ChoosePivot(unsigned int startIndex, unsigned int endIndex)
{
    if(m_choice == PIVOT_CHOICE_METHOD::FIRST_METHOD)
    {
        return startIndex;
    }
    else if(m_choice == PIVOT_CHOICE_METHOD::END_METHOD)
    {
        return endIndex;
    }
    else if(m_choice == PIVOT_CHOICE_METHOD::MEDIAN_METHOD)
    {
        unsigned int middleIndex = static_cast<unsigned int>((startIndex + endIndex)/2);
        int &midValue = m_vectorToSort[middleIndex];
        int &startValue = m_vectorToSort[startIndex];
        int &endValue = m_vectorToSort[endIndex];
        std::vector<int> tempVector {midValue, startValue, endValue};
        std::sort(tempVector.begin(), tempVector.end());
        int sortedMidVlaue = tempVector[1];
        if(midValue == sortedMidVlaue)
        {
            return middleIndex;
        }
        else if(startValue == sortedMidVlaue)
        {
            return startIndex;
        }
        else
        {
            return endIndex;
        }
    }
    else
    {
        //If method not provided, choose startIndex by default
        return startIndex;
    }

}

void Sort::SwapElements(unsigned int to, unsigned int from)
{
    int toOriginalValue = m_vectorToSort[to];
    m_vectorToSort[to] = m_vectorToSort[from];
    m_vectorToSort[from] = toOriginalValue;
}

int Sort::CompareValuesAtIndices(unsigned int first, unsigned second)
{
    if(m_vectorToSort[first] > m_vectorToSort[second])
        return 1;
    else if(m_vectorToSort[second] > m_vectorToSort[first])
    {
        return -1;
    }
    else
    {
        assert(0);
        return 0;
    }
}

bool Sort::CreatePartition(unsigned int inputStartIndex,
                         unsigned int inputEndIndex,
                         unsigned int &pivotIndex,
                         unsigned int &lessStartIndex,
                         unsigned int &lessEndIndex,
                         unsigned int &moreStartIndex,
                         unsigned int &moreEndIndex)
{
    if(pivotIndex != inputStartIndex)
        SwapElements(inputStartIndex, pivotIndex);
    
    int partitionIndex = inputStartIndex + 1;
    for(int iIndex = inputStartIndex + 1; iIndex <= inputEndIndex; ++iIndex)
    {
        int compRetValue = CompareValuesAtIndices(inputStartIndex, iIndex);
        if(compRetValue > 0)
        {
            SwapElements(partitionIndex, iIndex);
            partitionIndex++;
        }
        else if(compRetValue < 0)
        {

        }
        else
        {
            assert(0);
            return false;
        }
    }
    int indexToSwipe = partitionIndex - 1;
    SwapElements(inputStartIndex, indexToSwipe);

    lessStartIndex = inputStartIndex;
    lessEndIndex = indexToSwipe - 1; //Because pivot elem has found it's position
    moreStartIndex = partitionIndex;
    moreEndIndex = inputEndIndex;
    return  true;
}

bool Sort::SortInput(unsigned int inputStartIndex, unsigned int inputEndIndex)
{
    unsigned long long  currComparisons = inputEndIndex - inputStartIndex + 1 - 1;
    m_totalComparisons +=currComparisons;
    unsigned int pivotIndex = ChoosePivot(inputStartIndex, inputEndIndex);

    unsigned int lessStartIndex, lessEndIndex, moreStartIndex, moreEndIndex;

    bool partitionDone = CreatePartition(inputStartIndex, inputEndIndex, pivotIndex,
                            lessStartIndex,lessEndIndex,moreStartIndex,moreEndIndex);
    if(!partitionDone)
        return false;
    unsigned int sizeOfFirstArray = lessEndIndex - lessStartIndex + 1;
    unsigned int sizeOfSecondArray = moreEndIndex - moreStartIndex + 1;
    if(sizeOfFirstArray > 1)
    {
        SortInput(lessStartIndex, lessEndIndex);
    }
    
    if(sizeOfSecondArray > 1)
    {
        SortInput(moreStartIndex, moreEndIndex);
    }
    return true;
}


unsigned long long Sort::GetComparisonsMade()
{
    return m_totalComparisons;
}

int IO_Interface::ReadInputFromFile(const char * filePath, std::vector<int> &readInput)
{
    readInput.clear();
    int totalValuesRead = 0;
    ifstream input(filePath);
    if(input.is_open())
    {
        string currValue;
        while(std::getline(input, currValue))
        {
            int currData = atoi(currValue.c_str());
            readInput.push_back(currData);
            totalValuesRead++;
        }
    }
    return totalValuesRead;
}

void IO_Interface::ReadFromConsole(std::vector<int> &readInput)
{
    //Reading input from console
    int value = 0;
    while (cin >> value)
    {
        readInput.push_back(value);
    }
}

void IO_Interface::PrintOnConsole(std::vector<int> &inputVector)
{
    cout << "Sorted Vector:     " << std::endl;
    for(auto &currValue : inputVector)
    {
        cout << currValue << " ";
    }
    cout << std::endl;
}

void IO_Interface::PrintComparisonsMadeCount(unsigned long long comparisonsMade)
{
    cout << "Total Comparisons Made Are: " << comparisonsMade << std::endl;
}
