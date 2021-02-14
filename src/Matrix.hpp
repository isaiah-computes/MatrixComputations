#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <ostream>

class Matrix
{
private:

	std::vector<double> entries;
	unsigned int rows;
	unsigned int cols;

public:

	Matrix(unsigned int NumberRows, unsigned int NumberCols);
	Matrix(const Matrix& input);
	int Index(unsigned int row, unsigned int col) const;
	virtual ~Matrix();

	static Matrix Identity(const unsigned int size);
	static Matrix Random(const unsigned int rows, const unsigned int columns);
	static Matrix RandomInteger(const unsigned int rows, const unsigned int columns, const int min_value, const int max_value);

	unsigned int Rows() const { return rows; }
	unsigned int Columns() const { return cols; }

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