//  CG.cpp
//  Jansen Dike
//  COSC 320
//  Project 3


#include "CG.h"

void Graph::readJobFiles(std::string nameFile, std::string edgeFile){		//function to read files containing job names and edges
    std::string v1, v2;		//v1 will be first vertex, v2 will be second
    std::string jobName;	//holds current jobName to be read in
    int jobNo = 1;		//keeps track of vertex number

    

    std::ifstream inFile(nameFile);	//stream first file jobNames

       if (inFile.is_open()) {		//if file was opened successfully

           while (inFile >> jobName) {		//read in one name at a time

               addVertex(jobNo, jobName);	//add vertex for each jobname

               jobNo++;				//increase current vertex number

           }

       }
    
    std::ifstream inFile2(edgeFile);	//stream second file (jobEdges)
    if (inFile2.is_open()) {		//if file opened successfully
        while (inFile2 >> v1 >> v2) {		//while there is still a pair of two ints to be read in
          addEdge(std::stoi(v1), std::stoi(v2));		//add edge from v1 TO v2
        }
    }
    
    
    
}

void Graph::testTime(){			//function to test Coffman-Graha, algorithm timing
	int Vsize;			//holds number of vertices or "size" of graph
	std::cout << "Enter number of vertices to test timing of the Coffman-Graham scheduling algorthm: " << std::endl;	//prompt user for size
	std::cin >> Vsize;		//read in size
	makeBigGraph(Vsize);		//create graph with Vsize number of vertices
	
	double start1 = double(clock()) / CLOCKS_PER_SEC;		//start clock
	Schedule();						//call CG algortihm
	double finish1 = double(clock()) / CLOCKS_PER_SEC;		//stop clock
	double elapsed1 = finish1 - start1;			//calculate elapsed time
	elapsed1 = elapsed1/1000;				//divide by 1000 to get time in seconds
	std::cout << "Scheduling time(s): " << elapsed1 << std::endl << std::endl;		//print scheduling time
}

void Graph::makeBigGraph(int vertices){		//function to make graph for testing time

    for(int i=0; i<vertices; i++){		//for loop to add each vertex

        std::string tempName = "Job";		//Each job name starts with "job"

        std::ostringstream oss;			//Create stringstream to add the jobNumber to the jobName to keep track

        oss << tempName << i;			//appending integer i (the job number) to the jobname

        addVertex(i+1, oss.str());		//adding job number and name

    }

    for(int i=0; i<vertices-3; i++){		//for loop to add edges to graph

        addEdge(i+1, i+3);			// adds edge to the vertex two ahead of itself
	
        if(i <= 0){
		addEdge(i+1,i+4);		//add additional edge from first to fourth vertex
	}

        int randint = rand() % 5 + 1;		//random int to add variety to graph

        if(i % 2 == 0){				//if i is even

            if(randint == 5 && (i+4)<vertices){		//if randint = 5 and there remains a vertex 3 positions ahead
		if(i>1){	//if i<1 this edge already exists
			addEdge(i+1, i+4);		//add edge to three ahead of current vertex
		}

            }

        }else{

            if(randint == 5 ){		//if odd and randint = 5
                addEdge(i+1, i+2);	//add edge to the vertex one ahead

            }

        }

    }

}

void Graph::addVertex(int vertex, std::string job){      //function to add vertex to graph given an integer
    std::vector<int> adj;               //vector holding its adjacent vertices (empty to start)
    
    if(outgoing.find(vertex) == outgoing.end()){            //if the vertex is not already in the graph
       outgoing.insert(std::pair<int, std::vector<int>>(vertex, adj));      //insert the vertex into the map
    }
    
    std::vector<int> inc;               //vector holding its adjacent vertices (empty to start)
    
    if(incoming.find(vertex) == incoming.end()){            //if the vertex is not already in the graph
       incoming.insert(std::pair<int, std::vector<int>>(vertex, inc));      //insert the vertex into the map
    }
    
    jobName.insert(std::pair<int, std::string>(vertex, job));
}

void Graph::addEdge(int v1, int v2){        //function to add an edge from v1 to v2
    
    if(v1 == v2){       //if they are the same vertex
        //std::cout << "Cannot add edge from a node to itself" << std::endl;    //print error message
        return;
    }
    
    if(outgoing.find(v1) == outgoing.end()){            //if first vertex is not in graph
        //std::cout << "Error: First vertex entered is not in graph" << std::endl;      //error message
        return;
    }
    if(outgoing.find(v2) == outgoing.end()){            //if second vertex is not in graoh
        //std::cout << "Error: Second vertex entered is not in graph" << std::endl;     /error message
        return;
    }
    
    
    if(std::find(outgoing[v1].begin(), outgoing[v1].end(), v2) == outgoing[v1].end()){  //edge is not already in graph
        outgoing[v1].push_back(v2);     //add v2 to v1's adjacent vertex list
        incoming[v2].push_back(v1);     //add v1 to v2's incoming vertex list
        return;
    }
    else{
        //std::cout << "Edge is already in graph!" << std::endl;    //error message
    }
}

