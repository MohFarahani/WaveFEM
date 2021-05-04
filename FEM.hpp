#ifndef FEM_HPP
#define FEM_HPP

#include"Triangulation.hpp"

#include<map>
#include<cmath>
#include<iostream>
#include<fstream>
#include <algorithm>

#include<vector>
#include<cmath>

class FEM{
public:

	FEM() ;
	~FEM() ;
	FEM(double delta , double epsilon , int refinement_level , const char* filename ) ;
	std::vector< std::map<int,double> > & stiffness();
	std::vector< std::map<int,double> > & mass();
	std::vector<double>& k2() ;
	std::vector<double>& eigenmode() ;


	double epsilon() ;

	void calc_k2() ;
	void calc_stiffness_mass() ;

	std::vector< double> matrix_vector_multiplication(const std::vector< std::map<int,double> > &  A_or_M , const std::vector< double> & u) ;
	double vector_vector_multiplication(const std::vector< double > &  u_t , const std::vector< double> & u) ;
	double l2_norm( const std::vector< double> & u) ;
	void normalize( std::vector< double> & u) ;
	void GS(std::vector< double>& u , const std::vector< double>& f ) ;
	int CG(std::vector< double>& u , const std::vector< double>& f ) ;

	void calc_eigenmode() ;



	void write(const char* filename, const std::vector< std::map<int,double> >&  stiff_or_mass) ;
	void write(const char* filename, const std::vector< double> &  K2) ;
	void write(const char* filename ) ;


private:
	double delta_ ;
	double epsilon_ ;
	Triangulation grid_triangles_;
	std::vector< std::map<int,double> > stiffness_;
	std::vector< std::map<int,double> > mass_;
	std::vector<double>  k2_ ;
	std::vector<double>  eigenmode_ ;

};















#endif //FEM_HPP
