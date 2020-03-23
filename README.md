truck uav
run: 

g++ -std=c++11 .\CoordMatrix.cpp .\Tour.cpp  .\TSPalgorithm.cpp .\main.cpp -o main

./main.exe

Tour.cpp: construct tour <vector>, function: CreateRandomTour(), CreateNearestNeighbourTour(), TourDistance(),....

CoordMatrix.cpp: Read text/tsp file data, calculates distances and generates DistanceMatrix.

TSPalgorithm.cpp: main algorithm : Two-opt , swap, path-relink, sTSP, mTSP. ( all available)

main.cpp: 


// Test single TSP

test.RunSingleTSP();

// Test mTSP

test.MultiTSP();




