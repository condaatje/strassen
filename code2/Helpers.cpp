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
    
    rawMatrix om (d, rawRow (d, 0));
    Matrix O = Matrix(0, 0, d, make_shared<rawMatrix>(om));
    
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
    
    rawMatrix om (d, rawRow (d, 0));
    Matrix O = Matrix(0, 0, d, make_shared<rawMatrix>(om));

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
    
    rawMatrix om (d, rawRow (d, 0));
    Matrix O = Matrix(0, 0, d, make_shared<rawMatrix>(om));
    
    for(int i = 0; i < d; i++) {
        for(int j = 0; j < d; j++) {
            for(int k = 0; k < d; k++) {
                // result[i][j] += M1[i][k] * M2[k][j];
                // TODO see if performance can be improved w caching optimizations.
                long l = (*M1.m)[M1.i0 + i][M1.j0 + k];
                long r = (*M2.m)[M2.i0 + k][M2.j0 + j];
                (*O.m)[O.i0 + i][O.j0 + j] += l * r;
            }
        }
    }
    
    return O;
}

int round_up_to_power_of_2(int n) {
    if ((n & (n - 1)) == 0) {
        return n;
    }
    else {
        return pow(2, ceil(log(n)/log(2)));
    }
}

void randFill(Matrix M) {
    for(int i = 0; i < M.d; i++) {
        for(int j = 0; j < M.d; j++) {
            // -512 through 512 for now. Could eliminate magic numbers...
            (*M.m)[i][j] = (rand() % 1024) - (1024 / 2);
        }
    }
}

void printMatrix(Matrix M) {
    for(int i = 0; i < M.d; i++) {
        for(int j = 0; j < M.d; j++) {
            cout << (*M.m)[i][j] << " ";
        }
        cout << nn;
    }
    cout << nn;
}

void staffPrint(Matrix M) {
    for(int i = 0; i < M.d; i++) {
        cout << (*M.m)[i][i] << nn;
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

Matrix cpy(Matrix M) {
    rawMatrix mm1 (M.d, rawRow (M.d, 0));
    Matrix N = Matrix(M.i0, M.j0, M.d, make_shared<rawMatrix>(mm1));
    
    for(int i = 0; i < M.d; i++) {
        for(int j = 0; j < M.d; j++) {
            (*N.m)[M.i0 + i][M.j0 + j] = (*M.m)[M.i0 + i][M.j0 + j];
        }
    }
    
    return N;
}
