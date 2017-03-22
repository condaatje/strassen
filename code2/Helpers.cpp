#include "Helpers.hpp"
#include <vector>
#include <math.h>
#include <assert.h>
#include <iostream>

using namespace std;
const char nn = '\n';


// IMPORTANT! SQUARE MATRICES ONLY! (as per the spec)
matrix subt(matrix M1, matrix M2) {
    int d = (int) M1.size();
    matrix result (d, vector<long long> (d, 0));
    
    for(int i = 0; i < d; i++) {
        for(int j = 0; j < d; j++) {
            result[i][j] = M1[i][j] - M2[i][j];
        }
    }
    return result;
}

matrix add(matrix M1, matrix M2) {
    int d = (int) M1.size();
    
    matrix result (d, vector<long long> (d, 0));
    for(int i = 0; i < d; i++) {
        for(int j = 0; j < d; j++) {
            result[i][j] = M1[i][j] + M2[i][j];
        }
    }
    return result;
}

matrix mult(matrix M1, matrix M2) {
    int d = (int) M1.size();
    matrix result (d, vector<long long> (d, 0));
    
    for(int i = 0; i < d; i++) {
        for(int j = 0; j < d; j++) {
            for(int k = 0; k < d; k++) {
                result[i][j] += M1[i][k] * M2[k][j];
            }
        }
    }
    
    return result;
}


int round_up_to_power_of_2(int n) {
    
    // http://stackoverflow.com/a/108360
    if ((n & (n - 1)) == 0) {
        return n;
    }
    else {
        // http://stackoverflow.com/a/466256
        double r = pow(2, ceil(log(n)/log(2)));
        assert(r > n);
        
        return r;
    }
}

void randFill(matrix M) {
    int d = (int) M.size();
    for(int i = 0; i < d; i++) {
        for(int j = 0; j < d; j++) {
            M[i][j] = (rand() % 1024) - (1024 / 2); // -512 through 512
            //assert(M1[i][j] >= 0);
        }
    }
}


void printMatrix(matrix v) {
    for(int i = 0; i < v.size(); i++) {
        for(int j = 0; j < v[i].size(); j++) {
            cout << v[i][j] << " ";
        }
        cout << nn;
    }
}




