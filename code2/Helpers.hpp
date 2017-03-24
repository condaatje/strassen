#ifndef Helpers_hpp
#define Helpers_hpp

#include <stdio.h>
#include <vector>
#include <chrono>
#include <iostream>

using namespace std;
using rawMatrix = vector<vector<long>>;

// A matrix has start and end dimensions, and base data.
// This way, instead of copying a ton we can just pass around indices.
class Matrix {
public:
    Matrix(int ii0, int jj0, int dim, shared_ptr<rawMatrix> ptr) {
        this->i0 = ii0;
        this->j0 = jj0;
        this->d = dim; // better be square. TODO is this off by 1?
        this->m = ptr;
    }
    int i0;
    int j0;
    int d;
    shared_ptr<rawMatrix> m;
};

Matrix mult(Matrix M1, Matrix M2);

// in place
Matrix subt(Matrix M1, Matrix M2);
Matrix add(Matrix M1, Matrix M2);


int round_up_to_power_of_2(int n);
void randFill(Matrix M);
void printMatrix(Matrix M);
void staffPrint(Matrix M);

struct Trial {
    chrono::nanoseconds ns;
    int bound;
};

bool compare(Matrix M1, Matrix M2);

Matrix cpy(Matrix M);

#endif /* Helpers_hpp */


