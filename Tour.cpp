
#include "Tour.h"
#include <algorithm>
#include <functional>


Tour::Tour(void)
{
}


Tour::~Tour(void)
{
}


// Copy constructor
Tour::Tour( const Tour& t )
{
	cities = t.cities;
}

// Assignment operator
Tour& Tour::operator=( const Tour& t )
{
	if ( this != &t )
	{
		cities = t.cities;
	}

	return *this;
}




// Get total distance of tour
double Tour::TourDistance() const
{
	double dist = 0.0;

	int size = (int) cities.size();
	int c1, c2;

	for ( int i = 0; i < size - 1; i++ )
	{
		c1 = cities.at( i );
		c2 = cities.at( i + 1 );
		dist += Distance( c1, c2 );
	} 

	// And back to the beginning city
	c1 = cities.at( size - 1 );
	c2 = cities.at( 0 );
	dist += Distance( c1, c2 );

	return dist;
}


// Generate arbitrary tour
void Tour::CreateRandomTour()
{
	Reset();

	for ( int i = 0; i < matrix->size(); i++ )
	{
		cities.push_back( i );
	}

	random_shuffle( cities.begin() + 1, cities.end() );
}

// Generate arbitrary tour
void Tour::CreateTour()
{
	Reset();

	for ( int i = 0; i < matrix->size(); i++ )
	{
		cities.push_back( i );
	}
}


// Get distance bewteen selected cities
double Tour::Distance( const int& c1, 
		               const int& c2 ) const
{
	return matrix->Distance( c1, c2 );
}


// Set pointer to cost / distance matrix object
void Tour::SetMatrix( CoordMatrix* mat )
{
	matrix = mat;
}


// Reset existing tour data
void Tour::Reset()
{
	std::vector< int >().swap( cities );
}

// Return the number of cities in the tour
int Tour::TourSize() const
{
	return (int) cities.size();
}

// Get the tour city, given the index passed to it
int Tour::GetCity( const int& index )
{
	int node = cities.at( index );
	return node;
}


// Get tour from the set of nearest neighbours
void Tour::CreateNearestNeighbourTour()
{
	Reset();

	std::set<int> city_set;
	std::set<int>::iterator it;

	for ( int i = 0; i < matrix->size(); i++ )
	{
		city_set.insert( i );
	}

	int city = 0;	
	
	for ( int i = 1; i <= matrix->size(); i++ )
	{
		// Add city to tour
		cities.push_back( city );

		// Remove city from unique set
		it = city_set.find( city );
		city_set.erase( it );

		city = GetNearestNeighbour( city, city_set );		
	}
}

// Get the nearest node to this one
int Tour::GetNearestNeighbour( const int& c, std::set<int>& cset )
{
	int city = 0;

	// Get minimum distance node
	double min_dist = 99999999;
	std::set<int>::iterator cit;

	 for ( cit = cset.begin(); cit != cset.end(); cit++ )
	 {
		 int n = *cit;

		 if ( n == c ) continue;

		 double dist = Distance( c, n );
		
		 if ( dist < min_dist )
		 {
			city = n;
			min_dist = dist;
		 }
	 }
    
	return city;
}

// Set the cities
void Tour::SetCities( const std::vector<int>& v )
{
	cities = v;
}

void Tour::SetCity( const int& index, const int& value )
{
	cities[ index ] = value;
}