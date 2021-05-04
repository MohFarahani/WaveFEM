#ifndef Matrix2d_H
#define Matrix2d_H



#include <vector>
#include <algorithm>    // std::fill
#include <iostream>
#include <cassert>
//*******************************************************************************************************************
/*!  Matrix class 2  dimensions
*  In this class, we define 2-dimensional Matrix which can calculate every Matrix operator
*  such as Multiplication of two Matrix, vector to Matrix, Salar to Matrix, addition of two matrix, print like matrix form and so on.
*/
//*******************************************************************************************************************
class Matrix2d
{
public:

   // Default Constructor
   Matrix2d();
   ~Matrix2d();
   // Constructors
   Matrix2d( const int& x_points, const int & y_points);


   // copy constructor
   Matrix2d(const Matrix2d& s);

   // assignment operator
   Matrix2d& operator= (const Matrix2d& s);


   // Access Operators
   double & operator () ( int i ,int j );
   // for const Arrays the following access operators are required
   const double&  operator () ( int i ,int j ) const;



   // initialize the whole array with a constant value
   void fill( double value );



   // return xSize &  ySize
   int row() {return row_ ; }
   int col() {return col_ ; }
   const int row() const {return row_ ; }
   const int col() const {return col_ ; }





   // resize the vector_
   std::vector<double>  get_vector () const;

   void Resize(const int& x_points, const int & y_points) ;


   // Print the whole content in Matrix2d ( for debugging purposes )
   void print();
   void write_plot( Matrix2d u ,  const std::string& filename ) ;

private:

 std::vector<double>  vector_;
 int row_;
 int col_;

};


//===================================================================================================================
//
//  Inline Access Operators and Sizes
//
//===================================================================================================================







#endif //Matrix2d_H

