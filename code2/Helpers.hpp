//
//  Helpers.hpp
//  code2
//
//  Created by Eagle on 3/20/17.
//  Copyright © 2017 Ondaatje124. All rights reserved.
//

#ifndef Helpers_hpp
#define Helpers_hpp

#include <stdio.h>
#include <vector>

using namespace std;
using matrix = vector<vector<int>>;

matrix subt(vector<vector<int>> M1, vector<vector<int>> M2, int d);
matrix add(vector<vector<int>> M1, vector<vector<int>> M2, int d);
matrix mult(vector<vector<int>> M1, vector<vector<int>> M2, int d);

#endif /* Helpers_hpp */


