#include <vector>
#include <iterator>
#include <algorithm>
#include <sstream>
#include <fstream>
#include <iostream>

std::vector<int> bank_data(std::string bank_str)
{
	int val;
	std::vector<int> mem_banks;
	std::stringstream str(bank_str);

	while(str) {
		str >> val;
		if (!str)
			break;
		else
			mem_banks.push_back(val);
	}
	return mem_banks;
}

void disperse_blocks(std::vector<int>& mem_banks)
{
	int ndx, sum = 0;
	int max_bank = *std::max_element(begin(mem_banks), end(mem_banks));

	for (ndx = 0; ndx < mem_banks.size(); ndx++)
		if (mem_banks[ndx] == max_bank)
			break;

	mem_banks[ndx] = 0;
	while (max_bank != 0) {
		ndx += 1;
		if (ndx == mem_banks.size())
			ndx = 0;
		mem_banks[ndx]++;
		max_bank--;
	}
}

int unique_set(std::vector<std::vector<int>> sets, std::vector<int> mem_banks)
{
	int matches;
	for (int i = 0; i < sets.size(); i++) {
		matches = 0;
		for (int j = 0; j < sets[i].size(); j++) {
			if (mem_banks[j] == sets[i][j])
				matches++;
		}
		if (matches == mem_banks.size())
			return i;
	}
	return 0;
}

int main(int argc, char **argv)
{
	bool match = false;
	int bank_val, cycles = 0, repeat_cycles = 0;
	std::vector<int> mem_banks;
	std::vector<std::vector<int>> sets;
	std::string bank_str;
	std::ifstream input_file(argv[1]);

	if (input_file.is_open()) {
		getline(input_file, bank_str);
		mem_banks = bank_data(bank_str);
	} else {
		std::cout << "error: file not opened" << std::endl;
		exit(1);
	}
	sets.push_back(mem_banks);

	// part 1 -- complete
	while (!match) {
		disperse_blocks(mem_banks);
		cycles++;
		if (unique_set(sets, mem_banks))
			break;
		sets.push_back(mem_banks);
	}
	std::cout << "cycles: " << cycles << std::endl;

#define PART2
#ifdef PART2
	// part 2 -- complete
	std::vector<int> input_data;
	for (int i = 0; i < mem_banks.size(); i++) 
		input_data.push_back(mem_banks[i]);
	repeat_cycles = unique_set(sets, input_data);
	std::cout << "repeat cycles: " << cycles - repeat_cycles << std::endl;
#endif

	input_file.close();
	return 0;
}