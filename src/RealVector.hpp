#ifndef MATRIXCOMPS_REALVECTOR_H
#define MATRIXCOMPS_REALVECTOR_H

#include <vector>

class RealVector {

private:

	std::vector<double> entries;

public:
	
	RealVector(unsigned int size);
	unsigned int Length() { return entries.size(); }

	double& operator[](const unsigned int index);
	const double& operator[](const unsigned int index) const;

	static RealVector StandardBasis(unsigned int number_dimensions, unsigned int basis_dimension);
};

#endif