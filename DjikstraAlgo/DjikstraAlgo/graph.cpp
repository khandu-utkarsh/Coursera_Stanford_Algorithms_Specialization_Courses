//
//  graph.cpp
//  DjikstraAlgo
//
//  Created by Utkarsh Khandelwal on 06/03/20.
//  Copyright © 2020 Utk_Sort. All rights reserved.
//

#include "graph.hpp"
#include <iostream>

using namespace std;

 integer Interface::ReadFile(const char * filePath, vector< tuple<integer, vectorPair> > &dataRead)
{
    std::ifstream input(filePath);
    integer linesCount = 0;
    if(input.is_open())
    {
        string line;
        while(std::getline(input, line))
        {
            stringstream lineStream(line);
            string data;

            integer sourceNode;
            vectorPair weightedEdges;
            while(lineStream >> data)
            {
                auto commaPos = data.find(",");
                if(commaPos == string::npos)
                {
                    //No sub string found,
                    //Means it is the value of node
                    sourceNode = stoul(data);
                }
                else
                {
                    //Extracting Sub strings
                    integer sLength = data.size();
                    string edgeNode = data.substr(0,  commaPos);
                    integer edgeDisStrLen = sLength - (commaPos + 1);
                    string edgeWeigth = data.substr(commaPos + 1, edgeDisStrLen);
                    weightedEdges.emplace_back(stoul(edgeNode), stoul(edgeWeigth));
                }
            }
            dataRead.emplace_back(make_tuple(sourceNode, weightedEdges));
            linesCount++;
        }
    }
    return linesCount;
}

Node::Node(integer dataVal) : m_dataValue(dataVal)
{
}

// !Functions working on edges

Edge::Edge(node &head, node &tail, integer distance)
{
    m_head = head;
    m_tail = tail;
    m_weight = distance;

}

Edge::Edge(const Edge &copyObj)
{
    m_head = copyObj.m_head;
    m_tail = copyObj.m_tail;
    m_weight = copyObj.m_weight;
}

Edge::Edge(const Edge &&moveObj)
{
    m_head = std::move(moveObj.m_head);
    m_tail = std::move(moveObj.m_tail);
    m_weight = std::move(moveObj.m_weight);
}
    
Edge & Edge::operator =(const Edge & copyObj)
{
    m_head = copyObj.m_head;
    m_tail = copyObj.m_tail;
    m_weight = copyObj.m_weight;
    return *this;
}
    
Edge & Edge::operator =(const Edge && moveObj)
{
    m_head = move(moveObj.m_head);
    m_tail = move(moveObj.m_tail);
    m_weight = move(moveObj.m_weight);
    return *this;
}

integer Edge::GetDistance()
{
    return m_weight;
}

node Edge::GetHead()
{
    return m_head;
}

node Edge::GetTail()
{
     return m_tail;
}

Graph::Graph()
{
    
}

void Graph::CreateGraph(vector< tuple< integer, vectorPair > > &dataRead)
{
    for(auto & element : dataRead)
    {
        integer & sourceNodeValue = std::get<0>(element);
        auto & weightedEdges = std::get<1>(element);

        node source;
        auto iter = m_mapValueToNode.find(sourceNodeValue);
        if(iter != m_mapValueToNode.end())
        {
            //Already Present
            source = (*iter).second;
        }
        else
        {
            source = make_shared<Node>(sourceNodeValue);
            m_mapValueToNode.insert({sourceNodeValue, source});
        }
        
        for(auto &edgeData : weightedEdges)
        {
            integer headNodeValue = edgeData.first;
            integer distance = edgeData.second;
            
            node headNode;
            auto headIter = m_mapValueToNode.find(headNodeValue);
            if(headIter != m_mapValueToNode.end())
            {
                headNode = (*headIter).second;
            }
            else
            {
                headNode = make_shared<Node>(headNodeValue);
                m_mapValueToNode.insert({headNodeValue, headNode});
            }
            edge newEdge = make_shared<Edge>(headNode, source, distance);
            source->AddEdge(newEdge);
        }
    }
}

