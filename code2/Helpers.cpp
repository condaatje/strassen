//
//  Helpers.cpp
//  code2
//
//  Created by Eagle on 3/20/17.
//  Copyright © 2017 Ondaatje124. All rights reserved.
//

#include "Helpers.hpp"
#include <vector>

using namespace std;

matrix subt(matrix M1, matrix M2, int d) {
    matrix result (d, vector<int> (d, 0));
    for(int i = 0; i < d; i++) {
        for(int j = 0; j < d; j++) {
            result[i][j] = M1[i][j] - M2[i][j];
        }
    }
    return result;
}


matrix add(matrix M1, matrix M2, int d) {
    matrix result (d, vector<int> (d, 0));
    for(int i = 0; i < d; i++) {
        for(int j = 0; j < d; j++) {
            result[i][j] = M1[i][j] + M2[i][j];
        }
    }
    return result;
}

// works with square matrices at this point, but so does the program.
matrix mult(matrix M1, matrix M2, int d) {
    
    matrix result (d, vector<int> (d, 0));
    
    for(int i = 0; i < d; i++) {
        for(int j = 0; j < d; j++) {
            for(int k = 0; k < d; k++) {
                result[i][j] += M1[i][k] * M2[k][j];
            }
        }
    }
    
    return result;
}







