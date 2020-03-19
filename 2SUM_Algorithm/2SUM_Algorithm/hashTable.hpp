//
//  hashTable.hpp
//  2SUM_Algorithm
//
//  Created by Utkarsh Khandelwal on 18/03/20.
//  Copyright © 2020 Utk_Sort. All rights reserved.
//

#ifndef hashTable_hpp
#define hashTable_hpp

#include <stdio.h>

using integer = long long int;
using uinteger = unsigned long long int;

struct Value
{
    //Data Members
    integer * m_data = nullptr;
    Value * next = nullptr;
};


class HashTable
{
public:
    HashTable(uinteger & inputSize);
    ~HashTable();
    
    //Returns true if inserted, else returns false if already present
    bool Insert(integer &data);
    
    //Returns true if key already present, else returns false;
    integer * IsDataPresent(integer &data);

private:
    uinteger GetHash(integer &data);
    
    Value * p_arrayBuckets;
    uinteger p_bucketsCount;
};

#endif /* hashTable_hpp */
