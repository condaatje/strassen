#include "Strassen.hpp"
#include "Helpers.hpp"
#include <vector>
#include <assert.h>

using namespace std;

void loadout(Matrix out, Matrix quart) {
    for(int i = 0; i < quart.d; i++) {
        for(int j = 0; j < quart.d; j++) {
            (*out.m)[out.i0 + i][out.j0 + j] = (*quart.m)[quart.i0 + i][quart.j0 + j];
        }
    }
}


// A B E F = AE+BG AF+BH
// C D G H   CE+DG CF+DH
Matrix strass(Matrix O, Matrix M1, Matrix M2, int bound) {
    // Outbuffer, M1, M2, bound/crossover point
    
    int d = M1.d;
    int half = d / 2;
    if (d < bound) {
        // This should be the only time the outbuffer gets filled,
        // unless I'm going to be doing some super l33t hax.
        // TODO so much better/actual buffer usage - correctness first.
        return mult(M1, M2);
    }

    Matrix A = Matrix(M1.i0,            M1.j0,              half, M1.m);
    Matrix B = Matrix(M1.i0,            M1.j0 + half,       half, M1.m);
    Matrix C = Matrix(M1.i0 + half,     M1.j0,              half, M1.m);
    Matrix D = Matrix(M1.i0 + half,     M1.j0 + half,       half, M1.m);
    
    Matrix E = Matrix(M2.i0,            M2.j0,              half, M2.m);
    Matrix F = Matrix(M2.i0,            M2.j0 + half,       half, M2.m);
    Matrix G = Matrix(M2.i0 + half,     M2.j0,              half, M2.m);
    Matrix H = Matrix(M2.i0 + half,     M2.j0 + half,       half, M2.m);
    
    
    // Maybe could have a flag for when there is a matrix that is over-writeable?
    // Remember: order matters in matrix mult! (AB != BA)
    Matrix P1 = strass(O, A, subt(F, H), bound);                // P1 = A(F−H)
    Matrix P2 = strass(O, add(A, B), H, bound);                 // P2 = (A+B)H
    Matrix P3 = strass(O, add(C, D), E, bound);                 // P3 = (C+D)E
    Matrix P4 = strass(O, D, subt(G, E), bound);                // P4 = D(G−E)
    Matrix P5 = strass(O, add(A, D), add(E, H), bound);         // P5 = (A+D)(E+H)
    Matrix P6 = strass(O, subt(B, D), add(G, H), bound);        // P6 = (B−D)(G+H)
    Matrix P7 = strass(O, subt(A, C), add(E, F), bound);        // P7 = (A−C)(E+F)
    
    Matrix AEBG = add(subt(add(P5, P4), P2), P6);   // AE + BG = P5 + P4 − P2 + P6
    Matrix AFBH = add(P1, P2);                      // AF + BH = P1 + P2
    Matrix CEDG = add(P3, P4);                      // CE + DG = P3 + P4
    Matrix CFDH = subt(subt(add(P5, P1), P3), P7);  // CF + DH = P5 + P1 − P3 − P7
    
    // Load output Matrix
    // A B E F = AE+BG AF+BH
    // C D G H   CE+DG CF+DH
    
    vector<vector<long>> * om = new vector<vector<long>> (d, vector<long> (d, 0));
    Matrix O2 = Matrix(0, 0, d, om);

    O2.i0 = 0;
    O2.j0 = 0;
    loadout(O2, AEBG);
    //printMatrix(O2);
    
    O2.i0 = 0;
    O2.j0 = half;
    loadout(O2, AFBH);
    //printMatrix(O2);
    
    O2.i0 = half;
    O2.j0 = 0;
    loadout(O2, CEDG);
    //printMatrix(O2);
    
    
    O2.i0 = half;
    O2.j0 = half;
    loadout(O2, CFDH);
    //printMatrix(O2);
    
    O2.i0 = 0;
    O2.j0 = 0;

    return O2;
}
