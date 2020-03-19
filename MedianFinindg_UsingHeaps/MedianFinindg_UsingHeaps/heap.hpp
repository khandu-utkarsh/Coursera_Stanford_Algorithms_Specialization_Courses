//
//  heap.hpp
//  MedianFinding_UsingHeaps
//
//  Created by Utkarsh Khandelwal on 14/03/20.
//  Copyright © 2020 Utk_Sort. All rights reserved.
//

#ifndef heap_hpp
#define heap_hpp

#include <stdio.h>
#include <vector>

template<typename T>
class heap
{
public:
    heap(size_t maxLimit, bool type);
    ~heap();
    
    T * GetRoot();
    void InsertElement(const T &key);
    T PopElement();
private:
    void BubbleUp(const T &key);
    void BubbleDown(const T &key);
    bool Compare(const T &parent, const T &child);
    void Swap(const size_t & parentIndex, const size_t & child1Index, const size_t &child2Index);
    void Swap(const size_t & parentIndex, const size_t & keyIndex);

private:
    size_t p_dataCount;
    T * p_data;
    bool p_heapType;        //true for min heap, false for max heap
};


template<typename T>
class MedianFinder
{
public:
    MedianFinder(size_t &elementsCount);
    ~MedianFinder();
    void InsertElement(T &data);
    T GetMedian();

private:
    heap<T> * p_maxHeap;
    heap<T> * p_minHeap;
    std::vector<T> p_median;
    size_t p_maxHeapElemCount;
    size_t p_minHeapElemCount;
};
#endif /* heap_hpp */
