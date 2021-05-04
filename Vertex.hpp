#ifndef Vertex_HPP
#define Vertex_HPP

#include<iostream>
#include<vector>

//*******************************************************************************************************************
/*!  vertex class
*  In this class, we define a Vertex or (node) which have the following condition:
*  1- X position, Y position of node
*  2- Index of the node
*  3- It should store the index of neighbour nodes which have a connection(edge) with this node.
*
*/
//*******************************************************************************************************************
class Vertex {
public:
	Vertex() ;
	~Vertex() ;
	Vertex(const Vertex& vert) ;

	double& x() ;
	const double& x() const ;

	double& y() ;
	const double& y()const ;

	int& vertex_index() ;
	const int& vertex_index() const ;

	std::vector<int>& neighbours() ;
	const std::vector<int>& neighbours() const ;


	Vertex& operator= (const Vertex& ver) ;


private:
	double x_ ;									// "X" position of the vertex
	double y_ ;									// "Y" position of the vertex
	int vertex_index_ ;							// index of the vertex
	std::vector<int> neighbours_ ;				// index of the vertex of it's neighbour


};

bool operator==(const Vertex& lhs, const Vertex& rhs) ;


#endif //Vertex-H
