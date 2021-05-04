#include"Vertex.hpp"
//===================================================================================================================

	Vertex::Vertex() {}
	Vertex::~Vertex() {}

	Vertex::Vertex(const Vertex& vert): x_(vert.x()) , y_(vert.y()) , vertex_index_(vert.vertex_index() )
		{
			neighbours_.clear() ;
			neighbours_ = vert.neighbours() ;
		}


//===================================================================================================================
// Setter and Getter function
	double& Vertex::x() {return x_ ; }
	const double& Vertex::x() const {return x_ ; }

	double& Vertex::y() {return y_ ; }
	const double& Vertex::y() const {return y_ ; }

	int& Vertex::vertex_index() {return vertex_index_ ; }
	const int& Vertex::vertex_index() const {return vertex_index_ ; }

	std::vector<int>& Vertex::neighbours()  {return neighbours_; }
	const std::vector<int>& Vertex::neighbours() const  {return neighbours_ ; }




//===================================================================================================================
// overload operator
	// assignment operator
	Vertex& Vertex::operator= (const Vertex& ver)
	{
		x_ = ver.x() ;
		y_ = ver.y() ;
		vertex_index_ = ver.vertex_index_;
		neighbours_ = ver.neighbours();
		return *this;
	}

	bool operator==(const Vertex& lhs, const Vertex& rhs)
	{
		if( lhs.x() == rhs.x() && lhs.y() == rhs.y()  )
		{
			std::cout<< " lhs.index: " << lhs.vertex_index()<<" \t rhs.index: " << rhs.vertex_index()<< std::endl ;
			return true ;
		}
		else
		{
			return false ;
		}
	}


//===================================================================================================================
