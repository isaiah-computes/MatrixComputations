#include <stdexcept>
#include "RealVector.hpp"

RealVector::RealVector(unsigned int size)
{
	entries.resize(size);
}

double& RealVector::operator[](const unsigned int index)
{
	if (index >= entries.size()) throw std::out_of_range("Invalid index value.");
	return this->entries[index];
}

const double& RealVector::operator[](const unsigned int index) const
{
	if (index >= entries.size()) throw std::out_of_range("Invalid index value.");
	return this->entries[index];
}

RealVector RealVector::StandardBasis(unsigned int number_dimensions, unsigned int basis_dimension)
{
	RealVector v(number_dimensions);
	v[basis_dimension] = 1.0;
	return v;
}