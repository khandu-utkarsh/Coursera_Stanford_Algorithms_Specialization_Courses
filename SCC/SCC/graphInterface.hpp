//
//  graphInterface.hpp
//  SCC
//
//  Created by Utkarsh Khandelwal on 28/02/20.
//  Copyright © 2020 Utk_Sort. All rights reserved.
//

#ifndef graphInterface_hpp
#define graphInterface_hpp


#include <vector>
#include <utility>
#include <set>
#include <memory>
#include <map>
#include <stack>
#include <fstream>
#include <string>
#include <sstream>
#include <assert.h>
#include <algorithm>

using namespace std;
using integer = unsigned long int;
using vectorPair = vector<pair<integer, integer>>;

struct Node;
class Edge;
using node = shared_ptr<Node>;
using edge = shared_ptr<Edge>;
    //Helper Class
class Interface
{
public:
    static void ReadFile(const char * filePath, vector<pair<integer, integer>> &dataRead);
    

};

struct Node
{
    integer m_dataValue;
    set<edge> m_edges;
    bool m_hasSeen;
    integer m_finishValue;
    integer m_groupLeader;
};

class Edge{
    
public:
    //Constructors and Assignment Operators
    Edge(node &head, node &tail, bool direction = true);  //True means m_head is head and m_tail is tail
    Edge(const Edge &copyObj);
    Edge(const Edge &&moveObj);
    
    Edge & operator =(const Edge &  copyObj);
    Edge & operator =(const Edge && moveObj);
    
    node GetHead();
    node GetTail();
    void ReverseDirection();
    bool GetDir();
    
private:
    shared_ptr<Node> m_head;
    shared_ptr<Node> m_tail;
    bool m_dir;


};
//
//
//
class Graph
{
public:

    //Constructors
    Graph();
    Graph(const Graph &copyObj) = delete;
    Graph(const Graph &&moveObj) = delete;
    Graph& operator =(const Graph &&moveObj) = delete;
    Graph& operator =(const Graph &copyObj) = delete;
    
    void CreateGraph(vector<pair<integer, integer>> &inputVec);
    bool ReverseGraph();
    
    void ResetNodeMark();

    
    bool FindSCC();
    void ForwardSearch();
    void ReverseSearch();
    void DFS(stack<node> &currStack,
             integer &currTiming,
             integer &currLeader,
             const bool &reverseDFS);

    void GetSCCResult(std::vector<integer> &sizesVector);
    
    
    
public:
#ifdef DEBUG_SSC
        void PrintEdgesAndNodes();
        void PrintSCCResult();
        void PrintStackData();
#endif

private:
    set<edge> m_graphEdges;
    set<node> m_graphNodes;
    map<integer, node> m_mapValueToNode;
    stack<node> m_revTimingStack;
};
//
//
//

#endif /* graphInterface_hpp */





