#include "FEM.hpp"
#include"myColsamm/Source/Colsamm.h"
using namespace ::_COLSAMM_;
#include"Global.hpp"

double my_func( double x, double y)
{
	return (100 + DELTA  ) * exp((-50)*((x*x)+(y*y))) - 100 ;
}

//===================================================================================================================
	FEM::FEM(){}
	FEM::~FEM(){}
	FEM::FEM(double delta, double epsilon , int refinement_lvl , const char* filename): delta_(delta) , epsilon_(epsilon)
	{
		grid_triangles_.initialize(filename) ;
		grid_triangles_.refinement_level() =  refinement_lvl ;
		grid_triangles_.refinement() ;
	}

	std::vector< std::map<int,double> > & FEM::stiffness(){
		return stiffness_ ;
	}
	std::vector< std::map<int,double> > & FEM::mass(){
		return mass_ ;
	}

	std::vector<double>& FEM::k2()
	{

		return k2_;
	}
	std::vector<double>& FEM::eigenmode()
	{

		return eigenmode_;
	}

	double FEM::epsilon() {return epsilon_ ;}
//===================================================================================================================


//===================================================================================================================
	void FEM::calc_stiffness_mass()
	{
		stiffness_.resize(grid_triangles_.vertices().size() ) ;
		mass_.resize(grid_triangles_.vertices().size() ) ;

		   // Loop fo all triangles
		   for (int i= 0 ; i !=(int) grid_triangles_.triangles().size();++i)
		   {

				 		 	 ELEMENTS::Triangle my_element;
				 		 	 std::vector<double> corners(6, 0.0);
				 		 	 // array corners contains the x- and y-coordinates of the
				 		 	 // triangle corners in the order x0, y0, x1, y1, x2, y2
				 		 	 Vertex vertex1 , vertex2 , vertex3 ;
				 		 	 vertex1 = grid_triangles_.triangles()[i].triangle()[0];
				 		 	 vertex2 = grid_triangles_.triangles()[i].triangle()[1];
				 		 	 vertex3 = grid_triangles_.triangles()[i].triangle()[2];

				 		 	 corners[0] = vertex1.x() ;  corners[1] = vertex1.y();
				 		 	 corners[2] = vertex2.x() ;  corners[3] = vertex2.y();
				 		 	 corners[4] = vertex3.x() ;  corners[5] = vertex3.y();
				 		 	 // pass the corners to the finite element
				 		 	 my_element(corners);

				 		 	std::vector< std::vector<double> > my_local_stiffness_matrix = my_element.integrate( grad(v_()) * grad(w_()) - func<double> (my_func) * v_() * w_()) ;
				 		 	std::vector< std::vector<double> > my_local_mass_matrix = my_element.integrate(v_() * w_());

				 		 	 for (int m = 0; m < 3; ++m)
				 		 	 	 {
				 		 		 	 for (int n = 0; n < 3; ++n)
				 		 		 	 {
								 		 int current_vertex_index   = ((grid_triangles_.triangles())[i].triangle())[m].vertex_index() ;
										 int neighbour_vertex_index = ((grid_triangles_.triangles())[i].triangle())[n].vertex_index() ;

				 		 		 		 stiffness_[current_vertex_index ]  [neighbour_vertex_index] += my_local_stiffness_matrix[m ][n];
										 mass_[current_vertex_index ] [neighbour_vertex_index] += my_local_mass_matrix[m][n];
				 		 		 	 }
				 		 	 	}

		   }
	}




//===================================================================================================================
	void FEM::calc_k2()
	{

		k2_.clear() ;
		k2_.resize(grid_triangles_.vertices().size() ) ;
		for (int i = 0 ; i != (int) (grid_triangles_.vertices()).size(); ++i )
			{

		           double x = grid_triangles_.vertices()[i].x() ;
		           double y = grid_triangles_.vertices()[i].y() ;
		           k2_[i] = (100 + delta_) * exp((-50)*((x*x)+(y*y))) - 100 ;

			}
	}
//===================================================================================================================
	void FEM::write(const char* filename, const std::vector< std::map<int,double> >&  stiff_or_mass)
		{

		   std::ofstream output(filename);


		   for (size_t i = 0; i < stiff_or_mass.size(); ++i)
		   {
		      std::map<int,double>::const_iterator it = stiff_or_mass[i].begin();

		      while (it != stiff_or_mass[i].end())
		      {
		    	  output << i << "\t" << it->first << "\t " << it->second << std::endl;
		         ++it;
		      }
		   }

		   output.close();
		}
//===================================================================================================================
void FEM::write(const char* filename, const std::vector< double> &  k2)
	{

		std::ofstream output(filename);

			   for (size_t i = 0; i != k2_.size(); ++i )
			   {

			    	  output << grid_triangles_.vertices()[i].x() << "\t" << grid_triangles_.vertices()[i].y() << "\t " << k2[i] << std::endl ;

			   }

			   output.close();
	}
//===================================================================================================================
void FEM::write(const char* filename )
	{

		std::ofstream output(filename);
		output<< grid_triangles_.vertices().size() << "\t vertices in the domain " << std::endl ;
  	    output << " index of vertex " << "\t" << " x coordinate " << "\t " << " y coordinate " << std::endl ;

			   for (size_t i = 0; i != (int) grid_triangles_.vertices().size(); ++i )
			   {

			    	  output << grid_triangles_.vertices()[i].vertex_index() << "\t" << grid_triangles_.vertices()[i].x() << "\t " << grid_triangles_.vertices()[i].y() << std::endl ;

			   }
		output << "\t ******************************************************************************************************************************************************************* " << std::endl ;
		output<< grid_triangles_.triangles().size() << "\t triangles in the domain " << std::endl ;
		output << " index of vertex 0 " << "\t" << " index of vertex 1 " << "\t " << " index of vertex 2 " << std::endl ;
		   for (size_t i = 0; i != (int) grid_triangles_.triangles().size(); ++i )
		   {

		    	  output << grid_triangles_.triangles()[i].triangle()[0].vertex_index() << "\t" << grid_triangles_.triangles()[i].triangle()[1].vertex_index() << "\t " << grid_triangles_.triangles()[i].triangle()[2].vertex_index() << std::endl ;

		   }
			   output.close();
	}
