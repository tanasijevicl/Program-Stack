#include "Tree.hpp"
#include "Graph.hpp"
#include "Exceptions.hpp"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main() {
	int option = 0;
	
	Tree* tree = nullptr;
	Graph* graph = nullptr;
	
	while (1) {
		// Print options
		cout << "------------------------------------------------------------------" << endl;
		cout << "Options:" << endl;
		cout << "1. Form the tree (load stacks)" << endl;
		cout << "2. Add a program stack" << endl;
		cout << "3. Remove a program stack" << endl;
		cout << "4. Print the tree" << endl;
		cout << "5. Delete the tree" << endl;
		cout << "6. Convert the tree into the graph" << endl;
		cout << "7. Print the graph" << endl;
		cout << "8. Detect recursion" << endl;
		cout << "0. Exit" << endl;
		cout << "Please chose an option (enter a number): ";
		cin >> option;
		cout << "------------------------------------------------------------------" << endl;

		// Check if the input is good
		if (cin.fail()) {
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cout << "Invalid input. Please enter a valid integer." << endl;
			continue;
		}

		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		string str = "";

		try {
			// Check if the conditions are met to perform the option
			if (tree == nullptr && option != 1 && option != 0 && option != 7 && option != 8) throw InvalidUserInput("Tree is not formed!");
			if (graph == nullptr && (option == 7 || option == 8)) throw InvalidUserInput("Graph is not formed!");

			switch (option)
			{
			case 1: {
				cout << "Enter file name: ";

				cin >> str;
				fstream input_file(str, ios::in);

				if (input_file.is_open()) {
					if (tree) delete tree;
					tree = new Tree();
					while (getline(input_file, str)) {
						tree->addProgramStack(str);
					}
					input_file.close();
				}
				else throw InvalidUserInput("File not found!");

				cout << "The tree is successfully formed" << endl;
				break;
			}
			case 2:
				cout << "Please enter stack: ";
				getline(cin, str);
				tree->addProgramStack(str);
				cout << "The program stack successfully added" << endl;
				break;
			case 3:
				cout << "Please enter stack: ";
				getline(cin, str);
				tree->removeProgramStack(str);
				cout << "The program stack successfully removed" << endl;
				break;
			case 4:
				str = tree->treePreorder();
				cout << str << endl;
				break;
			case 5:
				delete tree;
				tree = nullptr;
				cout << "The tree is successfully deleted" << endl;
				break;
			case 6:
				graph = tree->treeToGraph();
				if (graph) cout << "The graph is successfully formed" << endl;
				else cout << "The graph is not formed, tree does not have a program stack" << endl;
				break;
			case 7:
				str = graph->graphBFS();
				cout << str << endl;
				break;
			case 8: {
				bool recursion = true;
				recursion = graph->detectRecursion();
				if (recursion) cout << "Recursion exist" << endl;
				else cout << "Recursion does not exist" << endl;
				break;
			}
			case 0:
				if (tree) delete tree;
				if (graph) delete graph;
				exit(0);
			default:
				cout << "Option doesn't exist." << endl;
			}
		}
		catch (InvalidUserInput error) {
			cout << error.what() << endl;
		}
		catch (InvalidStackFormat error) {
			cout << error.what() << endl;
		}
	}
	
	return 0;
}