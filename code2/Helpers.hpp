#ifndef Helpers_hpp
#define Helpers_hpp

#include <stdio.h>
#include <vector>
#include <chrono>

using namespace std;
using matrix = vector<vector<long long>>;

matrix subt(vector<vector<long long>> M1, vector<vector<long long>> M2);
matrix add(vector<vector<long long>> M1, vector<vector<long long>> M2);
matrix mult(vector<vector<long long>> M1, vector<vector<long long>> M2);

int round_up_to_power_of_2(int n);
void randFill(matrix M);
void printMatrix(matrix v);

struct Trial {
    chrono::nanoseconds ns;
    int bound;
};

#endif /* Helpers_hpp */


