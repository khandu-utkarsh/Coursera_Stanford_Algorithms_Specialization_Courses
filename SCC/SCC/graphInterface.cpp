#include "graphInterface.hpp"
#include <iostream>
//#define DEBUG_SSC 0
using namespace std;

#ifdef DEBUG_SSC
void static PrintData(integer intVal, string textToStart)
{
    ofstream output("/Users/utkarsh/Algorithms_Learning/Sorting_Alogs_CPP/Sorting_Algorithms_Learning/SCC/SCC/output.txt", ios::app);
    output << textToStart << "    " << intVal << endl;
}
void static PrintData(integer nodeValue, integer GrpLeader, string textToStart)
{
    ofstream output("/Users/utkarsh/Algorithms_Learning/Sorting_Alogs_CPP/Sorting_Algorithms_Learning/SCC/SCC/output.txt", ios::app);
    output << nodeValue << "   " << textToStart << "    " <<  GrpLeader << endl;
}
#endif

void Interface::ReadFile(const char * filePath, vector<pair<integer, integer>> &dataRead)
{
    std::ifstream input(filePath);
    vector<integer> tempVector;
    tempVector.reserve(2);
    int linesCount = 0;
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
        auto &second = currPair.second;  //Head
        auto firstIt = m_mapValueToNode.find(first);
        //auto firstIt = std::find(m_mapValueToNode.begin(), m_mapValueToNode.end(), first);
        node firstNode;  //Tail Node
        node secondNode; //Head Node
        if(firstIt != m_mapValueToNode.end())
        {
            //Means first exists, we simply need to add edge
            firstNode = (*firstIt).second;
        }
        else
        {
            firstNode = make_shared<Node>();
            firstNode->m_dataValue = first;
            firstNode->m_hasSeen = false;
            m_mapValueToNode.insert({first, firstNode});
            m_graphNodes.insert(firstNode);
        }
        auto secondIt = m_mapValueToNode.find(second);
        //        auto secondIt = std::find(m_mapValueToNode.begin(), m_mapValueToNode.end(), second);
        if(secondIt != m_mapValueToNode.end())
        {
            //Means, second exists, we need to add edge
            secondNode = (*secondIt).second;
        }
        else
        {
            secondNode = make_shared<Node>();
            secondNode->m_dataValue = second;
            secondNode->m_hasSeen = false;
            m_mapValueToNode.insert({second, secondNode});
            m_graphNodes.insert(secondNode);
        }
        edge currEdge = make_shared<Edge>(secondNode, firstNode);
        firstNode->m_edges.insert(currEdge);
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
        auto &oldTailEdges = oldTail->m_edges; //Should be a reference
        
        auto itFound = std::find(oldTailEdges.begin(), oldTailEdges.end(), currEdge);
        if(itFound == oldTailEdges.end())
        {
            assert("No orignial connectivity, how to reverse it");
        }
        oldTailEdges.erase(itFound);
        oldHead->m_edges.insert(currEdge);
    }
    return true;
}

void Graph::ResetNodeMark()
{
    for(auto currNode : m_graphNodes)
    {
        currNode->m_hasSeen = false;
    }
}

void Graph::DFS(stack<node> &currStack,
                integer &currTiming,
                integer &currLeader,
                const bool &reverseDFS)
{

    if(currStack.size() == 0)
        return;
    else
    {
        node currNode = currStack.top();
        bool currVisibltyValue = currNode->m_hasSeen;
        if(currVisibltyValue)
            return;
#ifdef DEBUG_SSC
        PrintData(currStack.top()->m_dataValue, "DFS_Call");
#endif
        currNode->m_hasSeen = true;
        currNode->m_groupLeader = currLeader;
#ifdef DEBUG_SSC
        PrintData(currNode->m_dataValue, currLeader, " < ---- Node, Leader ---- >");
#endif
        for(auto edge  : currNode->m_edges)
        {
            auto edgeHead = edge->GetHead();
            if(edgeHead->m_hasSeen)
                continue;
            else
            {
                currStack.push(edgeHead);
                if(!reverseDFS)
                {
                    //PrintData(currNode->m_dataValue, currLeader, "First node, second group Leader");
                }
                currNode->m_groupLeader = currLeader;
                DFS(currStack, currTiming, currLeader, reverseDFS);
            }
        }
        //Loop done or no edges found
        if(reverseDFS)
        {
            integer currUseCount = currNode.use_count();
            if(currUseCount == 0)
            {
                assert("No pointer exists");
            }
            m_revTimingStack.push(currNode);
#ifdef DEBUG_SSC
            PrintData(currNode->m_dataValue, "Pushed into m_rev Stack");
#endif
        }

        currStack.pop();
    }
}

