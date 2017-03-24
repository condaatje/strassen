#include "Tests.hpp"
#include "Helpers.hpp"
#include "Strassen.hpp"
#include <assert.h>
#include <iostream>

//const char nn = '\n';

void test0() {
    rawMatrix rm1 = {{1, 2}, {3, 4}};
    rawMatrix rm2 = {{5, 6}, {7, 8}};
    Matrix M1 = Matrix(0, 0, 2, make_shared<rawMatrix>(rm1));
    Matrix M2 = Matrix(0, 0, 2, make_shared<rawMatrix>(rm2));
    
    rawMatrix rmE = {{6, 8}, {10, 12}};
    Matrix expected = Matrix(0, 0, 2, make_shared<rawMatrix>(rmE));
    
    Matrix actual = add(M1, M2);
    if(!compare(expected, actual)) {
        printMatrix(expected);
        printMatrix(actual);
        assert(false);
    }
    
    rawMatrix rmE2 = {{-4, -4}, {-4, -4}};
    expected = Matrix(0, 0, 2, make_shared<rawMatrix>(rmE2));
    
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
    int d = 2;
    rawMatrix rm1 = {{1, 2}, {3, 4}};
    rawMatrix rm2 = {{5, 6}, {7, 8}};
    
    Matrix M1 = Matrix(0, 0, d, make_shared<rawMatrix>(rm1));
    Matrix M2 = Matrix(0, 0, d, make_shared<rawMatrix>(rm2));
    
    rawMatrix rmE = {{19, 22}, {43, 50}};
    Matrix expected = Matrix(0, 0, d, make_shared<rawMatrix>(rmE));
    
    // extra space
    rawMatrix b (d * 2, vector<long> (d * 2, 0));
    Matrix buffer = Matrix(0, 0, d * 2, make_shared<rawMatrix>(b));
    
    Matrix actual = mult(M1, M2);
    Matrix strassResult = strass(buffer, M1, M2, 8);
    
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
    int d = 4;
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
    
    Matrix M3 = Matrix(0, 0, d, make_shared<rawMatrix>(rm3));
    Matrix M4 = Matrix(0, 0, d, make_shared<rawMatrix>(rm4));
    
    rawMatrix rmE = {
        {250,  260,  270,  280},
        {618,  644,  670,  696},
        {986,  1028, 1070, 1112},
        {1354, 1412, 1470, 1528}};
    
    // extra space
    rawMatrix b (d * 2, vector<long> (d * 2, 0));
    Matrix buffer = Matrix(0, 0, d * 2, make_shared<rawMatrix>(b));
    
    Matrix expected = Matrix(0, 0, d, make_shared<rawMatrix>(rmE));
    Matrix actual = mult(M3, M4);
    Matrix strassResult = strass(buffer, M3, M4, 2);
    
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
    int d = 512;
    rawMatrix raw1 (d, vector<long> (d, 0));
    rawMatrix raw2 (d, vector<long> (d, 0));
    Matrix M1 = Matrix(0, 0, d, make_shared<rawMatrix>(raw1));
    Matrix M2 = Matrix(0, 0, d, make_shared<rawMatrix>(raw2));
    
    randFill(M1);
    randFill(M2);
    
    // extra space
    rawMatrix b (d * 2, vector<long> (d * 2, 0));
    Matrix buffer = Matrix(0, 0, d * 2, make_shared<rawMatrix>(b));
    
    Matrix actual = mult(M1, M2);
    Matrix strassResult = strass(buffer, M1, M2, 64);
    
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



