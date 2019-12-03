#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

struct node
{
    int weight;
    std::string name;
    std::vector<std::string> child_name;
};

node populate_node(std::string node_str)
{
    node single_node;
#if 0
    std::string delimiter = "->";
    size_t pos = 0;
    std::string token;
    while ((pos = node_str.find(delimiter)) != std::string::npos) {
        token = node_str.substr(0, pos);
        std::cout << token << std::endl;
        node_str.erase(0, pos + delimiter.length());
    }
    std::cout << node_str << std::endl;
#endif
    return single_node;
}

int main(int argc, char **argv)
{
    std::string node_str;
    std::ifstream input_file(argv[1]);
    std::vector<node> vec_node;
    if (input_file.is_open()) {
        while(getline(input_file, node_str)) {
            vec_node.push_back(populate_node(node_str));
        }
    } else {
        std::cout << "error: cannot open file" << std::endl;
        exit(1);
    }

    input_file.close();
    return 0;
}
