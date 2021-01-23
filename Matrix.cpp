
#include "Matrix.hpp"

Matrix::Matrix(unsigned int NumberRows, unsigned int NumberCols)
{
	rows = NumberRows;
	cols = NumberCols;

	entries.resize(rows);
	for (unsigned int i = 0; i < rows; i++) entries[i].resize(cols);
}

Matrix::Matrix(const Matrix& input) 
{
	rows = input.rows;
	cols = input.cols;
	entries = input.entries;
}

double& Matrix::operator()(const unsigned int& row, const unsigned int& col)
{
	return this->entries[row][col];
}

Matrix::~Matrix() {}

Matrix Matrix::Identity(const unsigned int size)
{
	Matrix m = Matrix(size, size);
	for (unsigned int i = 0; i < size; i++) m(i, i) = 1.0;
	return m;
}