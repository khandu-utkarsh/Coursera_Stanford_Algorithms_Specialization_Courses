//
//  graph.cpp
//  Iterative_SCC
//
//  Created by Utkarsh Khandelwal on 29/02/20.
//  Copyright © 2020 Utk_Sort. All rights reserved.
//

#include "graph.hpp"
#include <iostream>

//#define DEBUG_SSC 0
using namespace std;


void static PrintData(integer intVal, string textToStart)
{
    ofstream output("/Users/utkarsh/Algorithms_Learning/Sorting_Alogs_CPP/Sorting_Algorithms_Learning/SCC/SCC/output.txt", ios::app);
    output << textToStart << "    " << intVal << endl;
}
#ifdef DEBUG_SSC
void static PrintData(integer nodeValue, integer GrpLeader, string textToStart)
{
    ofstream output("/Users/utkarsh/Algorithms_Learning/Sorting_Alogs_CPP/Sorting_Algorithms_Learning/SCC/SCC/output.txt", ios::app);
    output << nodeValue << "   " << textToStart << "    " <<  GrpLeader << endl;
}
#endif

integer Interface::ReadFile(const char * filePath, vector<pair<integer, integer>> &dataRead)
{
    std::ifstream input(filePath);
    vector<integer> tempVector;
    tempVector.reserve(2);
    integer linesCount = 0;
    if(input.is_open())
    {
        string currString;

        while(std::getline(input, currString))
        {
            tempVector.clear();
            stringstream strStream(currString);
            integer currData;
            while(strStream >> currData)
            {
                tempVector.emplace_back(currData);
            }
            if(tempVector.size() != 2)
            {
                assert("More than 2 nodes in an edge, not possible");
            }
            //First tail, //Second head
            dataRead.emplace_back(tempVector[0], tempVector[1]);
            linesCount++;
        }
    }
    return linesCount;
}

Node::Node(integer dataVal) : m_dataValue(dataVal),
                              m_hasSeen(false),
                              m_finishValue(0),
                              m_groupLeader(0)
{
}

Edge::Edge(node &head, node &tail, bool direction)
{
    m_head = head;
    m_tail = tail;
    m_dir = direction;
}

Edge::Edge(const Edge &copyObj)
{
    m_head = copyObj.m_head;
    m_tail = copyObj.m_tail;
    m_dir = copyObj.m_dir;
}

Edge::Edge(const Edge &&moveObj)
{
    m_head = std::move(moveObj.m_head);
    m_tail = std::move(moveObj.m_tail);
    m_dir = moveObj.m_dir;
}
    
Edge & Edge::operator =(const Edge & copyObj)
{
    m_head = copyObj.m_head;
    m_tail = copyObj.m_tail;
    m_dir = copyObj.m_dir;
    return *this;
}
    
Edge & Edge::operator =(const Edge && moveObj)
{
    m_head = move(moveObj.m_head);
    m_tail = move(moveObj.m_tail);
    m_dir = move(moveObj.m_dir);
    return *this;
}

node Edge::GetHead()
{
    if(m_dir)
        return m_head;
    else
        return m_tail;
}

node Edge::GetTail()
{
    if(m_dir)
        return m_tail;
    else
        return m_head;
}

void Edge::ReverseDirection()
{
    if(m_dir)
        m_dir = false;
    else
        m_dir = true;
}

bool Edge::GetDir()
{
    return m_dir;
}


Graph::Graph()
{
    
}
    
void Graph::CreateGraph(vector<pair<integer, integer>> &inputVec)
{
    for(auto currPair : inputVec)
    {
        auto &first = currPair.first;  //Tail
        auto firstIt = m_mapValueToNode.find(first);
        node firstNode;  //Tail Node
        if(firstIt != m_mapValueToNode.end())
            firstNode = (*firstIt).second;
        else
        {
            firstNode = make_shared<Node>(first);
            m_mapValueToNode.insert({first, firstNode});
            m_graphNodes.insert(firstNode);
        }
        
        auto &second = currPair.second;  //Head
        node secondNode; //Head Node
        auto secondIt = m_mapValueToNode.find(second);
        if(secondIt != m_mapValueToNode.end())
            secondNode = (*secondIt).second;
        else
        {
            secondNode = make_shared<Node>(second);
            m_mapValueToNode.insert({second, secondNode});
            m_graphNodes.insert(secondNode);
        }
        edge currEdge = make_shared<Edge>(secondNode, firstNode);
        firstNode->AddEdge(currEdge);
        m_graphEdges.insert(currEdge);
    }
}

bool Graph::ReverseGraph()
{
    //Reversing connectivities
    for(auto currEdge : m_graphEdges)
    {
        auto oldHead = currEdge->GetHead();
        auto oldTail = currEdge->GetTail();
        currEdge->ReverseDirection();
        auto &oldTailEdges = oldTail->GetEdges();
        auto itFound = std::find(oldTailEdges.begin(), oldTailEdges.end(), currEdge);
        if(itFound == oldTailEdges.end())
        {
            assert("No orignial connectivity, how to reverse it");
        }
        oldTailEdges.erase(itFound);
        oldHead->AddEdge(currEdge);
    }
    return true;
}

void Graph::ResetNodeMark()
{
    for(auto currNode : m_graphNodes)
    {
        currNode->SetVisibilityVariable(false);
    }
}

