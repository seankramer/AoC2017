#include <vector>
#include <numeric>
#include <fstream>
#include <sstream>
#include <iostream>

#define TEST_LEN 10
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

int rev_sublist(std::vector<int>& vec, int rev_len, int& ndx, int skip)
{
	std::cout << ndx << " & " << rev_len << std::endl;
	for (int i = 0; i <= rev_len / 2; i++) {
		if (ndx + i <= vec.size())
			std::swap(vec[(rev_len / 2) - i], vec[(rev_len / 2) + i]);
		else
			exit(1);
	}

	for (int i = 0; i < vec.size(); i++)
		std::cout << vec[i] << "; ";
	std::cout << std::endl << std::endl;
	return rev_len + skip;
}

int main(int argc, char **argv)
{
	std::ifstream input_file(argv[1]);
	if (!input_file.is_open()) {
		std::cout << "error: file cannot be opened" << std::endl;
		exit(1);
	}

	int skip = 0, ndx = 0;
	std::vector<int> vec_rev;
	std::vector<int> n_seq(MAX_LEN);
	populate_vec_rev(input_file, vec_rev);
	std::iota(n_seq.begin(), n_seq.end(), 0);

	// for (int i = 0; i < n_seq.size(); i++)
	// 	std::cout << n_seq[i] << "; ";
	// std::cout << std::endl << std::endl;

	for (int i = 0; i < vec_rev.size(); i++) {
		ndx += rev_sublist(n_seq, vec_rev[i], ndx, skip);
		skip++;
	}

	input_file.close();
	return 0;
}