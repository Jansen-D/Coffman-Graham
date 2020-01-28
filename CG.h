//  CG.h
//  Jansen Dike
//  COSC 320
//  Project 3


#ifndef CG_h
#define CG_h


#include <stdio.h>
#include <algorithm>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <stack>
#include <queue>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>

enum color_t{       //possible colorings of vertices
    WHITE,          //not visited (default)
    GRAY,           //visited
};

class Graph{
private:
    std::map<int, std::vector<int>> outgoing;       //vector holding outgoing vertices of each vertex
    std::map<int, std::vector<int>> incoming;       //vector holding incoming vertices of each vertex
    std::map<int, std::string> jobName;             //string holding the corresponding name for each job
    void topoSortUtil(int v, std::stack<int> &sorted, std::vector<int> &visited);       //recursive utlility function to help topological sort
    bool checkCycleHelp(int v, std::map<int, color_t> &colors);     //recursive helper function to check for cycles
    
public:
    void testTime();				//function to test timing of CG algorithm
    void makeBigGraph(int vertices);		//function to create large graph for testing time
    void readJobFiles(std::string nameFile, std::string edgeFile);		//function to read info from jobfiles with file names as parameters
    void Schedule();                    //function to create schedule for processors
    bool jobReady(int vertex, std::vector<int> &visited, std::map<int, int> &timeSlot, int currTime, int currPos);         //function to determine if a task is ready
    void topoSort(std::vector<int> &topOrder);                    //topological sort function
    bool contained(std::vector<int> &vect, int check);            //determine if vector contains an int
    void addVertex(int vertex, std::string job);         //function to add vertex to graph given an integer
    void addEdge(int v1, int v2);       //function to add an edge given the two vertices
    void checkCycle(int Vs);            //function to check for a cycle in the graph
    void print();                       //function to print list of vertices each of their adjacent vertices
};


#endif /* CG_h */
