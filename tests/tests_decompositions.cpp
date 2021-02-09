#include "Catch.hpp"
#include "../src/Matrix.hpp"
#include "../src/MatrixDecompositions.hpp"

TEST_CASE("LU Decomoposiiton requires square input") {

	Matrix A = Matrix::Random(7, 9);
	Matrix L = Matrix(7, 9); 
	Matrix U = Matrix(7, 9);

	REQUIRE_THROWS_AS(MatrixDecompositions::LU(A, L, U), std::invalid_argument);
}

TEST_CASE("LU Decomoposiiton is correct") {

	int size = 5;
	Matrix A = Matrix::Random(size, size);
	Matrix L(size, size); Matrix U(size, size);

	MatrixDecompositions::LU(A, L, U);

	for (int i = 0; i < size - 1; i++) {
		for (int j = i + 1; j < size; j++) {
			REQUIRE(L(i, j) == 0);
		}
	}

	for (int i = 1; i < size; i++) {
		for (int j = 0; j < i; j++) {
			REQUIRE(U(i, j) == 0);
		}
	}

	bool equivalance = A == (L * U);
	REQUIRE(equivalance == true);
}