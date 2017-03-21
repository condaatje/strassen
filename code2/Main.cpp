
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <assert.h>
#include "Main.hpp"
#include "Helpers.hpp"
#include "Strassen.hpp"

using namespace std; // somewhat frowned upon, but fine as long as nobody is dumb and collides with std...
const char nn = '\n';
matrix stras(matrix M1, matrix M2, int d);
void printMatrix(matrix v, int d);
void runTests();

int main(int argc, const char * argv[]) {
    
    if(argc != 4) {
        cout << "Usage: ./strassen <flag> <dimension> <inputfile>" << nn;
        // TODO what flags do we like?
        
        return 1;
    }
    
    int flag = atoi(argv[1]);
    int dimension = atoi(argv[2]);
    ifstream matrixFile (argv[3]);
    
    if (!matrixFile.is_open()) {
        cout << "Error: Could not open infile!" << nn;
        return 1;
    }
    
    string line;
    matrix M1 (dimension, vector<int> (dimension, 0));
    matrix M2 (dimension, vector<int> (dimension, 0));
    
    if (flag == 0) {
        
        // Load matrix 1
        for(int i = 0; i < dimension; i++) {
            for(int j = 0; j < dimension; j++) {
                getline (matrixFile, line);
                auto asdf = atoi(line.c_str());
                M1[i][j] = asdf;
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
        printMatrix(result, dimension);
        cout << nn;
    }
    
    runTests();
    
    return 0;
}

void runTests() {
    matrix M1 = {{1, 2}, {3, 4}};
    matrix M2 = {{5, 6}, {7, 8}};
    
    matrix expected = {{19, 22}, {43, 50}};
    matrix actual = mult(M1, M2, 2);
    matrix strassResult = mult(M1, M2, 2);
    
    for(int i = 0; i < 2; i++) {
        for(int j = 0; j < 2; j++) {
            assert(expected[i][j] == actual[i][j]);
            assert(expected[i][j] == strassResult[i][j]); // TODO big
        }
    }
}

void printMatrix(matrix v, int d) {
    for(int i = 0; i < d; i++) {
        for(int j = 0; j < d; j++) {
            cout << v[i][j] << " ";
        }
        cout << nn;
    }
}





