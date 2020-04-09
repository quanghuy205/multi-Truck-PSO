#pragma once

#include "Tour.h"
#include <string>

class Observer; 


class Particle
	{	public:
		std::vector <Tour> Solution;
		int pBest;
		std::vector <Tour> pBestSolution; 
		
	};	
	class AllParticle

	{	
		public:
    	std::vector <Particle> AllSolution;
    	int gBest;
		std::vector <Tour> gBestSolution;

	};

class TSPalgorithm
{
public:
	CoordMatrix matrix;
	const int NumberOfParticles = 50;
	const int NumberOfSalesman  = 2;
	const int MaxIteration   = 100;

	TSPalgorithm(void);
	~TSPalgorithm(void);

	void Initialize(// const int& iterations,
					 CoordMatrix* mat );
	void SetupMatrix(CoordMatrix *mat );
	void TwoOpt1(const int& t);
	void TwoOptSwap1( const int& i, const int& k, const int& t,const int& j) ;
	void TwoOptSwap( const int& i, const int& k );
	void SwapOperator(const int& t);
	void PathRelinkOperator(const int& t);
	void RunSingleTSP();	
	int GetTourCity( const int& index );
	void CreateSolution();
	void InitBestValue (CoordMatrix* mat);
	void MultiTSP(); 
	int CalculatepBest();
	int CalculategBest();
	void UpdateBest(); 
	Tour tour;
	Tour new_tour;
	Tour new_tour1;
	Tour temp_tour;
	Tour guide_tour;
	
	
	
	AllParticle A;

	
	
private:
	void TwoOpt();
	void ThreeOpt();
	


private:
	

	int iterations;
	 std::vector<Observer*> ob_set; 
};

