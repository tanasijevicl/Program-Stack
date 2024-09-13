#include "Graph.hpp"
#include "Queue.hpp"

Graph::Graph() {
	nodes_ = nullptr;
	last_node_ = nullptr;
}

Graph::~Graph() {
	// Delete all graph nodes
	while (nodes_) {
		GraphNode* curr = nodes_;
		nodes_ = nodes_->next;

		// Delete all adjacent nodes
		Elem<GraphNode*>* adj = curr->adjacent;
		while (adj != nullptr) {
			Elem<GraphNode*>* tmp = adj;
			adj = adj->next;
			delete tmp;
		}
		
		delete curr;
	}
}

void Graph::addConnection(const string& from, const string& to) {
	GraphNode* node_from = nullptr;
	GraphNode* node_to = nullptr;

	// Try to find nodes of connection
	for (GraphNode* node = nodes_; node != nullptr; node = node->next) {
		if (node->name == from) node_from = node;
		if (node->name == to) node_to = node;
		if (node_from && node_to) break;
	}
	
	// If the nodes are not found, create them and add them to the list of nodes  
	if (node_from == nullptr) {
		node_from = new GraphNode();
		node_from->name = from;

		// If it's the first node "update" nodes_
		if (nodes_ == nullptr) {
			nodes_ = last_node_ = node_from;
		}
		// Else add behind last node
		else {
			last_node_->next = node_from;
			last_node_ = last_node_->next;
		}
	}
	if (node_to == nullptr) {
		node_to = new GraphNode();
		node_to->name = to;
		last_node_->next = node_to;
		last_node_ = last_node_->next;
	}

	// Find last adjacent node
	Elem<GraphNode*>* last_adj = nullptr;
	for (Elem<GraphNode*>* adj = node_from->adjacent; adj != nullptr; adj = adj->next) {
		if (adj->t == node_to) return;
		last_adj = adj;
	}

	// Add conection after last adjacent node
	if (last_adj) {
		last_adj->next = new Elem<GraphNode*>();
		last_adj->next->t = node_to;
	}
	else {
		node_from->adjacent = new Elem<GraphNode*>();
		node_from->adjacent->t = node_to;
	}
}


string Graph::graphBFS() {
	if (nodes_ == nullptr) return "";

	string bst = "";
	Elem<GraphNode*>* visited_nodes = nullptr;
	Elem<GraphNode*>* last_visited = nullptr;
	Queue<GraphNode*>* que = new Queue<GraphNode*>();
	que->insert(nodes_);

	while (!que->empty()) {
		// Take one node frome the que
		GraphNode* curr = que->remove();
		bool visited = false;
		
		// Check if that node is visited
		if (visited_nodes) {
			for (Elem<GraphNode*>* tmp = visited_nodes; tmp != nullptr; tmp = tmp->next) {
				if (curr == tmp->t) {
					visited = true;
					break;
				}
			}
			// Continue with the next knot if it is visited
			if (visited) continue;
		}

		// Add current node to the list of visited nodes
		if (visited_nodes) {
			last_visited->next = new Elem<GraphNode*>();
			last_visited = last_visited->next;
		}
		else {
			visited_nodes = last_visited = new Elem<GraphNode*>();
		}
		last_visited->t = curr;

		// Add node name to the string
		bst += curr->name + " -> ";

		// Add all adjacent nodes to the que
		for (Elem<GraphNode*>* tmp = curr->adjacent; tmp != nullptr; tmp = tmp->next) que->insert(tmp->t);
	}

	return bst.erase(bst.length() - 4, 4);
}

bool Graph::detectRecursion() {
	if (nodes_ == nullptr) return false;

	Elem<GraphNode*>* visited_nodes = nullptr;
	Elem<GraphNode*>* last_visited = nullptr;
	Queue<GraphNode*>* que = new Queue<GraphNode*>();
	que->insert(nodes_);

	while (!que->empty()) {
		// Take one node frome the que
		GraphNode* curr = que->remove();
		bool visited = false;

		// Check if that node is visited, if so a recursion is detected
		if (visited_nodes) {
			for (Elem<GraphNode*>* tmp = visited_nodes; tmp != nullptr; tmp = tmp->next) {
				if (curr == tmp->t) {
					return true;
				}
			}
		}
		
		// Add current node to the list of visited nodes
		if (visited_nodes) {
			last_visited->next = new Elem<GraphNode*>();
			last_visited = last_visited->next;
		}
		else {
			visited_nodes = last_visited = new Elem<GraphNode*>();
		}
		last_visited->t = curr;

		// Add all adjacent nodes to the que
		if (curr) for (Elem<GraphNode*>* tmp = curr->adjacent; tmp != nullptr; tmp = tmp->next) que->insert(tmp->t);
	}

	// If all nodes are visited return false (recursion is not detected)
	return false;
}
