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

// make clean && make && echo "Starting..." && ./strassen 1 1024 "matrices.txt"

using namespace std; // somewhat frowned upon, but fine as long as nobody is dumb and collides with std...
using namespace chrono;
const char nn = '\n';


int main(int argc, const char * argv[]) {
    
    if(argc != 4) {
        cout << "Usage: ./strassen <flag> <dimension> <inputfile>" << nn;
        cout << "0: Staff, 1: Random" << nn;        
        return 1;
    }
    
    runTests();
    
    cout << "Tests Passed!" << nn;
    
    int flag = atoi(argv[1]);
    int dimension = round_up_to_power_of_2(atoi(argv[2]));
    // TODO return matrix should not have padding zeroes.
    
    vector<vector<long>> mm1 (dimension, vector<long> (dimension, 0));
    vector<vector<long>> mm2 (dimension, vector<long> (dimension, 0));
    Matrix M1 = Matrix(0, 0, dimension, &mm1);
    Matrix M2 = Matrix(0, 0, dimension, &mm2);
    
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
                (*M1.m)[i][j] = atoi(line.c_str());
            }
        }
        
        // Load matrix 2
        for(int i = 0; i < dimension; i++) {
            for(int j = 0; j < dimension; j++) {
                getline (matrixFile, line);
                (*M2.m)[i][j] = atoi(line.c_str());
            }
        }
        
        // execute strassen's algorithm, print the result.
        vector<vector<long>> om (dimension, vector<long> (dimension, 0));
        Matrix O = Matrix(0, 0, dimension, &om);
        Matrix result = strass(O, M1, M2, 64); // TODO bound
        
        printMatrix(result);
        
        cout << nn;
    }
    
    else if (flag == 1) {
        // Just use a random matrix with dimensions as proposed
        randFill(M1);
        randFill(M2);
        int bound = 16;
        long long prevTime = LLONG_MAX;
        
        while (bound < dimension) {
            auto begin = high_resolution_clock::now();
            vector<vector<long>> oRaw (dimension, vector<long> (dimension, 0));
            Matrix O = Matrix(0, 0, dimension, &oRaw);
            
            Matrix result = strass(O, M1, M2, bound);
            auto end = high_resolution_clock::now();
            auto time = duration_cast<nanoseconds>(end-begin).count();

            // If this bound resulted in worse performance than the previous bound, then the optimal bound was the last one.
            if (time > prevTime) {
                cout << result.d << nn; // no optimizey guy.
                cout << "proper bound: " << bound / 2 << nn;
                break;
            }
            
            prevTime = time;
            bound = bound * 2;
        }
        
    }
    
    cout << "Success!" << nn;
    
    return 0;
}
