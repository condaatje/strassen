//
//  Strassen.cpp
//  code2
//
//  Created by Eagle on 3/20/17.
//  Copyright © 2017 Ondaatje124. All rights reserved.
//

#include "Strassen.hpp"
#include "Helpers.hpp"
#include <vector>

using namespace std;


// A B E F = AE+BG AF+BH
// C D G H   CE+DG CF+DH
matrix strass(matrix M1, matrix M2, int d) {
    // TODO Avoid excessive memory allocation and deallocation.
    // This requires some thinking. Will probably need to do it all in buffer(s).
    matrix A (d / 2, vector<int> (d / 2, 0));
    matrix B (d / 2, vector<int> (d / 2, 0));
    matrix C (d / 2, vector<int> (d / 2, 0));
    matrix D (d / 2, vector<int> (d / 2, 0));
    matrix E (d / 2, vector<int> (d / 2, 0));
    matrix F (d / 2, vector<int> (d / 2, 0));
    matrix G (d / 2, vector<int> (d / 2, 0));
    matrix H (d / 2, vector<int> (d / 2, 0));
    
    return mult(M1, M2, d); //TODO
}
