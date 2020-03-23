#include <iostream>
#include "CoordMatrix.h"
#include "Tour.h"
#include "TSPalgorithm.h"

using namespace std;
int main() {

    //CoordMatrix matrix;
    TSPalgorithm test;
    // readTSP file
  //  matrix.Initialize("att48.tsp");
    
    //cout << "Problem name: "<<  matrix.GetFileTitle() << endl;
    // Initialize algorithm
  //  test.Initialize(&matrix);

    // Test single TSP
 //  test.RunSingleTSP();
    // Test mTSP
   // cout << matrix.distMatrix(0,1);
   test.MultiTSP();
    
}