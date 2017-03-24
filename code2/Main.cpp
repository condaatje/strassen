#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <assert.h>
#include <chrono>
#include "Main.hpp"
#include "Helpers.hpp"
#include "Strassen.hpp"
#include "Tests.hpp"

using namespace std; // somewhat frowned upon, but fine as long as nobody is dumb and collides with std...
using namespace chrono;
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
    // TODO return matrix should not have padding zeroes.
    
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
        int bound = 16;
        long long prevTime = LONG_LONG_MAX;
        
        vector<Trial> results;
        
        while (bound < dimension) {
            auto begin = high_resolution_clock::now();
            matrix result = strass(M1, M2, bound);
            auto end = high_resolution_clock::now();
            auto time = duration_cast<nanoseconds>(end-begin).count();

            // If this bound resulted in worse performance than the previous bound, then the optimal bound was the last one.
            if (time > prevTime) {
                cout << "proper bound: " << bound / 2 << nn;
                break;
            }
            
            prevTime = time;
            bound = bound * 2;
        }
        
    }
    
    runTests();
    
    cout << "Success!" << nn;
    
    return 0;
}
