//
//  main.cpp
//  MedianFinding_UsingHeaps
//
//  Created by Utkarsh Khandelwal on 14/03/20.
//  Copyright © 2020 Utk_Sort. All rights reserved.
//

#include <iostream>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <numeric>
#include "heap.cpp"
using namespace std;

size_t Interface(std::vector<size_t> &inputVector, std::string &filePath)
{
    std::ifstream input(filePath);
    string data;
    size_t linesRead = 0;
    while(std::getline(input, data))
    {
        size_t value = std::stoull(data);
        inputVector.emplace_back(value);
        linesRead++;
    }
    return linesRead;
}


int main(int argc, const char * argv[])
{
    std::string inputPath;
    if(argc >= 2)
    {
        const char * filePath = argv[1];
        inputPath = filePath;
    }
    vector<size_t> inpVector;
    Interface(inpVector, inputPath);

    size_t inputSize =inpVector.size();
    MedianFinder<size_t> finder(inputSize);
    std::vector<size_t> medians;
    for(auto value : inpVector)
    {
        finder.InsertElement(value);
        size_t median = finder.GetMedian();
        medians.emplace_back(median);
    }
    
    size_t sum = 0;
    size_t finalSum = std::accumulate(medians.begin(), medians.end(), sum);
    
    std::cout << "Final Sum:  " << finalSum << endl;
    return 0;
}
