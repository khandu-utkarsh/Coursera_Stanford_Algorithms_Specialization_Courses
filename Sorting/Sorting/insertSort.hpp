//
//  insertSort.hpp
//  Sorting
//
//  Created by Utkarsh Khandelwal on 04/01/20.
//  Copyright © 2020 Utk_Sort. All rights reserved.
//

#ifndef insertSort_hpp
#define insertSort_hpp
#include<vector>
#include <stdio.h>
class InsertionSort
{
    //Data Variables
    private:
        std::vector<int> & data;
    
    //Constructors
    public:
        InsertionSort(std::vector<int> &inputValues);
    
    private:
        InsertionSort(const InsertionSort &obj);
        InsertionSort();
    
    //Destrcutors
    public:
        ~InsertionSort();
    
    //Methods
    public:
        std::vector<int> SortArray();
};


#endif /* insertSort_hpp */
