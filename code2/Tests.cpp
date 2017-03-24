//
//  Tests.cpp
//  code2
//
//  Created by Eagle on 3/21/17.
//  Copyright © 2017 Ondaatje124. All rights reserved.
//

#include "Tests.hpp"
#include "Helpers.hpp"
#include "Strassen.hpp"
#include <assert.h>
#include <iostream>

//const char nn = '\n';

void test0() {
    rawMatrix rm1 = {{1, 2}, {3, 4}};
    rawMatrix rm2 = {{5, 6}, {7, 8}};
    Matrix M1 = Matrix(0, 0, 2, &rm1);
    Matrix M2 = Matrix(0, 0, 2, &rm2);
    
    rawMatrix rmE = {{6, 8}, {10, 12}};
    Matrix expected = Matrix(0, 0, 2, &rmE);
    
    Matrix actual = add(M1, M2);
    if(!compare(expected, actual)) {
        printMatrix(expected);
        printMatrix(actual);
        assert(false);
    }
    
    rawMatrix rmE2 = {{-4, -4}, {-4, -4}};
    expected = Matrix(0, 0, 2, &rmE2);
    
    actual = subt(M1, M2);
    if(!compare(expected, actual)) {
        printMatrix(expected);
        printMatrix(actual);
        assert(false);
    }
}

void test1() {
    // 1 2  *  5 6 = 19 22
    // 3 4     7 8   43 50
    
    rawMatrix rm1 = {{1, 2}, {3, 4}};
    rawMatrix rm2 = {{5, 6}, {7, 8}};
    
    Matrix M1 = Matrix(0, 0, 2, &rm1);
    Matrix M2 = Matrix(0, 0, 2, &rm2);
    
    rawMatrix rmE = {{19, 22}, {43, 50}};
    Matrix expected = Matrix(0, 0, 2, &rmE);
    
    rawMatrix rmO1 = {{0, 0}, {0, 0}};
    //Matrix O1 = Matrix(0, 0, 2, &rmO1);
    
    rawMatrix rmO2 = {{0, 0}, {0, 0}};
    Matrix O2 = Matrix(0, 0, 2, &rmO2);
    
    Matrix actual = mult(M1, M2);
    Matrix strassResult = strass(O2, M1, M2, 8);
    
    // printMatrix(expected);
    // printMatrix(strassResult);
    
    if (!compare(expected, actual)) {
        printMatrix(expected);
        printMatrix(actual);
        assert(false);
    }
    
    if (!compare(expected, strassResult)) {
        assert(false);
    }
}

void test2() {
    // TODO better way of putting together a matrix from scratch.
    
    vector<vector<long>> rmO3 (4, vector<long> (4, 0));
    vector<vector<long>> rmO4 (4, vector<long> (4, 0));
    //Matrix O3 = Matrix(0, 0, 4, &rmO3);
    Matrix O4 = Matrix(0, 0, 4, &rmO4);
    
    rawMatrix rm3 = {
        {1,  2,  3,  4 },
        {5,  6,  7,  8 },
        {9,  10, 11, 12},
        {13, 14, 15, 16}};
    
    rawMatrix rm4 = {
        {17, 18, 19, 20},
        {21, 22, 23, 24},
        {25, 26, 27, 28},
        {29, 30, 31, 32}};
    
    Matrix M3 = Matrix(0, 0, 4, &rm3);
    Matrix M4 = Matrix(0, 0, 4, &rm4);
    
    rawMatrix rmE = {
        {250,  260,  270,  280},
        {618,  644,  670,  696},
        {986,  1028, 1070, 1112},
        {1354, 1412, 1470, 1528}};
    
    Matrix expected = Matrix(0, 0, 4, &rmE);
    Matrix actual = mult(M3, M4);
    Matrix strassResult = strass(O4, M3, M4, 2);
    
    if (!compare(expected, actual)) {
        assert(false);
    }
    
    if (!compare(expected, strassResult)) {
        printMatrix(expected);
        printMatrix(strassResult);
        assert(false);
    }
}

void test3() {
    vector<vector<long>> raw1 (512, vector<long> (512, 0));
    vector<vector<long>> raw2 (512, vector<long> (512, 0));
    vector<vector<long>> oRaw (512, vector<long> (512, 0));
    Matrix M1 = Matrix(0, 0, 512, &raw1);
    Matrix M2 = Matrix(0, 0, 512, &raw2);
    Matrix O = Matrix(0, 0, 512, &oRaw);
    
    randFill(M1);
    randFill(M2);
    
    Matrix actual = mult(M1, M2);
    Matrix strassResult = strass(O, M1, M2, 64);
    
    if (!compare(actual, strassResult)) {
        assert(false);
    }
    
}


void runTests() {
    test0();
    test1();
    test2();
    test3();
}



