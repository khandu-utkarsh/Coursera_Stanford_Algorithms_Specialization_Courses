//
//  main.cpp
//  2SUM_Algorithm
//
//  Created by Utkarsh Khandelwal on 18/03/20.
//  Copyright © 2020 Utk_Sort. All rights reserved.
//

#include "hashTable.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <set>
#include <unordered_set>
#include <chrono>

uinteger Interface(std::set<integer> &posNumSet, std::set<integer> &negNumSet)
{
    std::ifstream input("/Users/utkarsh/Downloads/_6ec67df2804ff4b58ab21c12edcb21f8_algo1-programming_prob-2sum.txt");
    std::string line;
    uinteger linesRead = 0;
    while(std::getline(input, line))
    {
        integer data = std::stoll(line);
        if(data >= 0)
        {
            posNumSet.insert(data);
        }
        else
        {
            negNumSet.insert(data);
        }
        linesRead++;
    }
    return linesRead;
}
uinteger TwoSumFunction(const std::set<integer> &posNumSet,
                        const std::set<integer> &negNumSet)
{
    std::set<integer> targetValues;
    
    std::unordered_set<integer> pos_table;
    for(auto value : posNumSet)
        pos_table.insert(value);
    std::unordered_set<integer> neg_table;
    for(auto value : negNumSet)
        neg_table.insert(value);


    //Range [-10,000,10,000]
    std::vector<std::pair<integer, integer>> targetPairs;
    std::set<integer> diffTargetValues;
    
    const integer maxValue = 10000;
    const integer minValue = -10000;
    
    //First only seeing positive table or values

    {
        auto uppIt = posNumSet.upper_bound(maxValue);
        for(auto posIt = posNumSet.cbegin(); posIt != uppIt; ++posIt)
        {
            auto x = *posIt;
            for(auto posYIt = std::next(posIt); posYIt != uppIt; ++posYIt)
            {
                auto y = *posYIt;
                auto t = x + y;
                if(t <= maxValue)
                {
                    targetValues.insert(t);
                }
            }
        }
    }
    //Now only seeing negative table or values
    {
        auto lowerIt = negNumSet.lower_bound(minValue);
        for(auto posIt = lowerIt; posIt != lowerIt; ++posIt)
        {
            auto x = *posIt;
            for(auto posYIt = std::next(posIt); posYIt != negNumSet.cend(); ++posYIt)
            {
                auto y = *posYIt;
                auto t = x + y;
                if(t >= minValue)
                {
                    targetValues.insert(t);
                }
            }
        }
    }

    
//    //Comparing and seeing values in both
    {
        for(auto neg :negNumSet)
        {
            auto x = neg;
            auto yMax = maxValue - neg;
            auto yMin = minValue - neg;
            auto upIt = posNumSet.upper_bound(yMax);
            auto lowIt = posNumSet.lower_bound(yMin);
            for(auto it = lowIt; it != upIt; ++it)
            {
                auto y = *it;
                auto t = x + y;
                targetValues.insert(t);
            }
        }
    }
    return targetValues.size();
}
using namespace std::chrono;
int main(int argc, const char * argv[]) {
    auto timeStart = std::chrono::high_resolution_clock::now();
    std::set<integer> posNumSet, negNumSet;
    auto totalLines = Interface(posNumSet,negNumSet);
    auto distinctCounts = TwoSumFunction(posNumSet, negNumSet);
    std::cout << distinctCounts <<std::endl;
    auto timeEnd = std::chrono::high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(timeEnd - timeStart);
    std::cout << "timeTaken:    " <<duration.count() <<"microsec" <<std::endl;
    return 0;
}
