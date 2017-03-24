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

// make clean && make && echo "Starting..." && ./strassen 0 256 "matrices.txt"
// make clean && make && echo "Starting..." && ./strassen 1 1024 "matrices.txt"
// for ((i=1; i <=131072; i++)); do echo $(((RANDOM % 10)+1)) >> matrices.txt; done

// somewhat frowned upon, fine as long as nobody is dumb and collides with std...
using namespace std;
using namespace chrono;
const char nn = '\n';

int CROSSOVER = 64;

int main(int argc, const char * argv[]) {
    
    if(argc != 4) {
        cout << "Usage: ./strassen <flag> <dimension> <inputfile>" << nn;
        cout << "0: Staff, 1: Find Optimal" << nn;
        return 1;
    }
    
    int flag = atoi(argv[1]);
    
    if (flag != 0) {
        runTests();
        cout << "Tests Passed!" << nn;
    }
    
    int originalDimension = atoi(argv[2]);
    int d = round_up_to_power_of_2(originalDimension);
    
    rawMatrix mm1 (d, rawRow (d, 0));
    rawMatrix mm2 (d, rawRow (d, 0));
    Matrix M1 = Matrix(0, 0, d, make_shared<rawMatrix>(mm1));
    Matrix M2 = Matrix(0, 0, d, make_shared<rawMatrix>(mm2));
    
    
    // Desired output for the Staff
    if (flag == 0) {
        ifstream matrixFile (argv[3]); // Open infile
        string line; // String buffer
        
        if (!matrixFile.is_open()) {
            cout << "Error: Could not open infile!" << nn;
            return 1;
        }
 
        // Load matrix 1
        for(int i = 0; i < d; i++) {
            for(int j = 0; j < d; j++) {
                getline (matrixFile, line);
                int x = atoi(line.c_str());
                (*M1.m)[i][j] = x;
            }
        }
        
        // Load matrix 2
        for(int i = 0; i < d; i++) {
            for(int j = 0; j < d; j++) {
                getline (matrixFile, line);
                (*M2.m)[i][j] = atoi(line.c_str());
            }
        }
        
        // Matrix Buffer (unused for now)
        rawMatrix b (d * 2, rawRow (d * 2, 0));
        Matrix buffer = Matrix(0, 0, d * 2, make_shared<rawMatrix>(b));
        
        // execute strassen's algorithm, print the result.
        Matrix result = strass(buffer, M1, M2, CROSSOVER);
        
        // Matrix check = mult(M1, M2);
        // assert(compare(result, check));
        
        result.d = originalDimension;
        staffPrint(result);
    }
    
    // Run trials to find the optimum crossover point
    else if (flag == 1) {
        randFill(M1);
        randFill(M2);
        
        int cross = 16; // Start at a reasonable number, otherwise it takes forever
        long long prevTime = LLONG_MAX;
        
        while (cross < d) {
            auto begin = high_resolution_clock::now();
    
            rawMatrix b (d * 2, rawRow (d * 2, 0));
            Matrix buffer = Matrix(0, 0, d * 2, make_shared<rawMatrix>(b));
            
            Matrix result = strass(buffer, M1, M2, cross);
            auto end = high_resolution_clock::now();
            auto time = duration_cast<nanoseconds>(end-begin).count();

            // If this bound resulted in worse performance than the previous bound,
            // then the optimal bound was the last one.
            if (time > prevTime) {
                cout << result.d << nn;
                cout << "Optimal crossover: " << cross / 2 << nn; // previous one
                break;
            }
            
            prevTime = time;
            cross = cross * 2;
        }
    }
    
    return 0;
}
