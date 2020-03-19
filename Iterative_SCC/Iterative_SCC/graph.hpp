//
//  graph.hpp
//  Iterative_SCC
//
//  Created by Utkarsh Khandelwal on 29/02/20.
//  Copyright © 2020 Utk_Sort. All rights reserved.
//

#ifndef graph_hpp
#define graph_hpp

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
#include <queue>
using namespace std;
using integer = unsigned long long int;
using vectorPair = vector<pair<integer, integer>>;

class Node;
class Edge;

using node = shared_ptr<Node>;
using edge = shared_ptr<Edge>;

//Helper Class
class Interface
{
public:
    static integer ReadFile(const char * filePath, vector<pair<integer, integer>> &dataRead);
};

class Node
{
private:
    integer m_dataValue;
    set<edge> m_edges;
    
    bool m_hasSeen;
    integer m_finishValue;
    integer m_groupLeader;
public:
    Node(integer dataVal);
    
    //Trivial Functions
    inline integer GetDataValue() {return m_dataValue;}
    inline void AddEdge(edge &edgeToAdd) { m_edges.insert(edgeToAdd);}
    inline std::set<edge> &GetEdges(){return m_edges;}
    
    inline bool IsAlreadyVisited() {return m_hasSeen;}
    inline void SetVisibilityVariable(bool inputHasSeen) {m_hasSeen = inputHasSeen;}
    
    inline integer GetFinishValue() {return m_finishValue;}
    inline void SetFinishValue(integer &setThis) {m_finishValue = setThis;}
    
    inline integer GetGroupLeader() {return m_groupLeader;}
    inline void SetGroupLeader(integer grpLeader) {m_groupLeader = grpLeader;}

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
    void ReverseIterativeDFS(vector<node> &revTimingVector);
    void ForwardIterativeDFS(vector<node> &revTimingVector);
    void GetSCCResult(std::vector<integer> &sizesVector);
    
    
    
public:
            void PrintEdgesAndNodes();
#ifdef DEBUG_SSC

        void PrintSCCResult();
        void PrintStackData();
#endif

private:
    set<edge> m_graphEdges;
    set<node> m_graphNodes;
    map<integer, node> m_mapValueToNode;
    //queue<node> m_timingQueue;
    //stack<node> m_nodeTimeStack;
};

#endif /* graph_hpp */
