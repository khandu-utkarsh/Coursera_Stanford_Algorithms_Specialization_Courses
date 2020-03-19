//
//  main.cpp
//  SCC
//
//  Created by Utkarsh Khandelwal on 28/02/20.
//  Copyright © 2020 Utk_Sort. All rights reserved.
//

#include <iostream>


//Output File Path
// /Users/utkarsh/Algorithms_Learning/Sorting_Alogs_CPP/Sorting_Algorithms_Learning/SCC/SCC/output.txt


#include "graphInterface.hpp"
using namespace std;

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
    
    Interface::ReadFile("/Users/utkarsh/Algorithms_Learning/Sorting_Alogs_CPP/Sorting_Algorithms_Learning/stanford-algs-master/testCases/course2/assignment1SCC_Input/input_mostlyCycles_67_320000.txt", inputData);
    
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
    
//    cout << "Five Biggest SCC Are" << endl;
//    for(int iNode  = 0; iNode < 5; ++iNode)
//    for(int iNode  = 0; iNode < sizesVector.size(); ++iNode)
//    {
//        cout << sizesVector[iNode] << std::endl;
//    }
    
    return 0;
}
