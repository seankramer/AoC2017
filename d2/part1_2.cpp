#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
using namespace std;

// part 1 -- complete
int sum_of_line(string data_str)
{
    stringstream str(data_str);
    int num, smallest = 0, largest = 0;

    while(str) {
        str >> num;
        if (!str)
            break;
        else if (num > largest)
            largest = num;
        else if (smallest == 0)
            smallest = num;
        else
            if (num < smallest)
                smallest = num;

    }
    cout << "smallest: " << smallest << endl;
    cout << "largest: " << largest << endl;
    cout << "sum of line: " << largest - smallest << endl;
    cout << endl;
    return (largest - smallest);
}

// part 2 -- complete
int quotient_of_line(string data_str)
{
    int num, sum = 0;
    stringstream str(data_str);
    vector<int> data;

    while(str) {
        str >> num;
        if (!str) break;
        data.push_back(num);
    }
    for (auto i : data) {
        for (auto j : data) {
            if (i != j && i % j == 0) {
                cout << "i: " << i << endl;
                cout << "j: " << j << endl;
                cout << "i / j: " << (i / j) << endl;
                sum = (i / j);
            }
        }
    }
    cout << endl;
    return sum;
}

int main(int argc, char **argv)
{
    int sum;
    string data_str;
    ifstream input_file(argv[1]);

    if (input_file.is_open()) {
        while(getline(input_file, data_str))
// #define PART1
#ifdef PART1
            sum += sum_of_line(data_str);
#else
            sum += quotient_of_line(data_str);
#endif
    } else {
        cout << "error: file not opened" << endl;
        exit(1);
    }
    input_file.close();
    cout << sum << endl;
    return 0;
}
