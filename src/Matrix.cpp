#include <algorithm>
#include <fstream>
#include <iostream>
#include <iomanip> 
#include <random>
#include <sstream>
#include "Matrix.hpp"

Matrix::Matrix(unsigned int NumberRows, unsigned int NumberCols)
{
	rows = NumberRows;
	cols = NumberCols;

	entries.resize(rows * cols);
}

Matrix::Matrix(const Matrix& input) 
{
	rows = input.rows;
	cols = input.cols;
	entries = input.entries;
}

Matrix::~Matrix() {}

int Matrix::Index(unsigned int row, unsigned int col) const
{
	return row * cols + col;
}

Matrix Matrix::Identity(const unsigned int size)
{
	Matrix m(size, size);
	for (unsigned int i = 0; i < size; i++) m(i, i) = 1.0;
	return m;
}

Matrix Matrix::Random(const unsigned int rows, const unsigned int columns)
{
	std::random_device rd;
	std::default_random_engine re(rd());
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

Matrix Matrix::RandomSymmetric(const unsigned int size)
{
	std::random_device rd;
	std::default_random_engine re(rd());
	std::uniform_real_distribution<double> rand_vals(0.0, 1.0);

	Matrix m(size, size);

	for (int i = 0; i < size; i++)
	{
		m(i, i) = rand_vals(re);
		for (int j = i + 1; j < size; j++)
		{
			m(i, j) = rand_vals(re);
			m(j, i) = m(i, j);
		}
	}

	return m;
}
double& Matrix::operator()(const unsigned int row, const unsigned int col)
{
	if (row >= rows || col >= cols) throw std::out_of_range("Invalid index value.");
	return this->entries[Index(row, col)];
}

const double& Matrix::operator()(const unsigned int row, const unsigned int col) const
{
	if (row >= rows || col >= cols) throw std::out_of_range("Invalid index value.");
	return this->entries[Index(row, col)];
}

bool Matrix::operator==(const Matrix& other)
{
	if (rows != other.rows || cols != other.cols) throw std::invalid_argument("Matrices not same dimensions");
	bool result = true;

	for (int i = 0; i < rows; i++){
		for (int j = 0; j < cols; j++) {
			if (this->entries[Index(i, j)] != other(i, j))
			{
				result = false;
				break;
			}
		}
		if (!result) break;
	}

	return result;
}

Matrix Matrix::operator+(const Matrix& other)
{
	if (rows != other.rows || cols != other.cols) throw std::invalid_argument("Cannot add matrices of differing dimensions.");

	Matrix output(rows, cols);

	for (unsigned int i = 0; i < rows; i++)
	{
		for (unsigned int j = 0; j < cols; j++)
		{
			output(i, j) = this->entries[Index(i, j)] + other(i, j);
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
			output(i, j) = this->entries[Index(i, j)] - other(i, j);
		}
	}

	return output;
}

Matrix Matrix::operator*(const Matrix& other)
{
	if (cols != other.rows) throw std::invalid_argument("Cannot multiply matrices (invalid dimensions).");

	Matrix output(rows, other.cols);

	for (unsigned int i = 0; i < rows; i++) 
	{
		for (unsigned int j = 0; j < other.cols; j++) 
		{
			for (unsigned int k = 0; k < cols; k++) 
			{
				output(i, j) += this->entries[Index(i, k)] * other(k, j);
			}
		}
	}

	return output;
}

Matrix Matrix::Transpose()
{
	Matrix m(cols, rows);

	for (unsigned int i = 0; i < rows; i++)
	{
		for (unsigned int j = 0; j < cols; j++) {
			m(j, i) = entries[Index(i, j)];
		}
	}

	return m;
}

void Matrix::ToFile(const std::string file_name, const char delimiter)
{
	std::ofstream out_file;
	out_file.open(file_name);
	
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			out_file << std::setprecision(17) << this->entries[Index(i, j)];
			if (j < cols - 1) out_file << ",";
		}
		out_file << "\n";
	}

	out_file.close();
}

Matrix Matrix::FromFile(const std::string file_name, const char delimiter)
{
	std::ifstream in(file_name);

	if (!in) throw std::ios_base::failure("Error opening file " + file_name);

	std::vector<std::string> lines;
	std::string line;
	while (std::getline(in, line))
	{
		lines.push_back(line);
	}

	unsigned int num_rows = lines.size();
	unsigned int num_cols = std::count(lines[0].begin(), lines[0].end(), delimiter);

	for (unsigned int i = 1; i < num_rows; i++)
	{
		if (std::count(lines[0].begin(), lines[0].end(), delimiter) != num_cols)
			throw std::invalid_argument("Number of columns in file is not consistent.");
	}

	num_cols++;
	Matrix m(num_rows, num_cols);

	for (unsigned int i = 0; i < num_rows; i++)
	{
		unsigned int curr_column = 0;
		std::string curr_entry;
		
		for (std::string::iterator it = lines[i].begin(); it != lines[i].end(); ++it) {
			if (*it != delimiter) curr_entry.push_back(*it);
			else {
				m(i, curr_column) = std::stod(curr_entry);
				curr_column++;
				curr_entry.clear();
			}

			if (it == lines[i].end()-1) m(i, curr_column) = std::stod(curr_entry);
		}
	}

	return m;
}

std::ostream& operator<<(std::ostream& output, const Matrix& m)
{
	for (int i = 0; i < m.rows; i++)
	{
		for (int j = 0; j < m.cols; j++)
		{
			std::cout << " " << m.entries[m.Index(i, j)] << " ";
		}
		std::cout << "\n";
	}

	return output;
}