void Graph::topoSortUtil(int v, std::stack<int> &sorted, std::vector<int> &visited){        //recursive utility function for topological sorting
    
    for(int i = 0; i<outgoing.at(v).size(); i++){       //traverse the outgoing nodes
            if(!contained(visited, outgoing.at(v).at(i)))       //if this outgoing vertex has not been visited
                topoSortUtil(outgoing.at(v).at(i), sorted, visited);        //recursive call
    
    }
    visited.push_back(v);       //push back v as a visited vertex
    sorted.push(v);     //push v into the sorted stack
}

void Graph::topoSort(std::vector<int> &topOrder){       //function to topologically sort job graph
    
    std::stack<int> sorted;         //stack to hold the topological ordering
    std::vector<int> visited;       //vector to hold visited vertices
    
    for(std::map<int, std::vector<int>>::const_iterator it = outgoing.begin(); it != outgoing.end(); it++){ //iterating the outgoing vertex map
        if(!contained(visited, it->first))      //if the vertec has been visited
            topoSortUtil(it->first, sorted, visited);       //call recursive topoSort Utility function
    }
    
    while(!sorted.empty()){
        topOrder.push_back(sorted.top());       //add the top of the stack to the topological ordering
        //std::cout << sorted.top() << " ";       //print the top of stack
        sorted.pop();       //pop the top of the stack
    }
}


bool Graph::contained(std::vector<int> &vect, int check){       //function to check if a vector contains an integer check
    bool doesContain = false;       // return variable false by default
    
    for(int i=0; i<vect.size(); i++){       //traverse vector
        if(vect.at(i)== check){         //if the vector at i is equal to the integer that is checked
            doesContain = true;     //true if vectoe does contain the integer
        }
    }
    return doesContain;         //returns boolean doesContain, true if the vector does contain
}

bool Graph::jobReady(int vertex, std::vector<int> &visited, std::map<int, int> &timeSlot, int currTime, int currPos){
    bool ready = true;          //true by default
    for(int i=0; i<incoming.at(vertex).size(); i++){        //traverse the pre-required jobs
        if(contained(visited, incoming.at(vertex).at(i)) == true){     //if all this job's pre-required job have been completed
			if(timeSlot.at(incoming.at(vertex).at(i)) == currTime){
				return false;
			}
		
        }else{
		return false;
	  }
    }
    return ready;           //return boolean ready (returns false if the pre-req jobs have not been completed
}

