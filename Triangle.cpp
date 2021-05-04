#include "Triangle.hpp"

//===================================================================================================================
// Constructor and destructor
	Triangle::Triangle()
	{
		triangle_.clear() ;
		triangle_.resize(3 ) ;
	}
	Triangle::~Triangle(){}

	Triangle::Triangle(Vertex& vertex1 , Vertex& vertex2 , Vertex& vertex3 )
	{
		triangle_.clear() ;
		triangle_.resize(3 ) ;

		assert( !(vertex1==vertex2) && "Two vertex are same in one Triangle ! ") ;
		assert( !(vertex2==vertex3) && "Two vertex are same in one Triangle ! ") ;
		assert( !(vertex1==vertex3) && "Two vertex are same in one Triangle ! ") ;

		triangle_[0] = vertex1 ;
		triangle_[1] = vertex2 ;
		triangle_[2] = vertex3 ;


	}
//===================================================================================================================
// Setter and Gettre function
	std::vector<Vertex>& Triangle::triangle()
			{
				return triangle_ ;
			}
	const std::vector<Vertex>& Triangle::triangle()const
			{
				return triangle_ ;
			}
//===================================================================================================================


	void Triangle::initialize(Vertex& vertex1 , Vertex& vertex2 , Vertex& vertex3 )
	{
		triangle_.clear() ;
		triangle_.resize(3 ) ;
		assert( !(vertex1==vertex2) && "Two vertex are same in one Triangle ! ") ;
		assert( !(vertex2==vertex3) && "Two vertex are same in one Triangle ! ") ;
		assert( !(vertex1==vertex3) && "Two vertex are same in one Triangle ! ") ;

		triangle_[0] = vertex1 ;
		triangle_[1] = vertex2 ;
		triangle_[2] = vertex3 ;

	}


//===================================================================================================================
Triangle& Triangle::operator= (const Triangle& tri )
{
	triangle_ .clear() ;
	for(int i = 0 ; i!=3 ; ++i)
		triangle_.push_back(tri.triangle()[i]) ;
	return *this;
}




