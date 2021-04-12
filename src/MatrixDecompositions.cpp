#include "Matrix.hpp"
#include "MatrixDecompositions.hpp"

void MatrixDecompositions::LU(const Matrix& A, Matrix& L, Matrix& U)
{
    size_t n = A.Rows();
	if (n != A.Columns()) throw std::invalid_argument("LU Decomposition requires square input");

	// ALGORITHM 3.2.1 FROM MATRIX COMPUTATIONS, 4TH ED
	
    L = Matrix::Identity(n);
	U = Matrix(A);

    for (size_t k = 0; k < n - 1; k++)
    {
        for (size_t i = k + 1; i < n; i++) U(i, k) /= U(k, k);

        for (size_t i = k + 1; i < n; i++)
        {
            for (size_t j = k + 1; j < n; j++)
            {
                U(i, j) -= U(i, k) * U(k, j);
            }
        }
    }

    for (int i = 1; i < n; i++)
    {
        for (int j = 0; j < i; j++)
        {
            L(i, j) = U(i, j);
            U(i, j) = 0;
        }
    }
}

