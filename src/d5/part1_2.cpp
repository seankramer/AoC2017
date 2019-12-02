#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>

void jump_trace(std::vector<int> vec_jmp)
{
	int steps = 0, ndx = 0, nxt_ndx = 0;
	while (ndx < vec_jmp.size()) {
		steps++;
		nxt_ndx += vec_jmp[ndx];
#define PART2
#ifdef PART2
		// part 2 -- complete
		if (vec_jmp[ndx] < 3)
			vec_jmp[ndx]++;
		else
			vec_jmp[ndx]--;
#else
		// part 1 -- complete
		vec_jmp[ndx]++;
#endif
		ndx = nxt_ndx;
	}
	std::cout << "steps: " << steps << std::endl << std::endl;

}

int main(int argc, char **argv)
{
	int jval;
	std::vector<int> vec_jmp;
	std::string joffset;
	std::ifstream input_file(argv[1]);

	if (input_file.is_open()) {
		while(getline(input_file, joffset)) {
			std::stringstream(joffset) >> jval;
			vec_jmp.push_back(jval);
		}
	} else {
		std::cout << "error: file not opened" << std::endl;
		exit(1);
	}

	jump_trace(vec_jmp);
	input_file.close();
	return 0;
}
