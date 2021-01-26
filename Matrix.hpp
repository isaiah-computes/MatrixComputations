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

	static Matrix Identity(const unsigned int size);

	unsigned int Rows() { return rows; }
	unsigned int Columns() { return cols; }

	double& operator()(const unsigned int row, const unsigned int col);
	const double& operator()(const unsigned int row, const unsigned int col) const;	

	Matrix operator+(const Matrix& other);
	Matrix operator-(const Matrix& other);

	void Print();
};


#endif
