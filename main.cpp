
//  main.cpp
//  Jansen Dike
//  COSC 320
//  Project 3

#include <iostream>
#include "CG.cpp"

int main() {

    Graph test;          //test graph

/*
    test.testTime();	//calls function for testing time of algorithm
*/


    test.readJobFiles("jobNames1.txt", "jobEdges1.txt");	//calls function to read job files passed in
    test.checkCycle(1);						//checks for cycles in the graph
    test.Schedule();						//calls function to run Coffman-Graham

    return 0;
}
