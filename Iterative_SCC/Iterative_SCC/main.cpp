//
//  main.cpp
//  Iterative_SCC
//
//  Created by Utkarsh Khandelwal on 29/02/20.
//  Copyright © 2020 Utk_Sort. All rights reserved.
//

#include <iostream>
#include "graph.hpp"
using namespace std;

// /Users/utkarsh/Algorithms_Learning/Sorting_Alogs_CPP/Sorting_Algorithms_Learning/SCC/SCC/testData.txt

void static PrintSSC_Sizes(const vector<integer> &sscSizes)
{
    ofstream output("/Users/utkarsh/Algorithms_Learning/Sorting_Alogs_CPP/Sorting_Algorithms_Learning/SCC/SCC/output.txt", ios::app);
    output << "Decreasing order SSC Output are" << endl;
    for(auto &data : sscSizes)
    {
        output << data << endl;
    }
}


int main(int argc, const char * argv[])
{

    vector<pair<integer, integer>> inputData;
    //Interface::ReadFile( "/Users/utkarsh/Downloads/_410e934e6553ac56409b2cb7096a44aa_SCC.txt", inputData);
    
    integer lineRead = Interface::ReadFile("/Users/utkarsh/Algorithms_Learning/Sorting_Alogs_CPP/Sorting_Algorithms_Learning/SCC/SCC/_410e934e6553ac56409b2cb7096a44aa_SCC.txt", inputData);
    
    Graph graphObj;
    graphObj.CreateGraph(inputData);
    //graphObj.PrintEdgesAndNodes();
    graphObj.FindSCC();
    std::vector<integer> sizesVector;
#ifdef DEBUG_SSC
    graphObj.PrintSCCResult();
#endif

    graphObj.GetSCCResult(sizesVector);
    PrintSSC_Sizes(sizesVector);
    return 0;
}
