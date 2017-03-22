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



void runTests() {
    matrix M1 = {{1, 2}, {3, 4}};
    matrix M2 = {{5, 6}, {7, 8}};
    
    matrix expected = {{19, 22}, {43, 50}};
    matrix actual = mult(M1, M2);
    matrix strassResult = strass(M1, M2, 0); //TODO bound
    
    // printMatrix(expected);
    // printMatrix(strassResult);
    
    for(int i = 0; i < 2; i++) {
        for(int j = 0; j < 2; j++) {
            assert(expected[i][j] == actual[i][j]);
            assert(expected[i][j] == strassResult[i][j]);
        }
    }
    
    matrix M3 = {
        {1,  2,  3,  4 },
        {5,  6,  7,  8 },
        {9,  10, 11, 12},
        {13, 14, 15, 16}};
    
    matrix M4 = {
        {17, 18, 19, 20},
        {21, 22, 23, 24},
        {25, 26, 27, 28},
        {29, 30, 31, 32}};
    
    matrix expected2 = {
        {250,  260,  270,  280},
        {618,  644,  670,  696},
        {986,  1028, 1070, 1112},
        {1354, 1412, 1470, 1528}};
    
    matrix actual2 = mult(M3, M4);
    matrix strassResult2 = strass(M3, M4, 0); //TODO bound
    
    //    1   250	  260	270	   280
    //    2	  618	  644	670	   696
    //    3	  986	  1028	1070   1112
    //    4	  1354	  1412	1470   1528
    
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            assert(expected2[i][j] == actual2[i][j]);
            assert(expected2[i][j] == strassResult2[i][j]); // TODO big
        }
    }
}
