#include "Helpers.hpp"
#include <vector>
#include <math.h>
#include <assert.h>
#include <iostream>

using namespace std;
const char nn = '\n';


// IMPORTANT! SQUARE MATRICES ONLY! (as per the spec)
Matrix subt(Matrix M1, Matrix M2) {
    // Read only
    
    int d = M1.d;
    
    // TODO memory leaks! (Shared pointers?)
    vector<vector<long>> * om = new vector<vector<long>> (d, vector<long> (d, 0));
    Matrix O = Matrix(0, 0, d, om);
    
    for(int i = 0; i < d; i++) {
        for(int j = 0; j < d; j++) {
            // Deal with offsets for the buffers.
            (*O.m)[O.i0 + i][O.j0 + j] =
                        (*M1.m)[M1.i0 + i][M1.j0 + j] -
                        (*M2.m)[M2.i0 + i][M2.j0 + j];
        }
    }
    return O;
}

Matrix add(Matrix M1, Matrix M2) {
    int d = M1.d;
    
    // TODO memory leaks! (Shared pointers?)
    vector<vector<long>> * om = new vector<vector<long>> (d, vector<long> (d, 0));
    Matrix O = Matrix(0, 0, d, om);
    // Also this should be taken out so we can be filling the out buffer instead.

    for(int i = 0; i < d; i++) {
        for(int j = 0; j < d; j++) {
            (*O.m)[O.i0 + i][O.j0 + j] =
                        (*M1.m)[M1.i0 + i][M1.j0 + j] +
                        (*M2.m)[M2.i0 + i][M2.j0 + j];
        }
    }
    return O;
}

Matrix mult(Matrix M1, Matrix M2) {
    int d = M1.d;
    
    vector<vector<long>> * om = new vector<vector<long>> (d, vector<long> (d, 0));
    Matrix O = Matrix(0, 0, d, om);
    
    for(int i = 0; i < d; i++) {
        for(int j = 0; j < d; j++) {
            for(int k = 0; k < d; k++) {
                // result[i][j] += M1[i][k] * M2[k][j];
                // TODO see if caching can be fixed.
                long l = (*M1.m)[M1.i0 + i][M1.j0 + k];
                long r = (*M2.m)[M2.i0 + k][M2.j0 + j];
                (*O.m)[O.i0 + i][O.j0 + j] += l * r;
            }
        }
    }
    
    return O;
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

void randFill(Matrix M) {
    for(int i = 0; i < M.d; i++) {
        for(int j = 0; j < M.d; j++) {
            (*M.m)[i][j] = (rand() % 1024) - (1024 / 2); // -512 through 512
        }
    }
}

void printMatrix(Matrix V) {
    for(int i = 0; i < V.d; i++) {
        for(int j = 0; j < V.d; j++) {
            cout << (*V.m)[i][j] << " ";
        }
        cout << nn;
    }
    cout << nn;
}

bool compare(Matrix M1, Matrix M2) {
    int d = M1.d;
    for(int i = 0; i < d; i++) {
        for(int j = 0; j < d; j++) {
            if ((*M1.m)[M1.i0 + i][M1.j0 + j] != (*M2.m)[M2.i0 + i][M2.j0 + j]) {
                return false;
            }
        }
    }
    return true;
}


