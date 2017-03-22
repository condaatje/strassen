#include "Strassen.hpp"
#include "Helpers.hpp"
#include <vector>
#include <assert.h>

using namespace std;


void load(matrix * quart, matrix * whole, int start_i, int end_i, int start_j, int end_j) {
    //(*test.frames)[0].w;
    // this is n^2, so may negate benefit of using strassen's.
    for(int i = start_i; i < end_i; i++) {
        for(int j = start_j; j < end_j; j++) {
            (*quart)[i - start_i][j - start_j] = (*whole)[i][j];
        }
    }
}

void loadout(matrix * out, matrix * quart, int start_i, int end_i, int start_j, int end_j) {
    for(int i = start_i; i < end_i; i++) {
        for(int j = start_j; j < end_j; j++) {
            (*out)[i][j] = (*quart)[i - start_i][j - start_j];
        }
    }
}

// A B E F = AE+BG AF+BH
// C D G H   CE+DG CF+DH
matrix strass(matrix M1, matrix M2, int bound) {
    // TODO implement bound
    
    int d = (int) M1.size();
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
    
    int half = d / 2;
    
    // For now, just trying to get the algo to work.
    // Will hit correctness, then maintain as I optimize.
    
    load(&A, &M1, 0, half, 0, half);
    load(&B, &M1, 0, half, half, d);
    load(&C, &M1, half, d, 0, half);
    load(&D, &M1, half, d, half, d);
    load(&E, &M2, 0, half, 0, half);
    load(&F, &M2, 0, half, half, d);
    load(&G, &M2, half, d, 0, half);
    load(&H, &M2, half, d, half, d);
    
    // TODO recursive
    // Remember: order matters in matrix mult! (AB != BA)
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
    loadout(&result, &AEBG, 0, half, 0, half);
    loadout(&result, &AFBH, 0, half, half, d);
    loadout(&result, &CEDG, half, d, 0, half);
    loadout(&result, &CFDH, half, d, half, d);

    return result;
}
