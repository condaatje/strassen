#include "Strassen.hpp"
#include "Helpers.hpp"
#include <vector>
#include <assert.h>

using namespace std;


// A B E F = AE+BG AF+BH
// C D G H   CE+DG CF+DH
matrix strass(matrix M1, matrix M2, int d) {
    // TODO Avoid excessive memory allocation and deallocation.
    // This requires some thinking. Will probably need to do it all in buffer(s).
    matrix A (d / 2, vector<long long> (d / 2, 0));
    matrix B (d / 2, vector<long long> (d / 2, 0));
    matrix C (d / 2, vector<long long> (d / 2, 0));
    matrix D (d / 2, vector<long long> (d / 2, 0));
    matrix E (d / 2, vector<long long> (d / 2, 0));
    matrix F (d / 2, vector<long long> (d / 2, 0));
    matrix G (d / 2, vector<long long> (d / 2, 0));
    matrix H (d / 2, vector<long long> (d / 2, 0));
    
    int dim = d / 2;
    
    // TODO pattern should become apparent so we can do this in a three-deep loop.
    // Also this most likely negates any benefit - should be done in a buffer.
    // For now, just trying to get the algo to work.
    // Will hit correctness, then maintain as I optimize.
    
    // Load A:
    for(int i = 0; i < dim; i++) {
        for(int j = 0; j < dim; j++) {
            A[i][j] = M1[i][j];
        }
    }
    
    // Load B:
    for(int i = 0; i < dim; i++) {
        for(int j = dim; j < d; j++) {
            B[i][j - dim] = M1[i][j];
        }
    }
    
    // Load C:
    for(int i = dim; i < d; i++) {
        for(int j = 0; j < dim; j++) {
            C[i - dim][j] = M1[i][j];
        }
    }
    
    // Load D:
    for(int i = dim; i < d; i++) {
        for(int j = dim; j < d; j++) {
            D[i - dim][j - dim] = M1[i][j];
        }
    }
    
    // Load E:
    for(int i = 0; i < dim; i++) {
        for(int j = 0; j < dim; j++) {
            E[i][j] = M2[i][j];
        }
    }
    
    // Load F:
    for(int i = 0; i < dim; i++) {
        for(int j = dim; j < d; j++) {
            F[i][j - dim] = M2[i][j];
        }
    }
    
    // Load G:
    for(int i = dim; i < d; i++) {
        for(int j = 0; j < dim; j++) {
            G[i - dim][j] = M2[i][j];
        }
    }
    
    // Load H:
    for(int i = dim; i < d; i++) {
        for(int j = dim; j < d; j++) {
            H[i - dim][j - dim] = M2[i][j];
        }
    }
    
    // TODO recursive
    // Note: order matters in matrix mult!
    matrix P1 = mult(A, subt(F, H)); // P1 = A(F−H)
    matrix P2 = mult(add(A, B), H);  // P2 = (A+B)H
    matrix P3 = mult(add(C, D), E);  // P3 = (C+D)E
    matrix P4 = mult(D, subt(G, E)); // P4 = D(G−E)
    matrix P5 = mult(add(A, D), add(E, H));  // P5 = (A+D)(E+H)
    matrix P6 = mult(subt(B, D), add(G, H)); // P6 = (B−D)(G+H)
    matrix P7 = mult(subt(A, C), add(E, F)); // P7 = (A−C)(E+F)
    
    matrix AEBG = add(subt(add(P5, P4), P2), P6); // AE + BG = P5 + P4 − P2 + P6
    matrix AFBH = add(P1, P2); // AF + BH = P1 + P2
    matrix CEDG = add(P3, P4); // CE + DG = P3 + P4
    matrix CFDH = subt(subt(add(P5, P1), P3), P7); // CF + DH = P5 + P1 − P3 − P7
    
    
    matrix result (d, vector<long long> (d, 0));
    
    // Load output matrix
    // Load AEBG:
    for(int i = 0; i < dim; i++) {
        for(int j = 0; j < dim; j++) {
            result[i][j] = AEBG[i][j];
        }
    }
    
    // Load B:
    for(int i = 0; i < dim; i++) {
        for(int j = dim; j < d; j++) {
            result[i][j] = AFBH[i][j - dim];
        }
    }
    
    // Load C:
    for(int i = dim; i < d; i++) {
        for(int j = 0; j < dim; j++) {
            result[i][j] = CEDG[i - dim][j];
        }
    }
    
    // Load D:
    for(int i = dim; i < d; i++) {
        for(int j = dim; j < d; j++) {
            result[i][j] = CFDH[i - dim][j - dim];
        }
    }
    
    return result; //TODO
}
