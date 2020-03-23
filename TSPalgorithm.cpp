
#include "TSPalgorithm.h"

#include <iostream>
#include <functional>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <random>
#include <chrono>
#include <vector>  
using namespace std;
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
	temp_tour.SetMatrix(mat);
	guide_tour.SetMatrix(mat);
	new_tour1.SetMatrix( mat );
	
	//iterations = iter;
}

void TSPalgorithm::SetupMatrix(CoordMatrix *mat )
{
	for (int i = 0; i < NumberOfParticles; i++)
	{
		for (int j = 0; j <NumberOfSalesman; j++) 
		{
			A.AllSolution.at(i).Solution.at(j).SetMatrix(mat);
		}
	}

}

default_random_engine dre (chrono::steady_clock::now().time_since_epoch().count());     // provide seed
int random (int lim)
{
    uniform_int_distribution<int> uid {1,lim};   // help dre to generate nos from 0 to lim (lim included);
    return uid(dre);    // pass dre as an argument to uid to generate the random no
}

// Run the optimization algorithm
void TSPalgorithm::RunSingleTSP()
{
	tour.Reset();	
	
	// Create the known optimal tour 
	int ct[ 5 ] = {10,1,38,8,31};
	for ( int i = 0; i < 5; i++ ) ct[ i ]--;	
	std::vector<int> v( ct, ct + 5 );
	tour.SetCities( v );

	std::cout << std::endl << "Optimal solution: "<< tour.TourDistance() << std::endl;
	//Create random tour
  //  tour.Reset();  
  //  tour.CreateRandomTour();     
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
					for (int i = 0; i < tour.TourSize(); i++) 
					{
						std::cout << tour.cities.at(i) << " " ; 
					}
					std::cout << std::endl;

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



void TSPalgorithm::TwoOpt1(const int& t)
{
	for (int j = 0; j < A.AllSolution.at(t).Solution.size(); j++)
	{
			// Get tour size
		int size = A.AllSolution.at(t).Solution.at(j).TourSize();

		new_tour = A.AllSolution.at(t).Solution.at(j);

		// repeat until no improvement is made 
		int improve = 0;

		while ( improve < 20 )
		{
			double best_distance = A.AllSolution.at(t).Solution.at(j).TourDistance();

			for ( int i = 1; i < size - 1; i++ ) 
			{
				for ( int k = i + 1; k < size; k++) 
				{
					TwoOptSwap1( i, k,t,j );

					double new_distance = new_tour.TourDistance();

					if ( new_distance < best_distance ) 
					{	

						// Improvement found so reset
						improve = 0;
						A.AllSolution.at(t).Solution.at(j) = new_tour;
						best_distance = new_distance;
						// for (int i = 0; i < A.AllSolution.at(t).Solution.at(j).TourSize(); i++) 
						// {
						// 	std::cout << A.AllSolution.at(t).Solution.at(j).cities.at(i) << " " ; 
						// }
						// std::cout << std::endl;

					}
				}
			}

			improve ++;
		}
	}
}
	


void TSPalgorithm::TwoOptSwap1( const int& i, const int& k, const int& t, const int& j ) 
{
	int size = A.AllSolution.at(t).Solution.at(j).TourSize();
    // 1. take route[0] to route[i-1] and add them in order to new_route
	for ( int c = 0; c <= i - 1; ++c )
	{
		new_tour.SetCity( c, A.AllSolution.at(t).Solution.at(j).GetCity( c ) );
	}
    
	// 2. take route[i] to route[k] and add them in reverse order to new_route
	int dec = 0;
	for ( int c = i; c <= k; ++c )
	{
		new_tour.SetCity( c, A.AllSolution.at(t).Solution.at(j).GetCity( k - dec ) );
		dec++;
	}

    // 3. take route[k+1] to end and add them in order to new_route
	for ( int c = k + 1; c < size; ++c )
	{
		new_tour.SetCity( c, A.AllSolution.at(t).Solution.at(j).GetCity( c ) );
	}
	
}
 
void TSPalgorithm::SwapOperator(const int& t) 
{	

	int size = A.AllSolution.at(t).Solution.size();	
	int randTour1 = 0;
	int randTour2 = 1;	
	if (size >= 3)
	{
		 randTour1 = random(size-1);
		 randTour2 = random(size-1);
	
		while(randTour2 == randTour1) 
		{
			randTour2 = random(size-1);
		}
	} 
	

		
	//	cout << A.AllSolution.at(t).Solution.at(randTour1).TourSize() << " ";
	//	cout << A.AllSolution.at(t).Solution.at(randTour2).TourSize() << " ";

		int randCity1= random(A.AllSolution.at(t).Solution.at(randTour1).TourSize()-1);
		int randCity2 = random(A.AllSolution.at(t).Solution.at(randTour2).TourSize()-1);
	//	cout << randTour1 <<" " << randTour2 <<" "<< randCity1 <<" "<< randCity2 <<" " << endl;
		int temp = A.AllSolution.at(t).Solution.at(randTour1).GetCity(randCity1);
		A.AllSolution.at(t).Solution.at(randTour1).SetCity(randCity1, A.AllSolution.at(t).Solution.at(randTour2).GetCity(randCity2));
		A.AllSolution.at(t).Solution.at(randTour2).SetCity(randCity2,temp);
	}

void TSPalgorithm::InitBestValue (CoordMatrix* mat) {
		//callculate pBest and gBest

	for (int i = 0; i < NumberOfParticles; i++)
	{
		A.AllSolution.at(i).pBest = A.AllSolution.at(i).Solution.at(0).TourDistance();
		A.AllSolution.at(i).pBestSolution = A.AllSolution.at(i).Solution;
		for (int j = 1; j < NumberOfSalesman; j++) 
		{
			A.AllSolution.at(i).pBest += A.AllSolution.at(i).Solution.at(j).TourDistance();
		}
	}

	A.gBest = A.AllSolution.at(0).pBest;
	A.gBestSolution = A.AllSolution.at(0).Solution;

	for (int i = 1; i < NumberOfParticles; i++) 
	{
		if (A.gBest > A.AllSolution.at(i).pBest)
		{
			A.gBest = A.AllSolution.at(i).pBest;
			A.gBestSolution = A.AllSolution.at(i).Solution;
		}
	}
	for (int j = 0; j <A.gBestSolution.size(); j++) 
	{
		A.gBestSolution.at(j).SetMatrix(mat);
	}
	
	for (int i = 0; i < NumberOfParticles; i++)
	{
		for (int j = 0; j <NumberOfSalesman; j++) 
		{
			A.AllSolution.at(i).pBestSolution.at(j).SetMatrix(mat);
		}
	}
} 

void TSPalgorithm::UpdateBest() 
{	 			
	for (int i = 0; i < NumberOfParticles; i++)
	{	
		int temp = A.AllSolution.at(i).Solution.at(0).TourDistance();
		// AllSolution.at(i).pBest = AllSolution.at(i).Solution.at(0).TourDistance()	
		// AllSolution.at(i).pBestSolution = AllSolution.at(i).Solution;
		for (int j = 1; j < NumberOfSalesman; j++) 
		{
			temp += A.AllSolution.at(i).Solution.at(j).TourDistance();	
		}
		
		if (temp < A.AllSolution.at(i).pBest) 
		{
		    A.AllSolution.at(i).pBest = temp;
			A.AllSolution.at(i).pBestSolution = A.AllSolution.at(i).Solution;
		}
	}

		int temp = A.AllSolution.at(0).pBest;
		int temp_index = 0;
		for (int i = 1; i < NumberOfParticles; i++) 
		{
			if (temp > A.AllSolution.at(i).pBest)
			{
				temp = A.AllSolution.at(i).pBest;
				temp_index = i;
			}
		}
		if (temp < A.gBest) 
		{
			A.gBest = temp;
			A.gBestSolution = A.AllSolution.at(temp_index).Solution;
		}

			
}


void TSPalgorithm::PathRelinkOperator(const int& t)
{	

    int size = A.AllSolution.at(t).Solution.size();
	//cout << size << endl;
	//cout << size;
	for (int k = 0; k < size; k++)
	{	
		
		temp_tour = A.AllSolution.at(t).Solution.at(k);
		new_tour1 = A.AllSolution.at(t).Solution.at(k);
		guide_tour = A.AllSolution.at(t).pBestSolution.at(k);
		//cout << new_tour1.TourDistance() << endl;
	
		int improve = 0;
		
		while (improve < 20)
		{
			double best_distance = new_tour1.TourDistance();
			for (int i = 0; i < temp_tour.TourSize() - 1; i++)
			{	
	
				if (guide_tour.cities.at(i) == temp_tour.cities.at(i)) break;
			//	cout << i;
				
				
				vector <int>::iterator it = find (temp_tour.cities.begin(),temp_tour.cities.end(),guide_tour.cities.at(i));
				int pos = std::distance(temp_tour.cities.begin(), it);
				//cout << pos;
				swap(temp_tour.cities.at(pos),temp_tour.cities.at(i));

				double new_distance = temp_tour.TourDistance();
				if (new_distance < best_distance)
				{
					improve = 0;
					new_tour1 = temp_tour;
					best_distance = new_distance;
				}
			}
			improve++;
		}
		if (new_tour1.TourDistance()  < A.AllSolution.at(t).Solution.at(k).TourDistance()) 
		{
			A.AllSolution.at(t).Solution.at(k) = new_tour1;
		}
	}
	UpdateBest();	
    
}


void TSPalgorithm::MultiTSP()
{	
	
	CoordMatrix matrix;
    
    // readTSP file
    matrix.Initialize("att48.tsp");
    
   std::cout << "Problem name: "<<  matrix.GetFileTitle() << std::endl;
    // Initialize algorithm
    Initialize(&matrix);

	
	tour.CreateRandomTour();
	int tour_size = tour.TourSize() ;
	
//	std::cout <<std::endl<< tour_size << std::endl;
	//Set the upper limit (number of cities to be visited per salesman)

	int UpperLimit = (int) ((tour_size - 1 + NumberOfSalesman)/NumberOfSalesman) + 1;

//	std::cout << UpperLimit;
	

//	std::vector <int> temp(1,0);

//Initialize popuplation and number of visited cities each salesman
	A.AllSolution.resize(NumberOfParticles);

	for (int i = 0; i < NumberOfParticles; i++) {
		A.AllSolution.at(i).Solution.resize(NumberOfSalesman);
	}
	SetupMatrix(&matrix);
	


	
// create random solutions
	
	int index = 1;
	std::vector <int> temp;

	for (int i = 0; i < NumberOfParticles; i++ ) 
	{	
		index = 1;	
		temp.clear();
		for (int j = 0; j < NumberOfSalesman; j++) 
		{
			if (j == NumberOfSalesman - 1) {
				temp.assign((tour.cities.begin() + index) , tour.cities.end());
			} else
			{
				temp.assign((tour.cities.begin() + index) , (tour.cities.begin() + index + UpperLimit - 1));
			}
			
			
			random_shuffle( temp.begin() + 1, temp.end() );
			temp.insert(temp.begin(), 0);
			A.AllSolution.at(i).Solution.at(j).SetCities(temp);
			index += UpperLimit - 1;
		}
	}

	InitBestValue(&matrix);
	

		int tempdis = A.gBestSolution.at(0).TourDistance();
	cout << endl;
	 for (int j = 0; j < NumberOfSalesman; j++)
		{	
			
			cout << "Salesman " << j << ": ";
			for (int k = 0; k < A.gBestSolution.at(j).cities.size(); k++)
			{	
				
				std::cout << " " << A.gBestSolution.at(j).cities.at(k) << " ";
			}
			if (j != 0)
			{
				tempdis = tempdis +  A.gBestSolution.at(j).TourDistance();
			}
				
			std::cout << std::endl << "Tour Distance: " << A.gBestSolution.at(j).TourDistance() << std::endl;
		} 
		cout << "Total tour length: " << tempdis << endl;

	//main algorithm

	
	for (int i = 0; i < MaxIteration; i++)
	{	
		UpdateBest();
		cout << i << endl;
		for (int t = 0; t < NumberOfParticles; t++) 
		{
	
			// TwoOpt1(t);
		
			// PathRelinkOperator(t);
	
			// SwapOperator(t);
			int RandomNumber = random(3);
			//std::cout << RandomNumber << " " ;
			
			if (RandomNumber == 1) 
			{
				TwoOpt1(t);
			} else
			{
				if (RandomNumber == 2)
				{
					PathRelinkOperator(t);
				} else
				{
					if (RandomNumber == 3)
					{
						SwapOperator(t);
					}
				  }

			}	
	 }	
	}
		
	cout <<endl <<  "Tour after mTSP: "	<< endl;
	

	tempdis = A.gBestSolution.at(0).TourDistance();
	cout << endl;
	 for (int j = 0; j < NumberOfSalesman; j++)
		{	
			
			cout << "Salesman " << j << ": ";
			for (int k = 0; k < A.gBestSolution.at(j).cities.size(); k++)
			{	
				
				std::cout << " " << A.gBestSolution.at(j).cities.at(k) << " ";
			}
			if (j != 0)
			{
				tempdis = tempdis +  A.gBestSolution.at(j).TourDistance();
			}
				
			std::cout << std::endl << "Tour Distance: " << A.gBestSolution.at(j).TourDistance() << std::endl;
		} 
		cout << "Total tour length: " << tempdis;

	
}
	
		
