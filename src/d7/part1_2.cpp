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
	struct Node *nxt;
};

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

void find_parent_node(Node *node, std::string pname, std::vector<Node> vec_node)
{

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

void create_node_ll(Node *llnode, std::vector<Node> vec_node)
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
	std::vector<Node> vec_node;

	if (input_file.is_open()) {
		while(getline(input_file, node_str)) {
			Node *node = new Node();
			node->node_str = node_str;
			get_node_attributes(node_str, node);
			vec_node.push_back(node);
		}
	} else {
		std::cout << "error: cannot open file" << std::endl;
		exit(1);
	}

	input_file.close();
	return 0;
}