//===================================================================================================================
std::vector< double> FEM::matrix_vector_multiplication(const std::vector< std::map<int,double> > &  A_or_M , const std::vector< double> & u)
	{
		std::vector< double> f ;
		f.resize( grid_triangles_.vertices().size(),0.0 ) ;
		for (int i = 0 ; i != (int) grid_triangles_.vertices().size() ; ++i )
			for( std::map<int,double>::const_iterator it = A_or_M[i].begin() ; it != A_or_M[i].end(); ++it)
				f[i] += it->second * u[ it->first ];
		return f ;
	}
//===================================================================================================================

double FEM::vector_vector_multiplication(const std::vector< double > &  u_t , const std::vector< double> & u)
	{
		double sum = 0.0 ;
		for(int i= 0; i != (int) u.size(); ++i)
				sum += u[i] * u_t[i];

		return sum ;
	}
//===================================================================================================================
double FEM::l2_norm( const std::vector< double> & u)
	{
		double l2 = 0.0 ;
		for(int i= 0; i != (int) u.size(); ++i)
			l2 += u[i] * u[i];
		return l2 ;
	}
//===================================================================================================================
void FEM::normalize( std::vector< double> & u)
	{
		double l2norm = sqrt(1.0 / l2_norm(u) ) ;
		for(int i= 0; i != (int) u.size(); ++i)
				u[i] *=  l2norm ;
	}
//===================================================================================================================

void FEM::GS(std::vector< double>& u , const std::vector< double>& f )
{


	std::vector< double> u_old(u) ;
	std::vector< double> Error(u) ;

    double error(1.0) ;
    while( error > epsilon_ )

  	{

		 u_old = u ;

	     for(int i=0 ; i != (int) u.size() ; ++i )
	     {
	 		double temp(0.0) , coefficient(0.0) ;
	 			for( std::map<int,double>::const_iterator it = stiffness_[i].begin() ; it != stiffness_[i].end(); ++it)
	 			{
	 				if( i != (int) it->first )
	 				{
	 					temp += (it->second) * u[ it->first ] ;

	 				}
	 				else
	 				{
	 					coefficient = it->second ;

	 				}
	 			}
		    u[i] = (double) (f[i] - temp) / coefficient ;

	     }
	     for(int i=0 ; i != (int) u.size() ; ++i )
	     {

	    	 Error[i] = fabs( u[i] - u_old[i] ) ;

	     }
	     std::vector<double>::const_iterator it= max_element(Error.begin(), Error.end());
	     error = *it ;

  	}


}
//===================================================================================================================

int FEM::CG(std::vector< double>& u , const std::vector< double>& f )
{
	// From wikipedia algorithm

	std::vector< double> r(f) ;
	for (int i = 0 ; i != (int) r.size() ; ++i ){
		r[i]= f[i] - matrix_vector_multiplication(stiffness_, u)[i]  ;

	}

	double rsold,rsnew, alpha;

	int counter = 0;
	std::vector< double> p(r) ;
	rsold = vector_vector_multiplication( r , r) ;

	for(counter = 1; counter > 0; ++counter)
	{
		std::vector< double> Ap = matrix_vector_multiplication(stiffness_, p );

		alpha = (double) rsold / vector_vector_multiplication(Ap,p);

		for (int i = 0 ; i != (int) u.size() ; ++i )
			u[i] += alpha * p[i] ;

		for (int i = 0 ; i != (int) r.size() ; ++i )
			r[i] -= alpha * Ap[i] ;

		rsnew = vector_vector_multiplication( r , r ) ;

		if ( sqrt(rsnew)  < epsilon_) break;


		double rel = (double) rsnew/rsold ;
		for (int i = 0 ; i != (int) p.size() ; ++i )
			p[i] = r[i] + rel*p[i]  ;

		rsold = rsnew ;

	}
	return counter ;

}
//===================================================================================================================
void FEM::calc_eigenmode()
{

	std::vector< double> f ;
	f.resize( grid_triangles_.vertices().size(),0.0 ) ;

	// initialize
	eigenmode_.resize( grid_triangles_.vertices().size(),1.0 ) ;


	f = matrix_vector_multiplication(mass_ , eigenmode_ );

	double Lambda_New = (vector_vector_multiplication( eigenmode_ , matrix_vector_multiplication(stiffness_ , eigenmode_ ) ) ) / (vector_vector_multiplication( eigenmode_ , f ));
	double Lambda_Old(0.0);
	double RelativeError(1.0);

	while( RelativeError > 1e-10 )
	{
		Lambda_Old = Lambda_New;

		f = matrix_vector_multiplication(mass_ ,eigenmode_ );

		GS( eigenmode_ , f );
		//CG(eigenmode_ , f) ;

		normalize(eigenmode_);

		// update Lambda_New
		Lambda_New = (double) (vector_vector_multiplication( eigenmode_ , matrix_vector_multiplication(stiffness_ , eigenmode_ ) ) ) /  ( vector_vector_multiplication( eigenmode_ , matrix_vector_multiplication(mass_ , eigenmode_ ) ) )  ;

		RelativeError = fabs( (double) (Lambda_New-Lambda_Old) / Lambda_Old );
		std::cout<<"Lambda is : "<< Lambda_New << std::endl ;


	} ;



}

