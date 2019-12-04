#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>

#define ARROW_DELIM "->"

struct Node
{
	int weight;
    int length;
	std::string name;
    std::vector<std::string> vec_chld;
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

void get_node_attributes(std::string node_str, Node& node)
{
	int st_paren, end_paren;
	st_paren = node_str.find("(") + 1;
	end_paren = node_str.find(")");
	std::stringstream ss(node_str.substr(st_paren, end_paren - st_paren));
	ss >> node.weight;
    node.length = 1;
	node.name = node_str.substr(0, node_str.find(' '));
	node.nxt = NULL;
}

std::vector<std::string> get_children(std::string node_str)
{
	std::vector<std::string> nxt_name;
    int arr_pos = node_str.find(ARROW_DELIM);
    if (arr_pos > 0) {
		std::stringstream ss(node_str.substr(arr_pos + sizeof(ARROW_DELIM)));
		while(ss.good()) {
			std::string sbstr;
			getline(ss, sbstr, ',');
            sbstr.erase(std::remove(sbstr.begin(), sbstr.end(), ' '), sbstr.end());
			nxt_name.push_back(sbstr);
		}
	}
    return nxt_name;
}

int main(int argc, char **argv)
{
	std::string node_str;
	std::ifstream input_file(argv[1]);
    std::vector<Node> pnode, cnode;
	Node node;

	if (input_file.is_open()) {
		while(getline(input_file, node_str)) {
			get_node_attributes(node_str, node);
            node.vec_chld = get_children(node_str);
            if (node.vec_chld.empty())
                cnode.push_back(node);
            else
                pnode.push_back(node);
		}
	} else {
		std::cout << "error: cannot open file" << std::endl;
		exit(1);
	}

    while (!cnode.empty()) {
        Node nit = cnode.front();
        std::cout << nit.name << " (" << nit.weight  << ")" << std::endl;
        cnode.erase(cnode.begin());
    }

	input_file.close();
	return 0;
}
