#include <string>
#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char **argv)
{
    int sum = 0;
    int half_size = 0;
    string data_str;
    ifstream input_file(argv[1]);
    if (input_file.is_open()) {
        getline(input_file, data_str);
        half_size = data_str.size() / 2;
    } else {
        cout << "error: file not opened" << endl;
        exit(1);
    }

#define PART1
#ifdef PART1
    // part 1 -- correct
    for (int i = 0; i < data_str.size(); i++) {
        if (data_str[i] == data_str[i + 1])
            sum += data_str[i] - '0';
        else if (i == data_str.size() - 1 && data_str[i] == data_str[0])
            sum += data_str[i] - '0';
    }
#else
    // part 2 -- correct
    for (int i = 0; i < half_size; i++)
        if (data_str[i] == data_str[i + half_size])
            sum += (data_str[i] - '0') * 2;
#endif

    cout << "sum: " << sum << endl;
    input_file.close();
    return 0;
}
