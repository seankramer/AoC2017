#include <map>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <functional>

#if 0
std::map<std::string, std::function<bool(int, int)> > cmp_map =
{
    {"==", std::equal_to<int>()},
    {"!=", std::not_equal_to<int>()},
    {">", std::greater<int>()},
    {">=", std::greater_equal<int>()},
    {"<", std::less<int>()},
    {"<=", std::less_equal<int>()}
};
#endif

int main(int argc, char **argv)
{
	std::string in_str;
	std::ifstream input_file(argv[1]);

    int op_val, cmp_val, max_val = 0;
    std::string reg, op, chreg, cmp;
    std::map<std::string, int> reg_data;

	if (input_file.is_open()) {
		while(getline(input_file, in_str)) {
            std::stringstream ss(in_str);
            ss >> reg >> op >> op_val;
		}
	} else {
		std::cout << "error: cannot open file" << std::endl;
		exit(1);
	}
	return 0;
}
