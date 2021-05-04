#include "Matrix2d.hpp"



Matrix2d::~Matrix2d(){}
//===================================================================================================================
//
//  Constructors
//
//===================================================================================================================
Matrix2d::Matrix2d()
{
   // Default construct
	row_ = 0 ;
	col_ = 0 ;
	vector_.clear();
	vector_.resize( 1,0.0) ;
}



Matrix2d::Matrix2d( const int& num_row, const int & num_col)

{
	// construct 2D array
	row_ = num_row ;
	col_ = num_col ;

	vector_.clear();
	vector_.resize(row_*col_,0.0);
}


Matrix2d::Matrix2d(const Matrix2d& s): row_(s.row()),col_ (s.col())
{
	vector_.clear();
	vector_= s.get_vector() ;
}


//===================================================================================================================
//
//  Overloaded operator
//
//===================================================================================================================
// assignment operator
Matrix2d& Matrix2d::operator= (const Matrix2d& s)
{
	row_ = s.row() ;
	col_ = s.col() ;
	vector_.clear();
	vector_ = s.get_vector();
	return *this;
}

// Operator()
double& Matrix2d::operator ()(int i,int j)
{
	assert (i <= row_ ) ;
	assert( i>= 0 ) ;
	assert (j <= col_ ) ;
	assert( j>= 0 ) ;

   return vector_[j*row_ + i ];
}


// Operator() const
const double& Matrix2d::operator ()(int i,int j) const
{
	assert (i <= row_ ) ;
	assert( i>= 0 ) ;
	assert (j <= col_ ) ;
	assert( j>= 0 ) ;
   return vector_[j*row_ + i ];
}
//===================================================================================================================
//
//  Convenience Functions
//
//===================================================================================================================

//===================================================================================================================
//

//===================================================================================================================
//initialize the whole array with a constant value
void Matrix2d::fill( double value )
{
	  std::fill(vector_.begin(),vector_.end(),value);
}

//===================================================================================================================
// Print the whole array (for debugging purposes)
void Matrix2d::print()
{


		for (int i=0 ; i != row_ ; ++i)
		{
			for (int j=0 ; j != col_ ; ++j)
			{
				std::cout<< vector_[j*row_+i] <<"\t";

		}
			std::cout<< std::endl;
	}

}

//===================================================================================================================
// return the vector_
std::vector<double> Matrix2d::get_vector () const
{
	return vector_ ;
}

//===================================================================================================================
//

void Matrix2d::Resize(const int& num_row, const int & num_col)
{
	row_ = num_row ;
	col_ = num_col ;
	vector_.clear();
	vector_.resize(row_*col_,0.0);
}

//===================================================================================================================


