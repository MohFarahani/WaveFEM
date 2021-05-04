#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include<iostream>
#include<vector>
#include"Vertex.hpp"
#include <cassert>

//*******************************************************************************************************************
/*!  Triangle class
*  In this class, we create one triangle.
*  For doing this, we need three different vertex
*
*/
//*******************************************************************************************************************

class Triangle {

public:
	Triangle() ;
	~Triangle() ;
	Triangle(Vertex& vertex1 , Vertex& vertex2 , Vertex& vertex3 ) ;
	void initialize(Vertex& vertex1 , Vertex& vertex2 , Vertex& vertex3 ) ;

	std::vector<Vertex>& triangle() ;
	const std::vector<Vertex>& triangle()const ;

	Triangle& operator= (const Triangle& ver) ;

private:

	std::vector<Vertex> triangle_ ;


};



#endif //TRIANGLE-H
