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
        cout << "0: Staff, 1: Random" << nn;
        // TODO what flags do we like?
        
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
        printMatrix(result, dimension);
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
                // TODO reassess testing on the fly.
                assert(result[i][j] == expected[i][j]);
            }
        }
        
        cout << "Success!" << nn;
    }
    
    runTests();
    
    return 0;
}

void runTests() {
    matrix M1 = {{1, 2}, {3, 4}};
    matrix M2 = {{5, 6}, {7, 8}};
    
    matrix expected = {{19, 22}, {43, 50}};
    matrix actual = mult(M1, M2);
    matrix strassResult = mult(M1, M2);
    
    for(int i = 0; i < 2; i++) {
        for(int j = 0; j < 2; j++) {
            assert(expected[i][j] == actual[i][j]);
            assert(expected[i][j] == strassResult[i][j]); // TODO big
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
    matrix strassResult2 = mult(M3, M4);
    
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

void printMatrix(matrix v, int d) {
    for(int i = 0; i < d; i++) {
        for(int j = 0; j < d; j++) {
            cout << v[i][j] << " ";
        }
        cout << nn;
    }
}







