# project_part_2

This project contains implementations of several searching algorithms:
  * AStar.
  * Best First Search.
  * Depth First Search.
  * Breadth First Search.

Every one of then is getting a matrix which represents a graph and a two point, source and destination, to find a path between them.
The choice of the searching algorithm is made in runtime and can be replaced at runtime.

There are two options to execute the program:
  * Parallel server - using multithreading to search multiple paths in multiple graphs simultaneously.
  * Serial server - search paths in grapths one after another.

Using cache to save solutions from previous executions.
