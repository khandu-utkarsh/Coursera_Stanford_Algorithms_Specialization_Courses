//
//  graph.hpp
//  DjikstraAlgo
//
//  Created by Utkarsh Khandelwal on 06/03/20.
//  Copyright © 2020 Utk_Sort. All rights reserved.
//

#ifndef graph_hpp
#define graph_hpp

#include <stdio.h>
#include <vector>
#include <utility>
#include <set>
#include <memory>
#include <fstream>
#include <string>
#include <sstream>
#include <assert.h>
#include <algorithm>
#include <map>
#include <tuple>


using namespace std;
using integer = unsigned long int;
using vectorPair = vector<pair<integer, integer>>;

class Node;
class Edge;
using node = shared_ptr<Node>;
using edge = shared_ptr<Edge>;

//Helper Class
class Interface
{
public:
    static integer ReadFile(const char * filePath, vector< tuple< integer, vectorPair > > &dataRead);
};

class Node
{
private:
    integer m_dataValue;
    set<edge> m_edges;

public:
    Node(integer dataVal);
    
    //Trivial Functions
    inline integer GetDataValue() {return m_dataValue;}
    inline void AddEdge(edge &edgeToAdd) { m_edges.insert(edgeToAdd);}
    inline std::set<edge> &GetEdges(){return m_edges;}

};

class Edge{
    
public:
    //Constructors and Assignment Operators
    Edge(node &head, node &tail, integer distance);
    Edge(const Edge &copyObj);
    Edge(const Edge &&moveObj);
    
    Edge & operator =(const Edge &  copyObj);
    Edge & operator =(const Edge && moveObj);
    
    node GetHead();
    node GetTail();
    integer GetDistance();
    
private:
    shared_ptr<Node> m_head;
    shared_ptr<Node> m_tail;
    integer m_weight;

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
    
    void CreateGraph(vector< tuple< integer, vectorPair > > &dataRead);
    void Dijkstra(const integer sourceValue, vector<integer> &outputDists);
    void PrintReqData(vector<integer> &shortestDists);
    void PrintOnConsole(vector<integer> &shortestDists);
private:
    map<integer, node> m_mapValueToNode;

};






#endif /* graph_hpp */
