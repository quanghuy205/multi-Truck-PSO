
#include "TSPalgorithm.h"
#include <iostream>

TSPalgorithm::TSPalgorithm(void)
{
}


TSPalgorithm::~TSPalgorithm(void)
{
}


// Set up TSP problem to run
void TSPalgorithm::Initialize( //const int& iter,
							   CoordMatrix* mat )
{
	// Set the matrix pointer for Tour object
	tour.SetMatrix( mat );
	new_tour.SetMatrix( mat );

	//iterations = iter;
}


// Run the optimization algorithm
void TSPalgorithm::RunSingleTSP()
{
	tour.Reset();	
	
	// Create the known optimal tour 
	int ct[ 48 ] = {1,8,38,31,44,18,7,28,6,37,19,27,17,43,30,36,46,33,20,47,21,32,39,48,5,42,24,10,45,35,4,26,2,29,34,41,16,22,3,23,14,25,13,11,12,15,40,9 };
	for ( int i = 0; i < 48; i++ ) ct[ i ]--;	
	std::vector<int> v( ct, ct + 48 );
	tour.SetCities( v );

	std::cout << std::endl << "Optimal solution: "<< tour.TourDistance() << std::endl;
	//Create random tour
    tour.Reset();  
    tour.CreateNearestNeighbourTour();     
	std::cout <<"Random Tour: " << tour.TourDistance() << std::endl;
    
	TwoOpt();  

	std::cout <<"Tour after TwoOpt: "<< tour.TourDistance()<< std::endl;
	
	for (int i = 0; i < tour.TourSize(); i++) 
	{
		std::cout << tour.cities.at(i) << " " ; 
	}


}


// Get the tour node, given the index
int TSPalgorithm::GetTourCity( const int& index )
{
	int node = tour.GetCity( index );
	return node;
}


// Do all 2-opt combinations
void TSPalgorithm::TwoOpt()
{
	// Get tour size
	int size = tour.TourSize();

	new_tour = tour;

	// repeat until no improvement is made 
	int improve = 0;

	while ( improve < 20 )
	{
		double best_distance = tour.TourDistance();

		for ( int i = 0; i < size - 1; i++ ) 
		{
			for ( int k = i + 1; k < size; k++) 
			{
				TwoOptSwap( i, k );

				double new_distance = new_tour.TourDistance();

				if ( new_distance < best_distance ) 
				{
					// Improvement found so reset
					improve = 0;
					tour = new_tour;
					best_distance = new_distance;
					
				}
			}
		}

		improve ++;
	}
}



void TSPalgorithm::TwoOptSwap( const int& i, const int& k ) 
{
	int size = tour.TourSize();
	
    // 1. take route[0] to route[i-1] and add them in order to new_route
	for ( int c = 0; c <= i - 1; ++c )
	{
		new_tour.SetCity( c, tour.GetCity( c ) );
	}
    
	// 2. take route[i] to route[k] and add them in reverse order to new_route
	int dec = 0;
	for ( int c = i; c <= k; ++c )
	{
		new_tour.SetCity( c, tour.GetCity( k - dec ) );
		dec++;
	}

    // 3. take route[k+1] to end and add them in order to new_route
	for ( int c = k + 1; c < size; ++c )
	{
		new_tour.SetCity( c, tour.GetCity( c ) );
	}
	
}
void TSPalgorithm::MultiTSP()
{	
	//Initialize the parameters
	const int MaxIteration = 100;
	const int NumberOfSalesman = 5;
	tour.CreateRandomTour();
	int tour_size = tour.TourSize() ;
	std::cout <<std::endl<< tour_size << std::endl;
	//Set the upper limit (number of cities to be visited per salesman)

	int UpperLimit = (int) ((tour_size - 1 + NumberOfSalesman)/NumberOfSalesman) + 1;

	std::cout << UpperLimit;
	
	std::vector <Tour> Solution;
	std::vector <int> temp(1,0);
	// for (int i = 0; i < UpperLimit; i++ ) {
	// 	Solution.at(i).SetCities(temp);
	// }
}