void Graph::ReverseSearch()
{
    integer currTiming = 0;
    integer currGroupLeader = 0;
    stack<node> nodeStack;
    for(auto &currNode : m_graphNodes)
    {
        //PrintData(currNode->m_dataValue, "  Loop Started with prev node ");
        nodeStack.push(currNode);
        currGroupLeader = currNode->m_dataValue;
        DFS(nodeStack, currTiming, currGroupLeader, true);
    }
}


void Graph::ForwardSearch()
{
    if(m_revTimingStack.size() == 0)
        return;
    while(m_revTimingStack.size() !=  0)
    {
        auto currTop = m_revTimingStack.top();
        if(currTop->m_hasSeen == true)
        {
            m_revTimingStack.pop();
            continue;
        }
        stack<node> currStack;
        integer currTiming;
        currStack.push(currTop);
        integer currGrpLeader = currTop->m_dataValue;
#ifdef DEBUG_SSC
        PrintData(currGrpLeader, "Group Leader, just before forward dfs call ");
#endif
        DFS(currStack, currTiming, currGrpLeader, false);
        m_revTimingStack.pop();
    }
}

bool Graph::FindSCC()
{
    ReverseGraph(); //Reverse Whole Graph
    
    //PrintEdgesAndNodes();
    
    ReverseSearch(); //Do DFC
    
    
    ReverseGraph(); // Again restore connectivity
    
    //PrintEdgesAndNodes();
    
    ResetNodeMark(); // resetting seen mark
    
    //PrintStackData();
    
    //Print the value of stack
    
    ForwardSearch(); //Do Depth First Search
    return true;
}

void Graph::GetSCCResult(std::vector<integer> &sizesVector)
{
    std::map<integer, vector<node>> map_leaderToSCC;
    for(auto currNode : m_graphNodes)
    {
        integer leaderValue = currNode->m_groupLeader;
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
#ifdef DEBUG_SSC
void Graph::PrintEdgesAndNodes()
{
    ofstream output("/Users/utkarsh/Algorithms_Learning/Sorting_Alogs_CPP/Sorting_Algorithms_Learning/SCC/SCC/output.txt", ios::app);
    output << "All graph Node Deails"   << endl;
    for(auto currNode :m_graphNodes)
    {
        output << "Node Value:  " << currNode->m_dataValue << endl;
        output << "     Edges Attached:    " << endl;
        for(auto currEdge : currNode->m_edges)
        {
            output << "             Edge Head    " <<currEdge->GetHead()->m_dataValue << endl;
        }
    }
    
    output << "All graph Edges Details" << endl;
    for(auto edge : m_graphEdges)
    {
        output << "Tail  " << edge->GetTail()->m_dataValue << "    "  << "Head "   << edge->GetHead()->m_dataValue << endl;
    }
    
    
}
#endif
#ifdef DEBUG_SSC
void Graph::PrintStackData()
{
    ofstream output("/Users/utkarsh/Algorithms_Learning/Sorting_Alogs_CPP/Sorting_Algorithms_Learning/SCC/SCC/output.txt", ios::app);
    output << "Stack Data" << endl;
    
    std::vector<node> stackDataParked;
    while(m_revTimingStack.size() != 0)
    {
        stackDataParked.push_back(m_revTimingStack.top());
        m_revTimingStack.pop();
    }
    for(auto data : stackDataParked)
    {
        output << "Node Value:  " << data->m_dataValue <<endl;
    }
    std::reverse(stackDataParked.begin(), stackDataParked.end());
    for(auto data : stackDataParked)
    {
        m_revTimingStack.push(data);
    }
    //Again inserting data in stack
    
}
#endif
#ifdef DEBUG_SSC
void Graph::PrintSCCResult()
{
    ofstream output("/Users/utkarsh/Algorithms_Learning/Sorting_Alogs_CPP/Sorting_Algorithms_Learning/SCC/SCC/output.txt", ios::app);
    output << "Output order stack results" << endl;
    for(auto currNode :m_graphNodes)
    {
        output << "Node Value:  " << currNode->m_dataValue <<  "    Group Leader:  " << currNode->m_groupLeader <<endl;
    }
}
#endif
