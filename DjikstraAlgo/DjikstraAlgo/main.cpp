//
//  main.cpp
//  DjikstraAlgo
//
//  Created by Utkarsh Khandelwal on 06/03/20.
//  Copyright © 2020 Utk_Sort. All rights reserved.
//
#include "graph.hpp"
#include <iostream>
int main(int argc, const char * argv[]) {
    vector< tuple< integer, vectorPair > > dataRead;

  Interface::ReadFile("/Users/utkarsh/Downloads/_dcf1d02570e57d23ab526b1e33ba6f12_dijkstraData.txt", dataRead);
    
    //Interface::ReadFile("/Users/utkarsh/Algorithms_Learning/Sorting_Alogs_CPP/Sorting_Algorithms_Learning/DjikstraAlgo/DjikstraAlgo/tempInput.txt", dataRead);
    
    Graph graphObj;
    graphObj.CreateGraph(dataRead);
    vector<integer> shortestDists;
    graphObj.Dijkstra(1,shortestDists);
    graphObj.PrintReqData(shortestDists);
    //graphObj.PrintOnConsole(shortestDists);
    return 0;
    }
