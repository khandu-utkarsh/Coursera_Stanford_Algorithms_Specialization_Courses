//
//  auxiliaryFunctions.hpp
//  Sorting
//
//  Created by Utkarsh Khandelwal on 07/01/20.
//  Copyright © 2020 Utk_Sort. All rights reserved.
//

#ifndef auxiliaryFunctions_hpp
#define auxiliaryFunctions_hpp

#include <stdio.h>
#include<vector>
#include<string>
class Helpers
{
public:
    static bool ParseStringFromConsolesIntoAndIntegerArray(std::string &input, std::vector<int> &output);
    static bool ParseDataFromFile(std::string filePath, std::vector<int> &inputData);

    
    static bool PrintDataOnConsole(std::vector<int> &outputData);
};

#endif /* auxiliaryFunctions_hpp */
