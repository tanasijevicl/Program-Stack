#ifndef TREE_HPP
#define TREE_HPP

#include "Queue.hpp"
#include "Graph.hpp"
#include <string>
using namespace std;

struct Node {
	string name = "";					// function name
	Node* brother = nullptr;			// the next node with the same parenth
	Node* child = nullptr;				// first child node
};

class Tree {
public:
	Tree();
	~Tree();

	void addProgramStack(const string& str);				// Adds a program stack to the tree
	void removeProgramStack(const string& str);				// Removes a program stack from the tree
	string treePreorder();									// Traverses the tree in pre-order
	Graph* treeToGraph();									// Converts the tree into the graph

private:
	Queue<string>* readString(const string& str);			// Processes a string and returns pointer to the queue with function names
	Node* findNode(Queue<string>* que);						// Finds the node to witch the rest of the stack should be added

	Node* root_;											// The root of the tree
};

#endif