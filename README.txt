Coffman-Graham Scheduling Algorithm:

Description and Approach: The goal of this program was to implement the Coffman-Graham algorithm for job scheduling. As a basic structure, I created a Graph class to organize the vertices and their edges.
The graph class includes three maps used to keep track of certain attributes of the vertices:

-jobName stores the name for each job corresponding to its number
-outgoing stores the outgoing vertices for each vertex
-incoming stores the incoming vertices for each vertex

There are two different ways to use the main.cpp file to run the CG algorithm. The other way must be commented out. You can either use the program to time the CG algorithm or it can be used to print
a schedule for the inputted jobs. The latter uses a function (accepting two file names as arguments) which will read input files and add the proper edges and vertices to the graph accordingly. Using
the earlier mentioned method will result in a prompt for the user to enter number of vertices, and from there the algorithm will run and instead of printing a schedule it will print the time taken.

After edges and vertices are added, the graph runs a function to check if there are cycles in the graph, because the CG algortihm requires a directed acyclic graph.

The function Schedule() runs the Coffman-Graham algorithm. Within schedule, a version of topological sort is called. This topological sort will develop an ordering for
the Schedule function to use to create the schedule. The scheduling aspect of the function is mainly inside a while loop, where every iteration is a different time slot.
Starting with processor 1, the processor will check if the job at the current place of the ordering is ready. If it is the job will be scheduled for that time slot, if not it will look for the next available job.
If there are no more ready jobs for processor 1, the scheduling is done. If there are no more ready jobs for processor 2, it must determine whether the scheduling is done or if it has to wait for the next time  slot.
Each time slot is printed in a way that shows which processor is running and the job it will complete. To check if a job is "ready" to be scheduled, the function jobReady will check if all of that job's prerequisite
jobs have been completed in a time slot before the current time slot. 

Future Goals:

In the future I would like to clean up my scheduling function to have less statment checking the iterator. There are a few places where blocks of code are repeated, I could
create some additional functions to better organize my code.

Currently, the algorithm only accepts DAGs and will not run if there are cycles or if the graph is not directed. In the future, I would like to implement a way of modifying a graph to get rid of cycles and
form the graph into a DAG.

In addition, it would be interesting to implement this algorithm in a way that would come up with a variety of schedules. This would allow comparison between them, allowing us to determine which schedule is ideal.
Whereas my current project only gives one possible schedule.

Lastly, an improvement I would make upon this project would be to add additional processors. It would be interesting to see how the schedule and the time taken to schedule vary
based on the number of processors.

