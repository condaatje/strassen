#ifndef Helpers_hpp
#define Helpers_hpp

#include <stdio.h>
#include <vector>

using namespace std;
using matrix = vector<vector<long long>>;

matrix subt(vector<vector<long long>> M1, vector<vector<long long>> M2);
matrix add(vector<vector<long long>> M1, vector<vector<long long>> M2);
matrix mult(vector<vector<long long>> M1, vector<vector<long long>> M2);

#endif /* Helpers_hpp */


