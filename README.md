# Program Stack

## Overview

This project involves creating and manipulating a data structure to model program execution through function call stacks. The goal is to work with both trees and graphs representing function call stacks, implementing operations such as loading, adding, removing, and displaying stack data. Additionally, the project includes converting the tree representation into a graph and detecting recursive calls.

## Features

1. **Tree Operations**:
    - **Loading Stacks**: Read a set of program stack snapshots from a text file and form a tree structure.
    - **Adding a Stack**: Add a new program stack to the existing tree.
    - **Removing a Stack**: Remove an existing program stack from the tree.
    - **Displaying the Tree**: Print the tree structure using preorder traversal.
    - **Deleting the Tree**: Free memory and delete the entire tree structure.

2. **Graph Operations**:
    - **Tree to Graph Conversion**: Convert the tree representation into a graph representation.
    - **Displaying the Graph**: Print the graph structure using BFS (Breadth First Search) traversal.
    - **Recursive Call Detection**: Detect recursive calls in the graph.
	
## Note

For the implementation of the project, the use of standard library data structures from STL or similar libraries was not permitted.

## Project Files

- **`UserInteraction.cpp`**: The part of the code responsible for interacting with the user
- **`Tree.cpp`** & **`Tree.hpp`**: Tree class represents a hierarchical structure of program stacks, allowing addition, removal, pre-order traversal and conversion of the tree to a graph.
- **`Graph.cpp`** & **`Graph.hpp`**: Graph class models a directed graph of function calls, allowing the addition of connections, breadth-first traversal and detection of recursion.
- **`Stack.cpp`**: Stack realized as an abstract data structure (temlate class)
- **`Queue.cpp`**: Queue class realized as an abstract data structure (temlate class)
- **`ElemType.cpp`**: Element structure for singly linked list, with "universal" data (template)
- **`Exceptions.cpp`**: This part of the code defines exception classes for error handling.

## Input Data Format

The data file containing stack snapshots follows the format below:
- Each line represents a stack snapshot.
- Function names in each stack are space-separated and ordered from the root function to the current function.

Example of a data file:

``` 
main > a > c > d
main > a > d
main > b > c > c > d
main > b > c > d
main > b > d 
```

## Usage

1. **Compile the Project**: Use your preferred C++ compiler to build the project.
2. **Run the Simulator**: Execute the compiled program. Follow the on-screen menu to load data and perform operations.

## Dependencies

- **C++ Compiler**: Visual Studio 2019 (or newer) is recommended for building this project.

