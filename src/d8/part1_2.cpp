#include <map>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>

int main(int argc, char **argv)
{
	std::string insn;
	std::ifstream input_file(argv[1]);

	if (input_file.is_open()) {
		while(getline(input_file, insn)) {
			std::cout << insn << std::endl;
		}
	} else {
		std::cout << "error: cannot open file" << std::endl;
		exit(1);
	}
	return 0;
}