void Graph::Dijkstra(const integer sourceValue, vector<integer> &outputDists)
{
    integer notConnectedDist = 1000000;
    integer totalNodes = m_mapValueToNode.size();
    
    node sourceNode = m_mapValueToNode[sourceValue];
    auto & sourceEdges = sourceNode->GetEdges();
    
    //Assuming that there is no node missing i.e nodes are numbered from 1 to nodesCount;
    vector<integer> shortestDistances(totalNodes, notConnectedDist);
    shortestDistances[sourceValue - 1] = 0;

    set<node> nodesInDomain;
    vector<edge> edgesGoingOut;

    nodesInDomain.insert(sourceNode);
    edgesGoingOut.insert(edgesGoingOut.end(), sourceEdges.begin(), sourceEdges.end());
    shortestDistances[sourceValue - 1] = 0;

    while(edgesGoingOut.size() != 0)
    {
        vector<edge> domainEdges;

        integer minimumDistance = notConnectedDist;
        node minNode;
        integer minEdgeTailValue = 0;
        edge minEdge;
        
        bool noEdgeValid = true;
        for(auto edge : edgesGoingOut)
        {
            node tail = edge->GetTail();
            integer tailIndex = tail->GetDataValue() - 1;
            node head = edge->GetHead();
            auto fountIt = std::find(nodesInDomain.begin(),nodesInDomain.end(), head);
            if(fountIt != nodesInDomain.end())
            {
                domainEdges.push_back(edge);
                continue;
            }
            integer edgeLen = edge->GetDistance();
            integer dist = edgeLen + shortestDistances[tailIndex];
            if(dist < minimumDistance)
            {
                minEdgeTailValue = tail->GetDataValue();
                minimumDistance = dist;
                minNode = head;
                minEdge = edge;
                noEdgeValid = false;
            }
        }
        
        if(noEdgeValid)
            break;
        
        domainEdges.push_back(minEdge);
        
        //Updating the shortest distances vector
        integer indexInVector = minNode->GetDataValue() - 1;
        integer minEdgeTailIndex = minEdgeTailValue -1;
        shortestDistances[indexInVector] =  minimumDistance;
        nodesInDomain.insert(minNode);

        
        //Deleting the array which are no more going out of domain
        auto lambdaCheck = [&domainEdges](const edge & currEdge)
        {
        auto present = std::find(domainEdges.begin(), domainEdges.end(), currEdge);
        if(present != domainEdges.end())
            return true;
        else
            return false;
        };
        auto newEnd = std::remove_if(edgesGoingOut.begin(), edgesGoingOut.end(), lambdaCheck);
        auto validCount = std::distance(edgesGoingOut.begin(), newEnd);
        edgesGoingOut.resize(validCount);

        //Adding all edges going out from minNode;
        auto & edgesFromMinNode = minNode->GetEdges();
        edgesGoingOut.insert(edgesGoingOut.end(), edgesFromMinNode.begin(), edgesFromMinNode.end());
    }
    outputDists = shortestDistances;
}

void Graph::PrintReqData(vector<integer> &shortestDists)
{
    ofstream out("/Users/utkarsh/Algorithms_Learning/Sorting_Alogs_CPP/Sorting_Algorithms_Learning/DjikstraAlgo/DjikstraAlgo/tempOutput.txt", ios::app);
    
    std::vector<integer> reqNodes{7,37,59,82,99,115,133,165,188,197};

    //reqNodes.clear();

    //for(auto itPair : m_mapValueToNode)
    //{
    //    integer value = itPair.first;
    //    reqNodes.push_back(value);
    //}

    out << std::endl;
    for(auto value : reqNodes)
    {
        integer index = value - 1;
        out << shortestDists[index] << ",";
    }
}

void Graph::PrintOnConsole(vector<integer> &shortestDists)
{
    std::vector<integer> reqNodes{7,37,59,82,99,115,133,165,188,197};
}
