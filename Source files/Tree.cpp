#include "Tree.hpp"
#include "Stack.hpp"
#include "Exceptions.hpp"
#include <iostream>
using namespace std;

Tree::Tree() {
	this->root_ = nullptr;
};

Tree::~Tree() {
	if (root_ == nullptr) return;
	Queue<Node*>* que = new Queue<Node*>;
	que->insert(root_);
	
	while (!que->empty()) {
		// Take one node frome the que
		Node* curr = que->remove();
		
		// Add brother and child to the queue
		if (curr->brother) que->insert(curr->brother);
		if (curr->child) que->insert(curr->child);

		// Delete current node
		delete curr;
	}

	delete que;
};

Queue<string>* Tree::readString(const string& str) {
	int i = 0;
	Queue<string>* que = new Queue<string>();

	while (i < str.size()) {
		string function_name = "";

		// Read character by character until separator
		while (i < str.size() && str[i] != ' ') {
			function_name += str[i];
			i++;
		}

		// Add function name to the queue
		if (!function_name.empty()) {
			que->insert(function_name);
		}

		// Skip characters
		while (i < str.size() && (str[i] == ' ' || str[i] == '>')) i++;
	}
	return que;
}

Node* Tree::findNode(Queue<string>* que) {
	string function_name = que->readNext();

	// Check stack format
	if (!root_) {
		return nullptr;
	}
	else if (root_->name != function_name) {
		throw InvalidStackFormat("Main function is not the same!");
	}

	Node* old = root_;
	Node* curr = root_->child;
	que->remove();

	// Read the firts node of the path from the que
	function_name = que->readNext();

	while (curr) {
		// If function names match move on to the son		
		if (curr->name == function_name) {
			old = curr;
			curr = curr->child;
			
			// Remove the current function from the queue and read the next one 
			que->remove();
			function_name = que->readNext();
		}
		// Else move on to the brother
		else {
			curr = curr->brother;
		}
	}
	
	// Return last node found on path
	return old;
}


void Tree::addProgramStack(const string& str) {
	Queue<string>* que = readString(str);

	try {
		if (que->empty()) {
			delete que;
			return;
		}
		Node* curr = findNode(que);

		// If it is the first program stack, add it as a root
		if (!root_) {
			root_ = new Node();
			root_->name = que->remove();
			curr = root_;
		}

		// Add new nodes from the que to the tree
		while (!que->empty()) {
			if (curr->child) {
				curr = curr->child;
				while (curr->brother != nullptr) {
					curr = curr->brother;
				}
				curr->brother = new Node();
				curr = curr->brother;
			}
			else {
				curr->child = new Node();
				curr = curr->child;
			}
			curr->name = que->remove();
		}
		delete que;
	}
	catch (Underflow) {
		delete que;
		return;
	}
};


void Tree::removeProgramStack(const string& str) {
	if (root_ == nullptr) throw InvalidUserInput("Stack does not exist!");

	Queue<string>* que = readString(str);
	if (que->empty()) {
		delete que;
		return;
	}

	Stack<Node*>* stack = new Stack<Node*>();
	Node* curr = root_;
	// Take the firts node of the path from the que
	string function_name = que->remove();

	// Find the path and add nodes to the stack
	while (curr) {
		if (curr->name == function_name) {
			stack->push(curr);
			curr = curr->child;
			if (!que->empty()) function_name = que->remove();
		}
		else {
			curr = curr->brother;
		}
	}

	// If the queue is not empty, the stack is not found
	if (!que->empty()) {
		delete que;
		delete stack;
		throw InvalidUserInput("Program stack does not exist!");
	}

	while (!stack->empty()) {
		// Take the node from the stack
		curr = stack->pop();

		// If the node has children, the deletion is completed
		if (curr->child != nullptr) return;

		if (curr != root_) {
			Node* father = stack->readTop();

			// Unlink the current node properly
			if (curr == father->child) {
				father->child = curr->brother;
			}
			else {
				Node* tmp = father->child;
				while (tmp->brother != curr) tmp = tmp->brother;
				tmp->brother = curr->brother;
			}
		}

		// Delete the current node
		delete curr;
	}

	delete que;
	delete stack;
	return;
};


string Tree::treePreorder() {

	if (!root_) return "";

	// Start from the root
	Node* curr = root_;
	Stack<Node*>* stack = new Stack<Node*>;
	string preorder = "";

	while (curr) {
		// Add node name to the string
		preorder += curr->name + " -> ";
		
		// Add all brothers to the stack
		if (curr->brother != nullptr) {
			stack->push(curr->brother);
		}

		// Move on to the child node
		curr = curr->child;

		// If the child node does not exist, take the node from the stack
		if (curr == nullptr) {
			if (!stack->empty()) curr = stack->pop();
		}
	}
	
	delete stack;
	return preorder.erase(preorder.length() - 4, 4);
}

Graph* Tree::treeToGraph() {
	if (root_ == nullptr) return nullptr;
	Graph* graph = new Graph();
	Queue<Node*>* que = new Queue<Node*>();
	Node* father = nullptr;

	que->insert(root_);

	while (!que->empty()) {
		// Take the node from the queue
		Node* curr = que->remove();
		
		// Move on to the child node
		father = curr;
		curr = curr->child;

		// For every child add the connection father-child
		while (curr != nullptr) {
			graph->addConnection(father->name, curr->name);

			// Add current node to the queue
			que->insert(curr);
			curr = curr->brother;
		}
	}

	delete que;
	return graph;
};