#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <assert.h>
#include "Main.hpp"
#include "Helpers.hpp"
#include "Strassen.hpp"
#include "Tests.hpp"

using namespace std; // somewhat frowned upon, but fine as long as nobody is dumb and collides with std...
const char nn = '\n';
matrix stras(matrix M1, matrix M2, int d);



int main(int argc, const char * argv[]) {
    
    if(argc != 4) {
        cout << "Usage: ./strassen <flag> <dimension> <inputfile>" << nn;
        cout << "0: Staff, 1: Random" << nn;        
        return 1;
    }
    
    int flag = atoi(argv[1]);
    int dimension = round_up_to_power_of_2(atoi(argv[2]));
    
    matrix M1 (dimension, vector<long long> (dimension, 0));
    matrix M2 (dimension, vector<long long> (dimension, 0));
    
    if (flag == 0) {
        ifstream matrixFile (argv[3]);
        
        if (!matrixFile.is_open()) {
            cout << "Error: Could not open infile!" << nn;
            return 1;
        }
        
        string line;
 
        // Load matrix 1
        for(int i = 0; i < dimension; i++) {
            for(int j = 0; j < dimension; j++) {
                getline (matrixFile, line);
                M1[i][j] = atoi(line.c_str());
            }
        }
        
        // Load matrix 2
        for(int i = 0; i < dimension; i++) {
            for(int j = 0; j < dimension; j++) {
                getline (matrixFile, line);
                M2[i][j] = atoi(line.c_str());
            }
        }
        
        // execute strassen's algorithm, print the result.
        matrix result = strass(M1, M2, dimension);
        
        printMatrix(result);
        
        cout << nn;
    }
    
    else if (flag == 1) {
        // Just use a random matrix with dimensions as proposed
        
        randFill(M1);
        randFill(M2);
        
        matrix result = strass(M1, M2, dimension);
        matrix expected = mult(M1, M2);
        
        for(int i = 0; i < dimension; i++) {
            for(int j = 0; j < dimension; j++) {
                assert(result[i][j] == expected[i][j]);
            }
        }
        
    
    }
    
    runTests();
    
    cout << "Success!" << nn;
    
    return 0;
}
