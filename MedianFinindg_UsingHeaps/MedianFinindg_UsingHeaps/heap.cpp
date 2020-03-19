//
//  heap.cpp
//  MedianFinding_UsingHeaps
//
//  Created by Utkarsh Khandelwal on 14/03/20.
//  Copyright © 2020 Utk_Sort. All rights reserved.
//

#include "heap.hpp"
#include <string>
#include <iostream>
#include <fstream>

template<typename T>
heap<T>::heap(size_t maxLimit, bool type)
{
    p_data = new T[maxLimit + 1];
    p_data[0] = 0;
    p_dataCount = 0;
    p_heapType = type;
}

template<typename T>
heap<T>::~heap()
{
    delete[] p_data;
    p_data = nullptr;
}

template<typename T>
T * heap<T>::GetRoot()
{
    if(p_dataCount >= 1)
        return &p_data[1];
    else
        return nullptr;
}

template<typename T>
void heap<T>::InsertElement(const T &key)
{
    p_data[p_dataCount + 1] = key;
    p_dataCount++;
    BubbleUp(key);
}

template<typename T>
T heap<T>::PopElement()
{
    T * root = GetRoot();
    T retValue = *root;
    
    T lastElement = p_data[p_dataCount];
    p_data[1] = lastElement;
    p_dataCount--;

    BubbleDown(p_data[1]);
    return retValue;
}

template<typename T>
void heap<T>::BubbleUp(const T &key)
{
    size_t keyIndex = p_dataCount;
    size_t parentIndex = keyIndex/2;
    if(parentIndex == 0)
    {
        return;
    }
    
    bool comparedValue = Compare(p_data[parentIndex], p_data[keyIndex]);
    if(comparedValue)
        return;
    while (!comparedValue)
    {
        Swap(parentIndex, keyIndex);
        keyIndex = parentIndex;
        parentIndex = keyIndex/2;
        if(parentIndex <= 0)
        {
            break;
        }
        comparedValue = Compare(p_data[parentIndex], p_data[keyIndex]);
    }
}

template<typename T>
void heap<T>::BubbleDown(const T &key)
{
    size_t index = 1;
    size_t child1Index = index * 2;
    size_t child2Index = index * 2 + 1;

    bool child1In = p_dataCount >= child1Index;
    bool child2In = p_dataCount >= child2Index;

    //Checking if we require to swap
    bool loopAgain = false;
     if(child2In)
     {
         bool child1Compared = Compare(p_data[index], p_data[child1Index]);
         bool child2Compared = Compare(p_data[index], p_data[child2Index]);
         loopAgain = child1Compared == false || child2Compared == false;
     }
     else if(!child2In && child1In)
     {
         bool child1Compared = Compare(p_data[index], p_data[child1Index]);
         loopAgain = child1Compared == false;
     }
    while(loopAgain)
    {
        if(child2In)
        {
            //This automatically means child1 is in
            if(p_heapType)
            {
                if(p_data[child1Index] < p_data[child2Index])
                {
                    Swap(index, child1Index);
                    index = child1Index;
                }
                else
                {
                    Swap(index, child2Index);
                    index = child2Index;
                }
            }
            else
            {
                if(p_data[child1Index] > p_data[child2Index])
                {
                    Swap(index, child1Index);
                    index = child1Index;
                }
                else
                {
                    Swap(index, child2Index);
                    index = child2Index;
                }
            }
        }
        else if(!child2In && child1In)
        {
            Swap(index, child1Index);
            index = child1Index;
        }
        else if(!child1In && !child2In)
        {
            //None of the child exists
        }
        child1Index = index * 2;
        child2Index = index * 2 + 1;
        child1In = p_dataCount >= child1Index;
        child2In = p_dataCount >= child2Index;
        //Checking if we require to swap
         if(child2In)
         {
             bool child1Compared = Compare(p_data[index], p_data[child1Index]);
             bool child2Compared = Compare(p_data[index], p_data[child2Index]);
             loopAgain = child1Compared == false || child2Compared == false;
         }
         else if(!child2In && child1In)
         {
             bool child1Compared = Compare(p_data[index], p_data[child1Index]);
             loopAgain = child1Compared == false;
         }
         else
         {
            //No child exists,
            loopAgain = false;
         }
    }
}

template<typename T>
bool heap<T>::Compare(const T &parent, const T &child)
{
    if(p_heapType) //True min heap
    {
        if(parent < child)
            return true;
        else
            return false;
    }
    else
    {
        if(parent > child)
            return true;
        else
            return false;
    }
}

template<typename T>
void heap<T>::Swap(const size_t & parentIndex, const size_t & keyIndex)
{
    T temp = p_data[keyIndex];
    p_data[keyIndex] = p_data[parentIndex];
    p_data[parentIndex] = temp;
}

template<typename T>
MedianFinder<T>::MedianFinder(size_t &elementsCount) :
        p_maxHeapElemCount(0),
        p_minHeapElemCount(0)
{
    
    p_maxHeap = new heap<T>(elementsCount, false);
    p_minHeap = new heap<T>(elementsCount, true);
}

template<typename T>
void MedianFinder<T>::InsertElement(T &data)
{
    if(p_maxHeapElemCount == 0)
    {
        p_maxHeap->InsertElement(data);
        p_maxHeapElemCount++;
        return;
    }
    
    //Checking where to put it
    T * maxRoot = p_maxHeap->GetRoot();
    if(data > *maxRoot)
    {
        p_minHeap->InsertElement(data);
        p_minHeapElemCount++;

    }
    else
    {
        p_maxHeap->InsertElement(data);
        p_maxHeapElemCount++;
    }
    
    //Now we will have to make tree sizes equal
    if(p_maxHeapElemCount >= p_minHeapElemCount)
    {
        size_t diff = p_maxHeapElemCount - p_minHeapElemCount;
        while(diff > 1)
        {
            //We need to rearrange it, otherwise
            T maxHeapRoot = p_maxHeap->PopElement();
            p_maxHeapElemCount--;
            p_minHeap->InsertElement(maxHeapRoot);
            p_minHeapElemCount++;
            diff = p_maxHeapElemCount - p_minHeapElemCount;
        }
    }
    else
    {
        size_t diff = p_minHeapElemCount - p_maxHeapElemCount;
        while(diff > 1)
        {
            //We need to rearrange it, otherwise
            T minHeapRoot = p_minHeap->PopElement();
            p_minHeapElemCount--;
            p_maxHeap->InsertElement(minHeapRoot);
            p_maxHeapElemCount++;
            diff = p_minHeapElemCount - p_maxHeapElemCount;
        }
    }
}

template<typename T>
T MedianFinder<T>::GetMedian()
{
    T * maxRoot = p_maxHeap->GetRoot();
    T * minRoot = p_minHeap->GetRoot();
    if(maxRoot == nullptr || minRoot == nullptr)
    {
        if(maxRoot)
            return *maxRoot;
        else
            return *minRoot;
    }
    size_t totalElements = p_maxHeapElemCount + p_minHeapElemCount;
    size_t remainder = totalElements%2;
    size_t medianElement = 0;
    if(remainder == 0)
    {
        medianElement = totalElements/2;
    }
    else
    {
        medianElement = (totalElements + 1)/2;
    }
    
    if(p_maxHeapElemCount == medianElement)
        return * p_maxHeap->GetRoot();
    else
        return * p_minHeap->GetRoot();
}

template<typename T>
MedianFinder<T>::~MedianFinder()
{
    delete p_maxHeap;
    p_maxHeap = nullptr;
    delete p_minHeap;
    p_minHeap = nullptr;
}
