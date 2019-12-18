#include <vector>
#include <numeric>
#include <fstream>
#include <sstream>
#include <iostream>

// #define EXAMPLE
#define TEST_LEN 5
#define MAX_LEN 256

void populate_vec_rev(std::ifstream& infile, std::vector<int>& vec)
{
	std::string line;
	getline(infile, line);
	std::stringstream ss(line);

	for (int i = 0; ss >> i;) {
		vec.push_back(i);
		if (ss.peek() == ',')
			ss.ignore();
	}
}

int main(int argc, char **argv)
{
	std::ifstream input_file(argv[1]);
	if (!input_file.is_open()) {
		std::cout << "error: file cannot be opened" << std::endl;
		exit(1);
	}

	int ndx = 0, ldex, hdex;;
	std::vector<int> vec_rev;

#ifdef EXAMPLE
	std::vector<int> n_seq(TEST_LEN);
#else
	std::vector<int> n_seq(MAX_LEN);
#endif

	populate_vec_rev(input_file, vec_rev);
	std::iota(n_seq.begin(), n_seq.end(), 0);

	for (int i = 0; i < vec_rev.size(); i++) {
		for (int j = 0; j < vec_rev[i] / 2; j++) {
			ldex = (ndx + j) % n_seq.size();
			hdex = (ndx + vec_rev[i] - 1 - j) % n_seq.size();
			std::swap(n_seq[ldex], n_seq[hdex]);
		}
		ndx += vec_rev[i] + i;
	}
	std::cout << "part 1 -> " << n_seq[0] * n_seq[1] << std::endl;



	input_file.close();
	return 0;
}