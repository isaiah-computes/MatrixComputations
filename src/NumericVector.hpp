#ifndef MATRIXCOMPS_NUMVECTOR_H
#define MATRIXCOMPS_NUMVECTOR_H


#include <vector>
#include <ostream>
#include <initializer_list>

class NumericVector
{
private:
	std::vector<double> entries;

public:
	NumericVector(size_t number_elements);
	NumericVector(std::initializer_list<double> list);
	size_t Dimension() { return entries.size(); }
};

#endif