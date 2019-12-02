#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>
#include <unordered_set>

std::vector<std::string> print_passphrase(std::string passphrase)
{
	std::string tstr = "";
	std::vector<std::string> vec_str;
	std::stringstream str(passphrase);

	while(str) {
		str >> tstr;
		if (!str)
			break;
		else
			vec_str.push_back(tstr);
	}
	return vec_str;
}

int duplicate_word(std::vector<std::string> vec_str)
{
	std::unordered_set<std::string> set_str;	
	for (int i = 0; i < vec_str.size(); i++) {
		if (set_str.find(vec_str[i]) != set_str.end())
			return 0;
		else
			set_str.insert(vec_str[i]);
	}
	return 1;
}

int main(int argc, char **argv)
{
	int valid_phrase = 0;
	std::vector<std::string> vec_str;
	std::string passphrase;
	std::ifstream input_file(argv[1]);

	if (input_file.is_open()) {
		while(getline(input_file, passphrase)) {
			vec_str = print_passphrase(passphrase);
#ifdef PART1
			// part 1 -- complete
			valid_phrase += duplicate_word(vec_str);
#else
			// part 2 -- w.i.p.
			// valid_phrase += anagram_word(vec_str);
#endif
		}
	} else {
		std::cout << "error: file not opened" << std::endl;
		exit(1);
	}

	input_file.close();
	std::cout << "valid phrases: " << valid_phrase << std::endl;
	return 0;
}