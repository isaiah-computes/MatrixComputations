#ifndef MATRIXCOMPS_MATRIX_H
#define MATRIXCOMPS_MATRIX_H

#include <vector>
#include <ostream>
#include "NumericVector.hpp"

class Matrix
{
private:

	std::vector<double> entries;
	size_t rows;
	size_t cols;

public:

	Matrix(size_t NumberRows, size_t NumberCols);
	Matrix(std::initializer_list<NumericVector> input_rows);
	Matrix(const Matrix& input);
	size_t Index(size_t row, size_t col) const;
	virtual ~Matrix();

	static Matrix Identity(const size_t size);
	static Matrix Random(const size_t rows, const size_t columns);
	static Matrix RandomSymmetric(const size_t size);
	static Matrix RandomInteger(const size_t rows, const size_t columns, const int min_value, const int max_value);

	size_t Rows() const { return rows; }
	size_t Columns() const { return cols; }

	double& operator()(const size_t row, const size_t col);
	const double& operator()(const size_t row, const size_t col) const;	
	double& At(const size_t row, const size_t col);
	const double& At(const size_t row, const size_t col) const;

	double& operator()(const size_t index);
	const double& operator()(const size_t index) const;

	double& At(const size_t index);
	const double& At(const size_t index) const;

	Matrix operator+(const Matrix& other);
	Matrix operator-(const Matrix& other);
	Matrix operator*(const Matrix& other);
	bool operator==(const Matrix& other);

	Matrix Transpose();

	void ToFile(const std::string& file_name, const char delimiter = ',');
	static Matrix FromFile(const std::string& file_name, const char delimiter = ',');
	friend std::ostream& operator<<(std::ostream& output, const Matrix& m);
};

#endif