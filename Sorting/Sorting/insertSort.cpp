//
//  insertSort.cpp
//  Sorting
//
//  Created by Utkarsh Khandelwal on 04/01/20.
//  Copyright © 2020 Utk_Sort. All rights reserved.
//
#include <iostream>
#include <vector>
#include "insertSort.hpp"
InsertionSort::InsertionSort(std::vector<int> &inputValues) :
                        data(inputValues)
{
    //std::cout << "Insertion Object Created, i.e. Constructor Called \n";
    //std::cout << "Size of Input Data " << data.size() << std::endl;
    for(auto &number : data)
    {
        std::cout << number << " ";
    }
    //std::cout << "At the end of constructor\n";
}

InsertionSort::~InsertionSort()
{
    //std::cout << "\nInsertion Object Deleted, i.e. Destructor Called\n";
}

std::vector<int> InsertionSort::SortArray()
{
    for(unsigned int index = 1; index < data.size(); ++index)
    {
        unsigned int currIndex = index;
        int currValue = data[index];
        while(currIndex >= 0)
        {
            if(currIndex >= 1)
            {
                if(data[currIndex- 1] > currValue)
                {
                    data[currIndex] = data[currIndex - 1];
                    currIndex--;
                }
                else
                {
                    data[currIndex] = currValue;d                    break;
                }
            }
            else
            {
                data[currIndex] = currValue;
                break;
            }
        }
    }
    return data;
}


