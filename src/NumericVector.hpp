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
	size_t Dimension() const { return entries.size(); }

	double& operator()(const size_t index);
	const double& operator()(const size_t index) const;
	double& At(const size_t index);
	const double& At(const size_t index) const;
};

#endif