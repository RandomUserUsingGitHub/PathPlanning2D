# Implementation of the a* algorithm alongside ucs and greedy algorithm
The a* algorithm is an algorithm used to find the best route in a subset of a graph. This algorithm is related to ucs, greedy algorithm and dynamic programming. It helps determine how to reach a target path in an efficient manner. Essentially, this algorithm can be used for pathfinding and finding the best solution to a problem.

In general, the a* algorithm is considered more efficient than ucs and greedy algorithm. However, there are situations where ucs and greedy algorithm are more efficient than the a* algorithm. For instance, if you are only looking for a short path from one node to another, the a* algorithm may not be as efficient as an initialized UC tree. However, for long paths or paths that lead to many nodes, the A*, greedy or random search algorithms may be more efficient.


## Results


![Alt Text](https://media3.giphy.com/media/CkhGkcb1cQ2fxyghjg/giphy.gif?cid=790b7611a5476e1cf37b84460a8e69136cb22c71bf294449&rid=giphy.gif&ct=g)


## Options
<a href="https://freeimage.host/"><img src="https://iili.io/6jILue.png" alt="6jILue.png" border="0"></a>

a* mode - - - - - - - - - - - - -> press **1**\
ucs mode - - - - - - - - - - - -> press **2**\
greedy mode - - - - - - - - -> press **3**\
remove walls - - - - - - - - -> press **w**\
allow  diagonal - - - - - - - -> press **d**\
exit the app -  - - - - - - - - -> press **q**


* Total length from agent to goal, gets calculated (only if there is a possible route)
* Total time taken by the execution of the selected algorithm gets calculated
* You can also set the output ratio and size from the code on Visual.h


Insert gif or link to demo


## Requirements

* [**g++**](https://linuxhint.com/install-and-use-g-on-ubuntu/)
* [**openCv**](https://github.com/RandomUserUsingGitHub/PathPlanning2D/blob/develop/PathPlanning-Visualizer/build_requirement.md)
## Build

To compile and build the code, just put ```make``` in the terminal and press enter.
To clean it up, just type ```make clean``` and you are good to go.
