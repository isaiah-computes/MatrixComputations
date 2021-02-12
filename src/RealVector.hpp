#ifndef MATRIXCOMPS_REALVECTOR_H
#define MATRIXCOMPS_REALVECTOR_H

#include <vector>

class RealVector {

private:

	std::vector<double> entries;

public:
	
	RealVector(unsigned int size);
	unsigned int Length() { return entries.size(); }
};

#endif