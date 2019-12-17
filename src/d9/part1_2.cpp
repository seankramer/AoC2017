#include <fstream>
#include <iostream>

int main(int argc, char **argv)
{
	std::ifstream input_file(argv[1]);
	if (!input_file.is_open()) {
		std::cout << "error: cannot open file" << std::endl;
		exit(1);
	}

	std::string line;
	bool gflg = false;
	int sz = 0, cmplnest = 0, nest = 0;
	std::getline(input_file, line);
	while (sz <= line.size()) {
		switch (line[sz]) {
			case '{':
				if (gflg) {
					break;
				} else {
					nest++;
					break;
				}
			case '}':
				if (gflg) {
					break;
				} else {
					cmplnest += nest;
					if (nest > 0)
						nest--;
					break;
				}
			case '<':
				gflg = true;
				break;
			case '>':
				gflg = false;
				break;
			case '!':
				sz++;
				break;
			default:
				break;
		}
		sz++;
	}
	std::cout << "complete nests: " << cmplnest << std::endl;
	return 0;
}