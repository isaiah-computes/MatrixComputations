#include "NumericVector.hpp"

NumericVector::NumericVector(size_t number_elements)
{
	entries.resize(number_elements);
}

NumericVector::NumericVector(std::initializer_list<double> list) : entries(list) {}