void Graph::Schedule(){                 //function to schedule the jobs using Coffman-Graham
	
	//Print statements/formatting...

	std::cout << std::endl << std::endl << 		"-------------------------------------------------------" << std::endl;
	std::cout << "-------------------------------------------------------" << std::endl;
	std::cout << "-------------------------------------------------------" << std::endl;
	std::cout << "-------|Coffman-Graham Job Scheduling Algorithm|-------" << std::endl;
	std::cout << "-------------------------------------------------------" << std::endl;
	std::cout << "-------------------------------------------------------" << std::endl;
	std::cout << "-------------------------------------------------------" << std::endl;
	

    std::vector<int> topOrder;          //will hold the job ordering
    topoSort(topOrder);                 //call topological sort to order the jobs
    std::vector<int> proc1;             //vector to keep track of processor 1's jobs
    std::vector<int> proc2;             //vector to keep track of processor 2's jobs
    std::vector<int> visited;           //keeps track of conpleted jobs
    std::map<int, int> timeSlot;        //map to keep time slot for each job
    
    int i=0;            //iterator for jobs order
    int time = 1;       //1 is starting time slot
	std::cout << std::endl << std::endl << "Scheduling..." << std::endl << std::endl;
while(i<topOrder.size()){       //while there are jobs left to do
	std::cout << "***********************************************" << std::endl;
	std::cout << "[Time Slot: " << time << "]" << std::endl << std::endl;		//print current time slot
			while(i<topOrder.size() && contained(visited, topOrder.at(i)) == true){
			if(i<topOrder.size()){		//all jobs scheduled
				i++;
			}
			if(i >= topOrder.size()){	//all jobs have been scheduled
				std::cout << std::endl << "Scheduling successful!" << std::endl << std::endl;
				return;
			}
			}
if(i<topOrder.size()){

        	if(jobReady(topOrder.at(i), visited, timeSlot, time, i) == true)		{      //if the current job is ready (all required jobs are done)
            	proc1.push_back(topOrder.at(i));        //add to processor 1's list of jobs
            	visited.push_back(topOrder.at(i));      //add job to visited (completed) jobs
		std::cout << "Processor 1: " << jobName.at(topOrder.at(i)) << std::endl << std::endl;
            	timeSlot.insert(std::pair<int, int>(topOrder.at(i), time));     //insert the job number and time slot it was done in
            	i++;        //move to next job
        	}else{
			int j = i;
		while(j<topOrder.size() && jobReady(topOrder.at(j), visited, timeSlot, time, j) == false){
			j++;
		}

            	proc1.push_back(topOrder.at(j));        //add to processor 1's list of jobs
            	visited.push_back(topOrder.at(j));      //add job to visited (completed) jobs
		std::cout << "Processor 1: " << jobName.at(topOrder.at(j)) << std::endl << std::endl;
            	timeSlot.insert(std::pair<int, int>(topOrder.at(j), time));     //insert the job number and time slot it was done in
		
		}
}

if(i >= topOrder.size()){
	std::cout << std::endl << "Scheduling successful!" << std::endl << std::endl;		//return because all jobs are scheduled
	return;
}      
		
if(i<topOrder.size()){

	while(contained(visited, topOrder.at(i)) == true){
			if(i<topOrder.size()){
				i++;
			}
			if(i >=topOrder.size()){
				std::cout << std::endl << "Scheduling successful!" << std::endl << std::endl;  //all jobs have been scheduled
				return;
			}
		}

            if(jobReady(topOrder.at(i), visited, timeSlot, time, i) == true){      //if the current job is ready to be completed
                proc2.push_back(topOrder.at(i));        //add job to processor 2's jobs
                visited.push_back(topOrder.at(i));      //add job to already visited jobs
		std::cout << "Processor 2: " << jobName.at(topOrder.at(i)) << std::endl << std::endl;
                timeSlot.insert(std::pair<int, int>(topOrder.at(i), time));     //insert the job number and time slot it was done
                i++;        // move to next job
            }else{
		int j = i;
		while(j<topOrder.size() && jobReady(topOrder.at(j), visited, timeSlot, time, j) == false){
			j++;
		  }
	if(j<topOrder.size() && contained(visited, topOrder.at(j)) == false){
            proc2.push_back(topOrder.at(j));        //add to processor 2's list of jobs
            visited.push_back(topOrder.at(j));      //add job to visited (completed) jobs
		std::cout << "Processor 2: " << jobName.at(topOrder.at(j)) << std::endl << std::endl;
            timeSlot.insert(std::pair<int, int>(topOrder.at(j), time));     //insert the job number and time slot it was done in
	}
	     }
}

        time++;     //move to next time slot
}
std::cout << "***********************************************" << std::endl;
std::cout << std::endl << "Schedule complete, all jobs have been scheduled" << std::endl << std:: endl;
std::cout << "------------------------------------------------------------------" << std::endl << std::endl;
}

void Graph::checkCycle(int Vs){
    std::map<int, color_t> colors;          //map to hold color for traversing graph
    
    std::map<int, std::vector<int>>::iterator it;           //iterator for list of vertices
    for(it = outgoing.begin(); it!=outgoing.end(); it++){       //traverse list of vertices
        colors.insert(std::pair<int, color_t>(it->first, WHITE));       //mark each vertex as unvisited
    }
        
    if(checkCycleHelp(Vs, colors) == true){     //call recursive function
        std::cout << "Error: There is a cycle...Jobs can not be scheduled" << std::endl;        //print if there is a cycle
    }
    
}

bool Graph::checkCycleHelp(int v, std::map<int, color_t> &colors){
    colors.at(v) = GRAY;        //Color v gray to indicate visited
    int parent =0;      //int to check if one of its incoming vertices (parent) is also an outgoing vertex
    for(int i=0; i<outgoing.at(v).size(); i++){     //for loop to traverse outgoing vertices
        if(colors.at(outgoing.at(v).at(i)) != GRAY){        //if this outgoing vertex has not veen visited
            checkCycleHelp(outgoing.at(v).at(i), colors);       //recursive call with the unvisited node
        }
        else{
            for(int j=0; i<incoming.at(v).size(); i++){         //for loop to traverse v's incoming nodes
                if(incoming.at(v).at(j) == outgoing.at(v).at(i))    //if one of v's incoming is also an outgoing vertex
                    parent = 1;     //mark as cycle
            }
        }
    }
    
    if(parent == 1){        // if there is a cycle
        std::cout << "Error: There is a cycle... Jobs can not be scheduled" << std::endl;   //print error
        std::cout << "Ended with exit code: 1" << std::endl;        // print exit code
        exit(1);        //exit
    }
    return false;       //return false if no cycles
}
