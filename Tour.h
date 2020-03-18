#pragma once

#include "CoordMatrix.h"
#include <vector>
#include <set>


class Tour
{
public:
	Tour();

	// Copy constructor
	Tour( const Tour& t );

	// Assignment operator
	Tour& operator=( const Tour& t );

	~Tour();

	void DoTwoOpt( const int& c1, 
		           const int& c2,
				   const int& c3,
				   const int& c4 );

	void DoThreeOpt( const int& c1, 
					 const int& c2,
					 const int& c3,
					 const int& c4,
					 const int& c5,
					 const int& c6 );

	double TourDistance() const;
	int TourSize() const;
	int GetCity( const int& index );
	void SetCity( const int& index, const int& value );

	void SetMatrix( CoordMatrix* mat );
	void CreateRandomTour();
	void CreateTour();
	void CreateNearestNeighbourTour();
	void Reset();
	void SetCities( const std::vector<int>& v );
	std::vector< int > cities;
private:	

	double Distance( const int& c1, 
		             const int& c2 ) const;	

	int GetNearestNeighbour( const int& c, std::set<int>& cset );

private:
//	std::vector< int > cities;
	CoordMatrix* matrix;
};

