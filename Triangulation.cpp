#include"Triangulation.hpp"
//===================================================================================================================

	Triangulation::Triangulation(){}
	Triangulation::~Triangulation(){}

//===================================================================================================================


std::vector<Vertex>& Triangulation::vertices() {return vertices_ ; }


std::vector<Triangle>& Triangulation::triangles(){ return triangles_ ; }

int& Triangulation::refinement_level() { return refinement_level_  ;  }


//===================================================================================================================
int Triangulation::initialize(const char* file_name){

	std::ifstream input( file_name ) ;
	if (!input.is_open())
	{
		std::cerr << "Cannot open the file ( maybe wrong directory ! ) " << std::endl;
		return EXIT_FAILURE;
	}

	std::string line_string ;

	int total_vertex ;

	input >> total_vertex;  // read first number which shows number of vertices

	vertices_.clear();
	vertices_.resize(total_vertex);


	getline(input, line_string);   // for ignoring first line of input
	getline(input, line_string);   // for ignoring second line of input

	for (int i = 0 ; i < total_vertex  ; ++i)
	{
		input >> vertices_[i].vertex_index() >> vertices_[i].x() >> vertices_[i].y() ;

	}

	int total_triangle ;
	input >> total_triangle ;



	triangles_.clear();
	triangles_.resize(total_triangle);

	getline(input, line_string);   // for ignoring first line of input
	getline(input, line_string);   // for ignoring second line of input


	for (int i = 0 ; i < total_triangle  ; ++i)
	{
		int face[3] ;
		input >> face[0] >> face[1] >> face[2] ;
		vertices_[face[0] ].neighbours().push_back(face[1]) ;
		vertices_[face[0] ].neighbours().push_back(face[2]) ;

		triangles_[i].initialize(vertices_[face[0]],vertices_[face[1]],vertices_[face[2]]) ;
	}
	input.close() ;
	return 1 ;
}
//===================================================================================================================

void Triangulation::mid_vertex(Vertex& mid_vertex_1_2 , const Vertex& vertex1 , const Vertex& vertex2 )
	{
		mid_vertex_1_2.x() = 0.5*(vertex1.x() + vertex2.x()) ;
		mid_vertex_1_2.y() = 0.5*(vertex1.y() + vertex2.y()) ;
		mid_vertex_1_2.neighbours().clear() ;
	}
//===================================================================================================================
int Triangulation::find( const Vertex& vertex)
{
	for( int i=0 ; i != (int) vertices_.size() ; ++i )
	{
		if (vertices_[i].x() == vertex.x() && vertices_[i].y() == vertex.y() )
			return vertices_[i].vertex_index() ;
	}
	return -1 ;
}
//===================================================================================================================
void Triangulation::update_index()
{
	for( int i=0 ; i != (int) vertices_.size() ; ++i )
	{
			vertices_[i].vertex_index() = i ;
	}
}
//===================================================================================================================
void Triangulation::refinement()
{
	/* Sample refinement for triangle "012"
	                                     0
									  /		\
									 /		 \
								    0-1 ---- 0-2
								   /  \     /  \
								  /	   \   /	\
								 1 ---  1-2 ---- 2


	*/

	int count = 0 ;
	// Refinement
	while (count != refinement_level_ )
	{
		std::vector<Triangle> triangles_new ;
		int number_tri = triangles_.size();
		// Loop over all triangles
		for (int i=0; i<number_tri ; ++i)
			{
				Vertex vertex0 (triangles_[i].triangle()[0] ), vertex1(triangles_[i].triangle()[1]) , vertex2(triangles_[i].triangle()[2]) ;
				Vertex vertex0_1 , vertex0_2 , vertex1_2 ;

				mid_vertex( vertex0_1 , vertex0 , vertex1 ) ;
				mid_vertex( vertex0_2 , vertex0 , vertex2 ) ;
				mid_vertex( vertex1_2 , vertex1 , vertex2 ) ;

				// check that the current new mid-vertex is already exist or not
				int  a ;
				a = find( vertex0_1 );

				if (a == -1 )
					{
						vertices_.push_back(vertex0_1);
						vertex0_1.vertex_index() = (int) vertices_.size()-1 ;
					}
				else
					{
						vertex0_1 = vertices_[a] ;
					}
				update_index() ;
				// check that the current new mid-vertex is already exist or not
				int  b ;
				b = find( vertex0_2 );
				if (b == -1 )  /// should determine the repeated nodes
					{
						vertices_.push_back(vertex0_2);
						vertex0_2.vertex_index() = (int) vertices_.size()-1 ;
					}
				else
					{
						vertex0_2 = vertices_[b] ;
					}
				update_index() ;
				// check that the current new mid-vertex is already exist or not
				int  c ;
				c = find( vertex1_2 );
				if (c == -1 )  /// should determine the repeated nodes
					{
						vertices_.push_back(vertex1_2);
						vertex1_2.vertex_index() = (int) vertices_.size()-1 ;
					}
				else
					{
						vertex1_2 = vertices_[c] ;
					}
				update_index() ;

				Triangle triangle1(vertex0 , vertex0_1 , vertex0_2);
				Triangle triangle2(vertex1 , vertex0_1 , vertex1_2);
				Triangle triangle3(vertex2 , vertex0_2 , vertex1_2);
				Triangle triangle4(vertex0_1 , vertex0_2 , vertex1_2);

				triangles_new.push_back(triangle1);
				triangles_new.push_back(triangle2);
				triangles_new.push_back(triangle3);
				triangles_new.push_back(triangle4);


			}
		triangles_.clear() ;
		for(int i = 0 ; i!= (int) triangles_new.size() ; ++i)
			triangles_.push_back(triangles_new[i]) ;
		++count ;

	}
}
//===================================================================================================================


