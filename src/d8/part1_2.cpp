#include <fstream>
#include <sstream>
#include <iostream>
#include <functional>
#include <unordered_map>

std::unordered_map<std::string, std::function<bool(int, int)>> const cmpr
{
	{
		{"==", std::equal_to<void>()},
		{"!=", std::not_equal_to<void>()},
		{"<=", std::less_equal<void>()},
		{"<", std::less<void>()},
		{">=", std::greater_equal<void>()},
		{">", std::greater<void>()}
	}
};

int main(int argc, char **argv)
{
	std::ifstream input_file(argv[1]);
	if (!input_file.is_open()) {
		std::cout << "error: cannot open file" << std::endl;
		exit(1);
	}

	std::string in_str;
	int op_val, cmp_val, p1mx = 0, p2mx = 0;
	std::string reg, op, cmp_reg, cmp;
	std::unordered_map<std::string, int> reg_data;

	while(getline(input_file, in_str)) {
		std::stringstream ss(in_str);
		ss >> reg >> op >> op_val >> cmp_reg >> cmp_reg >> cmp >> cmp_val;
		op_val = (op == "dec") ? op_val * -1 : op_val;
		if (cmpr.at(cmp)(reg_data[cmp_reg], cmp_val)) {
			reg_data[reg] += op_val;
			p2mx = (reg_data[reg] > p2mx) ? reg_data[reg] : p2mx;
		}
	}

	std::unordered_map<std::string, int>::iterator it = reg_data.begin();
	while (it != reg_data.end()) {
		p1mx = (it->second > p1mx) ? it->second : p1mx;
		it++;
	}

	std::cout << "part 1: " << p1mx << std::endl;
	std::cout << "part 2: " << p2mx << std::endl;

	return 0;
}
