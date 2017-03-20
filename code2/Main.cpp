
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <assert.h>
#include "Main.hpp"

using namespace std; // somewhat frowned upon, but fine as long as nobody is dumb and collides with std...
const char nn = '\n';
vector<vector<int>> stras(vector<vector<int>> M1, vector<vector<int>> M2);
void printMatrix(vector<vector<int>> v, int d);


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
    vector<vector<int>> M1 (dimension, std::vector<int> (dimension, 0));
    vector<vector<int>> M2 (dimension, std::vector<int> (dimension, 0));
    
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
        vector<vector<int>> result = stras(M1, M2);
        printMatrix(result, dimension);
        cout << nn;
    }
    
    return 0;
}



void printMatrix(vector<vector<int>> v, int d) {
    for(int i = 0; i < d; i++) {
        for(int j = 0; j < d; j++) {
            cout << v[i][j] << " ";
        }
        cout << nn;
    }
}

vector<vector<int>> stras(vector<vector<int>> M1, vector<vector<int>> M2) {
    
    
    return M1; //TODO
}
