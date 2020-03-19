//
//  hashTable.cpp
//  2SUM_Algorithm
//
//  Created by Utkarsh Khandelwal on 18/03/20.
//  Copyright © 2020 Utk_Sort. All rights reserved.
//

#include "hashTable.hpp"
#include <vector>

HashTable::HashTable(uinteger & inputSize)
{
    p_bucketsCount = inputSize;
    p_arrayBuckets = new Value[p_bucketsCount];
}

HashTable::~HashTable()
{
    
    //First have to delete linked list
    for(uinteger iB = 0; iB < p_bucketsCount; ++iB)
    {
        Value bucket = p_arrayBuckets[iB];
        Value * currB = bucket.next;
        while(currB != nullptr)
        {
            bucket.next = currB->next;
            delete currB;
            currB = bucket.next;
        }
    }
    //Than delete array
    delete [] p_arrayBuckets;
    p_arrayBuckets = nullptr;
}

bool HashTable::Insert(integer &data)
{
    uinteger index = GetHash(data);
    Value &bucket = p_arrayBuckets[index];
    if(bucket.m_data == nullptr)
    {
        bucket.m_data = &data;
        bucket.next = nullptr;
    }
    else
    {
        if(*bucket.m_data == data)
        {
            //Already there
            return false;
        }
        Value * nextBucket = bucket.next;
        while (nextBucket != nullptr)
        {
            if(*nextBucket->m_data == data)
            {
                //Already there
                return false;
            }
            nextBucket = nextBucket->next;
        }
        nextBucket = new Value;
        nextBucket->m_data = &data;
        nextBucket->next = nullptr;
    }
    return true;
}


integer * HashTable::IsDataPresent(integer &data)
{
    uinteger index = GetHash(data);
    Value bucket = p_arrayBuckets[index];
    if(bucket.m_data == nullptr)
    {
        return nullptr;
    }
    else
    {
        if(*bucket.m_data == data)
        {
            return bucket.m_data;
        }
        else
        {
            Value * nextBucket = bucket.next;
            while (nextBucket != nullptr)
            {
                if(*nextBucket->m_data == data)
                {
                    return nextBucket->m_data;
                }
                nextBucket = nextBucket->next;
            }
        }
    }
    return nullptr;
}

uinteger HashTable::GetHash(integer &data)
{
     uinteger reqPrime = 1000159;
     if(data < 0)
     {
         integer localData = -1 * data;
         return (localData%reqPrime);
     }
    else
    {   
        return data%reqPrime;
    }
}
