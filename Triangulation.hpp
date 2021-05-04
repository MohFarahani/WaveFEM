#ifndef TRIANGULATION_HPP
#define TRIANGULATION_HPP

#include<iostream>
#include<fstream>
#include<vector>
#include <algorithm>
#include<string>
#include"Vertex.hpp"
#include "Triangle.hpp"
#include <stdlib.h>

//*******************************************************************************************************************
/*!  Triangulation class
*  In this class, we create our triangular our domain. Therefore, we need to know about all of the vertex (which here store in vertices_)
*  and the relationship between each vertex ( which is in triangle) that stores in triangles_
*/
//*******************************************************************************************************************


class Triangulation {

public:
	Triangulation() ;
	~Triangulation() ;
	std::vector<Vertex>& vertices() ;
	std::vector<Triangle>& triangles();
	int& refinement_level() ;

	void mid_vertex(Vertex& mid_vertex_1_2 , const Vertex& vertex1 , const Vertex& vertex2 ) ;
	int find(const Vertex& vert) ;
	void update_index() ;

	int initialize(const char* file_name) ;
	void refinement() ;


private:

	std::vector<Vertex> vertices_;
	std::vector<Triangle> triangles_ ;
	int refinement_level_ ;


};



#endif //TRIANGULATION-H
