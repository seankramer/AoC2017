#include <cmath>
#include <iostream>

using namespace std;

// #define PART1
#define ACCESS_PORT 1
#define START_NUM   312051


struct Coords
{
    int row;
    int col;
};

struct adj_data
{
    int blocks;
    int sum;
};

int **make_spiral(int n)
{
    int **matrix = new int *[n];
    int i, j, x, r, c, val = 0;
    for (i = 0; i < n; i++) {
        matrix[i] = new int[n];
        for (j = 0; j < n; j++) {
            x = max(max(i, j), max(n-1-i, n-1-j));
            val = (i < j) ? (n-2*x)*(n-2*x) - (i-x) - (j-x) :
                            (n-2*x-2)*(n-2*x-2) + (i-x) + (j-x);
            matrix[i][j] = val;
        }
    }
    return matrix;
}

void find_matrix_coords(Coords& pos, int **matrix, int msz, int pval)
{
    if (pval == ACCESS_PORT) {
        pos.row = msz / 2;
        pos.col = msz / 2;
    } else {
        for (int i = 0; i < msz; i++) {
            for (int j = 0; j < msz; j++) {
                if (matrix[i][j] == pval) {
                    pos.row = i;
                    pos.col = j;
                }
            }
        }
    }
}

void find_adjacent_vals(adj_data& ajd, int **matrix, int r, int c, int msz)
{
    // cout << "start row : " << r << " " << "start col : " << c << endl;
    int adj_sum = 0, adj_blocks = 0;
    for (int i = r - 1; i <= r + 1; i++) {
        if (i >= msz || i < 0) {
            continue;
        } else {
            for (int j = c - 1; j <= c + 1; j++) {
                if (i == r && j == c) {
                    continue;
                } else if (j >= msz || j < 0) {
                    continue;
                } else {
                    adj_sum += matrix[i][j];
                    if (matrix[i][j] != 0) {
                        // cout << "i, j: " << i << ", " << j << endl;
                        adj_blocks++;
                    }
                }
            }
        }
    }
    ajd.blocks = adj_blocks;
    ajd.sum = adj_sum;
    cout << "adj_sum : " << adj_sum << endl;
}

int **blank_spiral(int n)
{
    int **matrix = new int *[n];
    int i, j, x, r, c, val = 0;
    for (i = 0; i < n; i++) {
        matrix[i] = new int[n];
        for (j = 0; j < n; j++) {
            matrix[i][j] = 0;
        }
    }
    return matrix;
}

void populate_fib_matrix(int **matrix, int msz)
{
    adj_data ajd;
    int filled_blocks = 0;
    int empty_blocks = msz * msz;
    int r = msz / 2, c = msz / 2;
    while (ajd.sum < START_NUM) {
    // while (empty_blocks != 0) {
        find_adjacent_vals(ajd, matrix, r, c, msz);
        if (ajd.blocks == 0) {
            matrix[r][c] = 1;
            c++;
        } else {
            matrix[r][c] = ajd.sum;
            if (ajd.blocks == 1) {
                r--;
            } else if (ajd.blocks == 2) {
                if (c == 0) {
                    if (matrix[r][c + 1] == 0)
                        c++;
                    else
                        r++;
                } else if (matrix[r + 1][c - 1] != 0 && matrix[r][c - 1] == 0)
                    c--;
                else if (matrix[r + 1][c + 1] != 0)
                    r++;
                else if (matrix[r][c - 1] != 0)
                    r--;
                else
                    c++;
            } else if (ajd.blocks == 3) {
                if (matrix[r][c - 1] == 0 && matrix[r + 1][c] != 0)
                    c--;
                else if (matrix[r][c + 1] != 0 && matrix[r + 1][c] == 0)
                    r++;
                else if (matrix[r][c + 1] == 0 && matrix[r - 1][c] != 0)
                    c++;
                else if (matrix[r][c - 1] != 0 && matrix[r - 1][c] == 0)
                    r--;
            } else if (ajd.blocks == 4) {
                if (r == 0) {
                    if (matrix[r][c - 1] == 0)
                        c--;
                } else if (c == 0) {
                    if (matrix[r + 1][c] == 0)
                        r++;
                } else if (matrix[r][c - 1] == 0 && matrix[r][c + 1] != 0) {
                    if (matrix[r - 1][c] != 0 && matrix[r + 1][c] == 0)
                        r++;
                    else
                        c--;
                } else if (matrix[r - 1][c] == 0) {
                    r--;
                } else if (matrix[r - 1][c] != 0 && matrix[r + 1][c] == 0) {
                    if (matrix[r][c + 1] != 0)
                        r++;
                    else
                        c++;
                } else
                    c++;
            } else {
                break;
            }
        }
        filled_blocks++;
        // cout << "end row : " << r << " " << "end col : " << c << endl << endl;
    }
    cout << "filled blocks: " << filled_blocks << endl;
}

int main(int argc, char **argv)
{
    float start_sqrt = (float)sqrt(START_NUM);
    int matrix_sz = round(start_sqrt);
    if (matrix_sz % 2 == 0) matrix_sz += 1;

#ifdef PART1
    // part 1 -- complete
    Coords center, start_pos;
    int **matrix = make_spiral(matrix_sz);
    find_matrix_coords(center, matrix, matrix_sz, ACCESS_PORT);
    find_matrix_coords(start_pos, matrix, matrix_sz, START_NUM);

    int total_steps = abs(start_pos.col - center.col) +
                      abs(start_pos.row - center.row);
    cout << "total steps: " << total_steps << endl;
#else
    // part 2 -- complete
    int **matrix = blank_spiral(matrix_sz);
    populate_fib_matrix(matrix, matrix_sz);
#endif

    return 0;
}
