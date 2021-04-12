#include <algorithm>
#include <fstream>
#include <iostream>
#include <iomanip> 
#include <random>
#include <sstream>
#include "Matrix.hpp"

Matrix::Matrix(size_t NumberRows, size_t NumberCols)
{
	rows = NumberRows;
	cols = NumberCols;

	entries.resize(rows * cols);
}

Matrix::Matrix(std::initializer_list<NumericVector> input_rows)
{
	rows = input_rows.size();
	auto it = input_rows.begin();
	cols = it->Dimension();

	for (it = input_rows.begin(); it != input_rows.end(); ++it){
		if (it->Dimension() != cols) throw std::out_of_range("Inconsistent input vector dimensions.");
	}

	entries.resize(rows * cols);
	size_t curr_entry = 0;

	for (it = input_rows.begin(); it != input_rows.end(); ++it) {
		for (size_t elem = 0; elem < cols; elem++) {
			entries[curr_entry] = it->At(elem);
			curr_entry++;
		}
	}
}

Matrix::Matrix(const Matrix& input) 
{
	rows = input.rows;
	cols = input.cols;
	entries = input.entries;
}

Matrix::~Matrix() {}

size_t Matrix::Index(size_t row, size_t col) const
{
	return row * cols + col;
}

Matrix Matrix::Identity(const size_t size)
{
	Matrix m(size, size);
	for (size_t i = 0; i < size; i++) m(i, i) = 1.0;
	return m;
}

Matrix Matrix::Random(const size_t rows, const size_t columns)
{
	std::random_device rd;
	std::default_random_engine re(rd());
	std::uniform_real_distribution<double> rand_vals(0.0, 1.0);

	Matrix m(rows, columns);

	for (size_t i = 0; i < rows; i++)
	{
		for (size_t j = 0; j < columns; j++)
		{
			m(i, j) = rand_vals(re);
		}
	}

	return m;
}

Matrix Matrix::RandomSymmetric(const size_t size)
{
	std::random_device rd;
	std::default_random_engine re(rd());
	std::uniform_real_distribution<double> rand_vals(0.0, 1.0);

	Matrix m(size, size);

	for (size_t i = 0; i < size; i++)
	{
		m(i, i) = rand_vals(re);
		for (size_t j = i + 1; j < size; j++)
		{
			m(i, j) = rand_vals(re);
			m(j, i) = m(i, j);
		}
	}

	return m;
}

Matrix Matrix::RandomInteger(const size_t rows, const size_t columns, const int min_value, const int max_value)
{
	std::random_device rd;
	std::default_random_engine re(rd());
	std::uniform_int_distribution<int> rand_vals(min_value, max_value);

	Matrix m(rows, columns);

	for (size_t i = 0; i < rows; i++)
	{
		for (size_t j = 0; j < columns; j++)
		{
			m(i, j) = rand_vals(re);
		}
	}

	return m;
}

double& Matrix::operator()(const size_t row, const size_t col)
{
	return this->entries[Index(row, col)];
}

const double& Matrix::operator()(const size_t row, const size_t col) const
{
	return this->entries[Index(row, col)];
}

double& Matrix::At(const size_t row, const size_t col)
{
	if (row >= rows || col >= cols) throw std::out_of_range("Invalid index value.");
	return entries[Index(row, col)];
}

const double& Matrix::At(const size_t row, const size_t col) const
{
	if (row >= rows || col >= cols) throw std::out_of_range("Invalid index value.");
	return entries[Index(row, col)];
}

double& Matrix::operator()(const size_t index)
{
	return this->entries[index];
}

const double& Matrix::operator()(const size_t index) const
{
	return this->entries[index];
}

bool Matrix::operator==(const Matrix& other)
{
	if (rows != other.rows || cols != other.cols) throw std::invalid_argument("Matrices not same dimensions");
	bool result = true;

	for (size_t i = 0; i < rows; i++){
		for (size_t j = 0; j < cols; j++) {
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

	for (size_t i = 0; i < rows; i++)
	{
		for (size_t j = 0; j < cols; j++)
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

	for (size_t i = 0; i < rows; i++)
	{
		for (size_t j = 0; j < cols; j++)
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

	for (size_t i = 0; i < rows; i++) 
	{
		for (size_t j = 0; j < other.cols; j++) 
		{
			for (size_t k = 0; k < cols; k++) 
			{
				//output(i, j) += this->entries[Index(i, k)] * other(k, j);
				output.At(i, j) += this->entries[Index(i, k)] * other.At(k, j);
			}
		}
	}

	return output;
}

Matrix Matrix::Transpose()
{
	Matrix m(cols, rows);

	for (size_t i = 0; i < rows; i++)
	{
		for (size_t j = 0; j < cols; j++) {
			m(j, i) = entries[Index(i, j)];
		}
	}

	return m;
}

void Matrix::ToFile(const std::string& file_name, const char delimiter)
{
	std::ofstream out_file;
	out_file.open(file_name);
	
	for (size_t i = 0; i < rows; i++)
	{
		for (size_t j = 0; j < cols; j++)
		{
			out_file << std::setprecision(17) << this->entries[Index(i, j)];
			if (j < cols - 1) out_file << ",";
		}
		out_file << "\n";
	}

	out_file.close();
}

Matrix Matrix::FromFile(const std::string& file_name, const char delimiter)
{
	std::ifstream in(file_name);

	if (!in) throw std::ios_base::failure("Error opening file " + file_name);

	std::vector<std::string> lines;
	std::string line;
	while (std::getline(in, line))
	{
		lines.push_back(line);
	}

	size_t num_rows = lines.size();
	size_t num_cols = std::count(lines[0].begin(), lines[0].end(), delimiter);

	for (size_t i = 1; i < num_rows; i++)
	{
		if (std::count(lines[0].begin(), lines[0].end(), delimiter) != num_cols)
			throw std::invalid_argument("Number of columns in file is not consistent.");
	}

	num_cols++;
	Matrix m(num_rows, num_cols);

	for (size_t i = 0; i < num_rows; i++)
	{
		size_t curr_column = 0;
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
	for (size_t i = 0; i < m.rows; i++)
	{
		for (size_t j = 0; j < m.cols; j++)
		{
			std::cout << " " << m.entries[m.Index(i, j)] << " ";
		}
		std::cout << "\n";
	}

	return output;
}