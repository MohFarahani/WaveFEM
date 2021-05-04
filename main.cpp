#include<iostream>
#include <fstream>
#include <string>
#include <sys/time.h>
#include <boost/lexical_cast.hpp>
#include"Global.hpp"
#include"FEM.hpp"
#include <stdlib.h>
using namespace boost;

//===================================================================================================================
int main( int argc, char** argv )
{
	   if(argc<4)
	    {
	      std::cerr << "waveguide <delta> <epsilon> <refinement>" << std::endl ;
		  return EXIT_FAILURE ;
	    }
	    DELTA = lexical_cast<double>(argv[1]);
		double epsilon = lexical_cast<double>(argv[2]);
		int refinement_level  = atoi( argv[3] ) ;
	    FEM fem( DELTA , epsilon , refinement_level , "inputs/unit_circle.txt") ;
	    fem.write("unit_circle.txt" ) ;
	    fem.calc_k2() ;
	    fem.write("ksq.txt" , fem.k2() ) ;
	    fem.calc_stiffness_mass() ;
	    fem.write("A.txt",fem.stiffness() ) ;
	    fem.write("M.txt",fem.mass() ) ;
	    fem.calc_eigenmode() ;
	    fem.write("eigenmode.txt" , fem.eigenmode() ) ;

	    return 0 ;
}
	    
