#ifndef Helpers_hpp
#define Helpers_hpp

#include <stdio.h>
#include <vector>

using namespace std;
using matrix = vector<vector<int>>;

matrix subt(vector<vector<int>> M1, vector<vector<int>> M2);
matrix add(vector<vector<int>> M1, vector<vector<int>> M2);
matrix mult(vector<vector<int>> M1, vector<vector<int>> M2);

#endif /* Helpers_hpp */


