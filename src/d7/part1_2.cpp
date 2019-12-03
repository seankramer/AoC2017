#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <boost/algorithm/string.hpp>

#define ARROW_DELIM "->"

struct Node
{
	int weight;
	std::string name;
	std::string node_str;
	// std::vector<std::string> child_name;
	struct Node *nxt;
};

#ifdef NO_LINKEDLIST
void get_child_nodes(std::string node_str, std::vector<std::string>& names)
{
	int arr_pos = node_str.find(ARROW_DELIM);
	if (arr_pos > 0) {
		std::stringstream ss(node_str.substr(arr_pos + sizeof(ARROW_DELIM)));
		while(ss.good()) {
			std::string substr;
			getline(ss, substr, ',');
			boost::trim_left(substr);
			names.push_back(substr);
		}
	}
}

void get_node_attributes(std::string node_str, Node& node)
{
	int st_paren, end_paren;
	st_paren = node_str.find("(") + 1;
	end_paren = node_str.find(")");
	std::stringstream ss(node_str.substr(st_paren, end_paren - st_paren));
	ss >> node.weight;
	node.name = node_str.substr(0, node_str.find(' '));
}

void find_root_node(std::string node_name, std::vector<Node>& nodes)
{
	for (auto it = begin(nodes); it != end(nodes); ++it) {
		if (!(*it).child_name.empty()) {
			for (auto jt = begin((*it).child_name); jt != end((*it).child_name); ++jt) {

			}
		}
	}
}
#endif

// Node find_parent_node(std::string pname, std::vector<Node*> vec_node)
// {
// 	Node node;
// 	for (auto it = vec_node.begin(); it != vec_node.end(); ++it) {
// 		if (pname.compare((*it)->name) == 0) {
// 			std::cout << (*it)->name << std::endl;
// 			return *(*it);
// 		}
// 	}
// 	return node;
// }

void find_parent_node(Node *node, std::string pname, std::vector<Node*> vec_node)
{
	for (auto it = vec_node.begin(); it != vec_node.end(); ++it) {
		if (pname.compare((*it)->name) == 0) {
			std::cout << (*it)->name << std::endl;
			node = *it;
			// return *(*it);
		}
	}
	// return node;
}

void get_node_attributes(std::string node_str, Node *node)
{
	int st_paren, end_paren;
	st_paren = node_str.find("(") + 1;
	end_paren = node_str.find(")");
	std::stringstream ss(node_str.substr(st_paren, end_paren - st_paren));
	ss >> node->weight;
	node->name = node_str.substr(0, node_str.find(' '));
	node->nxt = NULL;
}

void create_node_ll(Node *llnode, std::vector<Node*> vec_node)
{
	std::vector<std::string> nxt_name;
	int arr_pos = llnode->node_str.find(ARROW_DELIM);
	if (arr_pos <= 0) {
		return;
	} else {
		std::stringstream ss(llnode->node_str.substr(arr_pos + sizeof(ARROW_DELIM)));
		while(ss.good()) {
			std::string sbstr;
			getline(ss, sbstr, ',');
			boost::trim_left(sbstr);
			nxt_name.push_back(sbstr);
		}
	}

	std::cout << "llnode: " << llnode->name << std::endl;
	for (int i = 0; i < nxt_name.size(); i++) {
		Node *node = NULL;
		node = new Node();
		find_parent_node(node, nxt_name[i], vec_node);
		// std::cout << nxt_name[i] << std::endl;
		// Node node = find_parent_node(nxt_name[i], vec_node);
		std::cout << "node.name: " << node->name << std::endl << std::endl;
		// if (node != NULL) {
			// std::cout << llnode->name << std::endl;
			// std::cout << node->name << std::endl;
			// node->nxt = llnode;
			// llnode = node;
		// }
	}
}

void printList(Node *node)  
{  
    while (node != NULL) {  
        std::cout << node->name << " -> ";  
        node = node->nxt;  
    }
    std::cout << std::endl;
}

int main(int argc, char **argv)
{
	std::string node_str;
	std::ifstream input_file(argv[1]);
	std::vector<Node*> vec_node;

	if (input_file.is_open()) {
		while(getline(input_file, node_str)) {
			Node *node = new Node();
			vec_node.push_back(node);
			node->node_str = node_str;
			get_node_attributes(node_str, node);
			// get_child_nodes(node_str, node.child_name);
			// vec_node.push_back(node);
		}
	} else {
		std::cout << "error: cannot open file" << std::endl;
		exit(1);
	}

	for (auto it = begin(vec_node); it != end(vec_node); ++it)
		create_node_ll((*it), vec_node);
	std::cout << std::endl;

#ifdef PRINT_NODE_DATA
	for (auto it = begin(vec_node); it != end(vec_node); ++it) {
		std::cout << (*it).name << " (" << (*it).weight << ") ";
		if (!(*it).child_name.empty()) {
			std::cout << "-> ";
			for (auto jt = begin((*it).child_name); jt != end((*it).child_name); ++jt)
				std::cout << *jt << "; ";
		}
		std::cout << std::endl;
	}
#endif

#ifdef NO_LINKEDLIST
	for (auto it = begin(vec_node); it != end(vec_node); ++it)
		find_root_node((*it).name, vec_node);
#endif

	// for (auto it = begin(vec_node); it != end(vec_node); ++it)
	// 	printList((*it));

	input_file.close();
	return 0;
}
