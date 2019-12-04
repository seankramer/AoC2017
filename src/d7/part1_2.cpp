#include <utility>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>

#define DEBUG
#define ARROW_DELIM "->"

struct Node
{
	int weight;
	int lvl_weight;
	std::string name;
	std::vector<std::string> vec_chld;
};

#ifdef DEBUG
void print_node(Node *node)
{
	std::cout << node->name << " (" << node->weight << ")" << std::endl;
	for (auto str : node->vec_chld)
		std::cout << "    " << str << std::endl;
	std::cout << std::endl << std::endl;
}

// void print_vectors(std::vector<Node*> cnode, std::vector<Node*> pnode)
void print_vectors(std::vector<Node*> pnode)
{
	// for (auto& c : cnode)
	// 	std::cout << c->name << std::endl;
	// std::cout << std::endl;

	for (auto& p : pnode)
		std::cout << p->name  << " " << p->weight << std::endl;
	std::cout << std::endl;
}

void print_parent_vector(std::vector<Node*> pnode)
{
	for (auto& nd : pnode) {
		std::cout << nd->name << " (" << nd->weight  << ") -> ";
		for (auto chld : nd->vec_chld)
			std::cout << chld << "; ";
		std::cout << std::endl;
	}
}
#endif

std::pair<Node*, int> link_nodes(std::vector<Node*> vec_cnode, std::string cname)
{
	int ndx = 0;
	for (auto& cnode : vec_cnode) {
		if (cname.compare(cnode->name) == 0)
			return std::make_pair(cnode, ndx);
		ndx++;
	}
	return std::make_pair(nullptr, -1);
}

void get_attrib(std::string node_str, Node *node)
{
	int st_paren, end_paren;
	st_paren = node_str.find("(") + 1;
	end_paren = node_str.find(")");
	std::stringstream ss(node_str.substr(st_paren, end_paren - st_paren));
	ss >> node->weight;
	node->lvl_weight = 0;
	node->name = node_str.substr(0, node_str.find(' '));
}

std::vector<std::string> get_chld_names(std::string node_str)
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
	std::vector<Node*> pnode, cnode;

	if (input_file.is_open()) {
		while(getline(input_file, node_str)) {
			Node *node = new Node();
			get_attrib(node_str, node);
			node->vec_chld = get_chld_names(node_str);
			(node->vec_chld.empty()) ? cnode.push_back(node) : pnode.push_back(node);

		}
	} else {
		std::cout << "error: cannot open file" << std::endl;
		exit(1);
	}

	while (!pnode.empty()) {
		Node *node = pnode.front();
		std::pair<Node*, int> cnode_pair;
		std::cout << node->name << " (" << node->weight  << ")" << std::endl;

		while (!node->vec_chld.empty()) {
			std::string chld = node->vec_chld.front();
			cnode_pair = link_nodes(cnode, chld);

			if (cnode_pair.first != nullptr) {
				// if (node->lvl_weight == 0) {
				// 	node->lvl_weight = cnode_pair.first->weight;
				// } else if (node->lvl_weight != cnode_pair.first->weight) {
				// 	std::cout << node->name << " " << node->lvl_weight << " != ";
				// 	std::cout << cnode_pair.first->name << " ";
				// 	std::cout << cnode_pair.first->weight << std::endl;
				// }
				node->weight += cnode_pair.first->weight;
				std::cout << "    " << cnode_pair.first->name << " (";
				std::cout << cnode_pair.first->weight << ")" << std::endl;
				cnode.erase(cnode.begin() + cnode_pair.second);
				node->vec_chld.erase(node->vec_chld.begin());
			} else {
				pnode.push_back(node);
				std::cout << "    child node not found" << std::endl;
				break;
			}
		}
		if (node->vec_chld.empty())
			cnode.push_back(node);

		if (pnode.size() == 1)
			std::cout << "king node: " << node->name << std::endl;
		pnode.erase(pnode.begin());
	}

	input_file.close();
	return 0;
}
