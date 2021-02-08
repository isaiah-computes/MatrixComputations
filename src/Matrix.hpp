#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <ostream>

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
	static Matrix Random(const unsigned int rows, const unsigned int columns);

	unsigned int Rows() { return rows; }
	unsigned int Columns() { return cols; }

	double& operator()(const unsigned int row, const unsigned int col);
	const double& operator()(const unsigned int row, const unsigned int col) const;	

	Matrix operator+(const Matrix& other);
	Matrix operator-(const Matrix& other);
	Matrix operator*(const Matrix& other);
	bool operator==(const Matrix& other);

	Matrix Transpose();

	void ToFile(const std::string file_name, const char delimiter = ',');
	static Matrix FromFile(const std::string file_name, const char delimiter = ',');
	friend std::ostream& operator<<(std::ostream& output, const Matrix& m);
};

#endif