void Graph::ReverseIterativeDFS(vector<node> &revTimingVector)
{
    revTimingVector.reserve(m_graphNodes.size());
    for(integer iNode = 1; iNode <= m_graphNodes.size(); ++iNode)
    {
        node currNode = m_mapValueToNode[iNode];
        if(currNode == nullptr)
            continue;
        //PrintData(currNode->GetDataValue(), "Node Value");
        if(currNode->IsAlreadyVisited())
            continue;
        stack<node> currStack;
        currStack.push(currNode);
        while(currStack.size())
        {
            auto topNode = currStack.top();
            topNode->SetVisibilityVariable(true);
            auto &currNodeEdges = topNode->GetEdges();
            bool edgesAdded = false;
            for(auto currEdge : currNodeEdges)
            {
                auto edgeHead = currEdge->GetHead();
                if(edgeHead->IsAlreadyVisited())
                    continue;
                currStack.push(edgeHead);
                edgesAdded = true;
            }
            if(edgesAdded == false)
            {
                auto currTopNode = currStack.top();
                currStack.pop();
                if(currTopNode !=nullptr)
                    revTimingVector.push_back(currTopNode);
                //revTimingStack.push(currTopNode);
            }
        }
    }
}


void Graph::ForwardIterativeDFS(vector<node> &revTimingVector)
{
    long long int currStackSize = revTimingVector.size();
    for(integer iNode = revTimingVector.size() - 1; iNode >= 0; iNode--)
    {
        node leaderNode = revTimingVector[iNode];
        if(leaderNode->IsAlreadyVisited())
        {
            //revTimingStack.pop();
            //currStackSize--;
            continue;
        }
        integer leaderValue = leaderNode->GetDataValue();
        stack<node> currLocalStack;
        currLocalStack.push(leaderNode);
        while(currLocalStack.size())
        {
            auto topNode = currLocalStack.top();
            topNode->SetVisibilityVariable(true);
            topNode->SetGroupLeader(leaderValue);
            auto &currNodeEdges = topNode->GetEdges();
            bool edgesAdded = false;
            for(auto currEdge : currNodeEdges)
            {
                auto edgeHead = currEdge->GetHead();
                if(edgeHead->IsAlreadyVisited())
                    continue;
                currLocalStack.push(edgeHead);
                edgesAdded = true;
            }
            if(edgesAdded == false)
            {
                currLocalStack.pop();
            }
        }
        //revTimingStack.pop();
        //currStackSize--;
    }
}

//void Graph::IterativeDFS()
//{
//    if(m_timingQueue.size() == 0)
//        return;
//
//    stack<node> localStack;
//    while(m_timingQueue.size() != 0)
//    {
//        auto currNode = m_timingQueue.front();
//        m_timingQueue.pop();
//        if(currNode->IsAlreadyVisited())
//            continue;
//        localStack.push(currNode);
//        integer leaderValue = currNode->GetDataValue();
//        //currNode->SetVisibilityVariable(true);
//        while (localStack.size())
//        {
//            auto topNode = localStack.top();
//            topNode->SetGroupLeader(leaderValue);
//            localStack.pop();
//            topNode->SetVisibilityVariable(true);
//            auto &currNodeEdges = topNode->GetEdges();
//            for(auto currEdge : currNodeEdges)
//            {
//                auto edgeHead = currEdge->GetHead();
//                if(edgeHead->IsAlreadyVisited())
//                    continue;
//                localStack.push(edgeHead);
//            }
//        }
//    }
//}

bool Graph::FindSCC()
{
    ReverseGraph(); //Reverse Whole Graph

    //PrintEdgesAndNodes();
    vector<node> revTimingVector;
    //stack<node> revTimingStack;
    ReverseIterativeDFS(revTimingVector); //Do DFC


    ReverseGraph(); // Again restore connectivity

    //PrintEdgesAndNodes();

    ResetNodeMark(); // resetting seen mark
    ForwardIterativeDFS(revTimingVector);
    //IterativeDFS();
    //PrintStackData();

    //Print the value of stack

    //ForwardSearch(); //Do Depth First Search
    return true;
}

void Graph::GetSCCResult(std::vector<integer> &sizesVector)
{
    std::map<integer, vector<node>> map_leaderToSCC;
    for(auto currNode : m_graphNodes)
    {
        integer leaderValue = currNode->GetGroupLeader();
        auto it = map_leaderToSCC.find(leaderValue);
        if(it != map_leaderToSCC.end())
        {
            vector<node> &currComp = it->second;
            currComp.push_back(currNode);
        }
        else
        {
            vector<node> currComp;
            currComp.push_back(currNode);
            map_leaderToSCC.insert({leaderValue, currComp});
        }
    }
    for(auto iter : map_leaderToSCC)
    {
        integer connectivityCompSize = iter.second.size();
        sizesVector.emplace_back(connectivityCompSize);
    }
    std::sort(sizesVector.begin(), sizesVector.end(), [](integer &firstSize, integer &secondSize)->bool{
        if(firstSize > secondSize)
            return true;
        else
            return false;});
}
//#ifdef DEBUG_SSC
void Graph::PrintEdgesAndNodes()
{
    ofstream output("/Users/utkarsh/Algorithms_Learning/Sorting_Alogs_CPP/Sorting_Algorithms_Learning/SCC/SCC/output.txt", ios::app);
    output << "All graph Node Deails"   << endl;
    for(auto currNode :m_graphNodes)
    {
        output << "Node Value:  " << currNode->GetDataValue() << endl;
        output << "     Edges Attached:    " << endl;
        auto allEdges = currNode->GetEdges();
        for(auto currEdge : allEdges)
        {
            output << "             Edge Head    " <<currEdge->GetHead()->GetDataValue() << endl;
        }
    }

    output << "All graph Edges Details" << endl;
    for(auto edge : m_graphEdges)
    {
        output << "Tail  " << edge->GetTail()->GetDataValue() << "    "  << "Head "   << edge->GetHead()->GetDataValue() << endl;
    }


}
