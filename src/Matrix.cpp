
#include <iostream>
#include <random>
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

Matrix::~Matrix() {}

Matrix Matrix::Identity(const unsigned int size)
{
	Matrix m(size, size);
	for (unsigned int i = 0; i < size; i++) m(i, i) = 1.0;
	return m;
}

Matrix Matrix::Random(const unsigned int rows, const unsigned int columns)
{
	std::default_random_engine re;
	std::uniform_real_distribution<double> rand_vals(0.0, 1.0);

	Matrix m(rows, columns);

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			m(i, j) = rand_vals(re);
		}
	}

	return m;
}

double& Matrix::operator()(const unsigned int row, const unsigned int col)
{
	if (row >= rows || col >= cols) throw std::out_of_range("Invalid index value.");
	return this->entries[row][col];
}

const double& Matrix::operator()(const unsigned int row, const unsigned int col) const
{
	if (row >= rows || col >= cols) throw std::out_of_range("Invalid index value.");
	return this->entries[row][col];
}


Matrix Matrix::operator+(const Matrix& other)
{
	if (rows != other.rows || cols != other.cols) throw std::invalid_argument("Cannot add matrices of differing dimensions.");

	Matrix output(rows, cols);

	for (unsigned int i = 0; i < rows; i++)
	{
		for (unsigned int j = 0; j < cols; j++)
		{
			output(i, j) = this->entries[i][j] + other(i, j);
		}
	}

	return output;
}

Matrix Matrix::operator-(const Matrix& other)
{
	if (rows != other.rows || cols != other.cols) throw std::invalid_argument("Cannot subtract matrices of differing dimensions.");

	Matrix output(rows, cols);

	for (unsigned int i = 0; i < rows; i++)
	{
		for (unsigned int j = 0; j < cols; j++)
		{
			output(i, j) = this->entries[i][j] - other(i, j);
		}
	}

	return output;
}

Matrix Matrix::operator*(const Matrix& other)
{
	if (rows != other.cols || cols != other.rows) throw std::invalid_argument("Cannot multiply matrices (invalid dimensions).");

	Matrix output(rows, other.cols);

	for (unsigned int i = 0; i < rows; i++) 
	{
		for (unsigned int j = 0; j < other.cols; j++) 
		{
			for (unsigned int k = 0; k < cols; k++) 
			{
				output(i, j) += this->entries[i][k] * other(k, j);
			}
		}
	}

	return output;
}

std::ostream& operator<<(std::ostream& output, const Matrix& m)
{
	for (int i = 0; i < m.rows; i++)
	{
		for (int j = 0; j < m.cols; j++)
		{
			std::cout << " " << m.entries[i][j] << " ";
		}
		std::cout << "\n";
	}

	return output;
}