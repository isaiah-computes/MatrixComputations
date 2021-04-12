#include "NumericVector.hpp"

NumericVector::NumericVector(size_t number_elements)
{
	entries.resize(number_elements);
}

NumericVector::NumericVector(std::initializer_list<double> list) : entries(list) {}

double& NumericVector::At(const size_t index)
{
	if (index >= entries.size()) throw std::out_of_range("Invalid index value.");
	return entries[index];
}

const double& NumericVector::At(const size_t index) const
{
	if (index >= entries.size()) throw std::out_of_range("Invalid index value.");
	return entries[index];
}

double& NumericVector::operator()(const size_t index)
{
	return this->entries[index];
}

const double& NumericVector::operator()(const size_t index) const
{
	return this->entries[index];
}