#include "Helpers.hpp"
#include <vector>

using namespace std;


// IMPORTANT! SQUARE MATRICES ONLY! (as per the spec)
matrix subt(matrix M1, matrix M2) {
    int d = (int) M1.size();
    matrix result (d, vector<long long> (d, 0));
    
    for(int i = 0; i < d; i++) {
        for(int j = 0; j < d; j++) {
            result[i][j] = M1[i][j] - M2[i][j];
        }
    }
    return result;
}

matrix add(matrix M1, matrix M2) {
    int d = (int) M1.size();
    
    matrix result (d, vector<long long> (d, 0));
    for(int i = 0; i < d; i++) {
        for(int j = 0; j < d; j++) {
            result[i][j] = M1[i][j] + M2[i][j];
        }
    }
    return result;
}

matrix mult(matrix M1, matrix M2) {
    int d = (int) M1.size();
    matrix result (d, vector<long long> (d, 0));
    
    for(int i = 0; i < d; i++) {
        for(int j = 0; j < d; j++) {
            for(int k = 0; k < d; k++) {
                result[i][j] += M1[i][k] * M2[k][j];
            }
        }
    }
    
    return result;
}







