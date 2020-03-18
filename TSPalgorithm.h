#pragma once

#include "Tour.h"
#include <string>

class Observer; 

class TSPalgorithm
{
public:
	TSPalgorithm(void);
	~TSPalgorithm(void);

	void Initialize(// const int& iterations,
					 CoordMatrix* mat );

	void TwoOptSwap( const int& i, const int& k );

	void RunSingleTSP();	
	int GetTourCity( const int& index );

	void MultiTSP(); 

private:
	void TwoOpt();
	void ThreeOpt();

private:
	Tour tour;
	Tour new_tour;

	int iterations;
	 std::vector<Observer*> ob_set; 
};

