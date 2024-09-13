#ifndef GRAPH_HPP
#define GRAPH_HPP

#include "ElemType.hpp"
#include <string>
using namespace std;


struct GraphNode {
	string name = "";							// functon name
	Elem<GraphNode*>* adjacent = nullptr;		// a list of adjacent nodes
	GraphNode* next = nullptr;					// a link to the next node
};

class Graph {
public:
	Graph();
	~Graph();

	void addConnection(const string& from, const string& to);		// Adds a link between two nodes

	string graphBFS();						// Traverses the graph (BFS algorithm)
	bool detectRecursion();					// Detects recursion of function calls

private:
	GraphNode* nodes_;						// The first graph node in the list
	GraphNode* last_node_;					// The last graph node added in the list
};

#endif