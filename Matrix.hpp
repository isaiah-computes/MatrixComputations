#ifndef MATRIX_H
#define MATRIX_H

#include <vector>

class Matrix
{
private:

	std::vector<std::vector<double>> entries;
	unsigned int rows;
	unsigned int cols;

public:

	Matrix(unsigned int NumberRows, unsigned int NumberCols);
	Matrix(const Matrix& input);
	virtual ~Matrix();

	unsigned int Rows() { return rows; }
	unsigned int Columns() { return cols; }

	void Print();

	double& operator()(const unsigned int row, const unsigned int col);

	Matrix operator+(const Matrix& other);
	Matrix operator-(const Matrix& other);

	const double& operator()(const unsigned int row, const unsigned int col) const;

	static Matrix Identity(const unsigned int size);
};


#endif
