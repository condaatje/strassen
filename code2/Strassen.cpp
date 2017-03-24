#include "Strassen.hpp"
#include "Helpers.hpp"
#include <vector>
#include <assert.h>

using namespace std;

void loadout(Matrix out, Matrix quart, int r, int c) {
    for(int i = 0; i < quart.d; i++) {
        for(int j = 0; j < quart.d; j++) {
            (*out.m)[r + i][c + j] = (*quart.m)[quart.i0 + i][quart.j0 + j];
        }
    }
}

// A B E F = AE+BG AF+BH
// C D G H   CE+DG CF+DH
Matrix strass(Matrix buffer, Matrix M1, Matrix M2, int bound) {
    int d = M1.d;
    int half = d / 2;
    if (d <= bound) {
        return mult(M1, M2);
    }

    // O(1) "copy" - no extra space used.
    Matrix A = Matrix(M1.i0,            M1.j0,              half, M1.m);
    Matrix B = Matrix(M1.i0,            M1.j0 + half,       half, M1.m);
    Matrix C = Matrix(M1.i0 + half,     M1.j0,              half, M1.m);
    Matrix D = Matrix(M1.i0 + half,     M1.j0 + half,       half, M1.m);
    
    Matrix E = Matrix(M2.i0,            M2.j0,              half, M2.m);
    Matrix F = Matrix(M2.i0,            M2.j0 + half,       half, M2.m);
    Matrix G = Matrix(M2.i0 + half,     M2.j0,              half, M2.m);
    Matrix H = Matrix(M2.i0 + half,     M2.j0 + half,       half, M2.m);
    
    Matrix P1 = strass(buffer, A, subt(F, H), bound);           // P1 = A(F−H)
    Matrix P2 = strass(buffer, add(A, B), H, bound);            // P2 = (A+B)H
    Matrix P3 = strass(buffer, add(C, D), E, bound);            // P3 = (C+D)E
    Matrix P4 = strass(buffer, D, subt(G, E), bound);           // P4 = D(G−E)
    Matrix P5 = strass(buffer, add(A, D), add(E, H), bound);    // P5 = (A+D)(E+H)
    Matrix P6 = strass(buffer, subt(B, D), add(G, H), bound);   // P6 = (B−D)(G+H)
    Matrix P7 = strass(buffer, subt(A, C), add(E, F), bound);   // P7 = (A−C)(E+F)
    
    Matrix AEBG = add(subt(add(P5, P4), P2), P6);   // AE + BG = P5 + P4 − P2 + P6
    Matrix AFBH = add(P1, P2);                      // AF + BH = P1 + P2
    Matrix CEDG = add(P3, P4);                      // CE + DG = P3 + P4
    Matrix CFDH = subt(subt(add(P5, P1), P3), P7);  // CF + DH = P5 + P1 − P3 − P7
    
                                // A B E F = AE+BG AF+BH
    // Load output Matrix       // C D G H   CE+DG CF+DH
    rawMatrix om (d, rawRow (d, 0));
    Matrix Out = Matrix(0, 0, d, make_shared<rawMatrix>(om));
    loadout(Out, AEBG, 0, 0);
    loadout(Out, AFBH, 0, half);
    loadout(Out, CEDG, half, 0);
    loadout(Out, CFDH, half, half);
    
    return Out;
}

// NOTE: for now, we aren't using the buffer because the program is fast enough
// To get the theoretical answer anyway. However, this could be a spot
// for future optimizations.

// Also, by using shared pointers I've eliminated the worst of the memory
// pressure already (though there is a good amount of
// allocation/deallocation that could be avoided).

