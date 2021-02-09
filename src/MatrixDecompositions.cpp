#include "Matrix.hpp"
#include "MatrixDecompositions.hpp"


void MatrixDecompositions::LU(const Matrix A, Matrix& L, Matrix& U)
{
	if (A.Rows() != A.Columns()) throw std::invalid_argument("LU Decomposition requires square input");

	// ALGORITHM 3.2.1 FROM MATRIX COMPUTATIONS, 4TH ED

	//U = Matrix(A);


}

