#include <iostream>
#include "catch.hpp"
#include "Matrix.hpp"
#include "MatrixDecompositions.hpp"
#include "test_utility.hpp"

TEST_CASE("LU Decomoposiiton requires square input") {

	Matrix A = Matrix::Random(7, 9);
	Matrix L = Matrix(7, 9); 
	Matrix U = Matrix(7, 9);

	REQUIRE_THROWS_AS(MatrixDecompositions::LU(A, L, U), std::invalid_argument);
}

TEST_CASE("LU Decomoposiiton is correct") {

	size_t size = 5;
	Matrix A = Matrix::Random(size, size);
	Matrix L(size, size); Matrix U(size, size);

	MatrixDecompositions::LU(A, L, U);

	REQUIRE(Is_Upper_Triangular(U) == true);
	REQUIRE(Is_Lower_Triangular(L) == true);

	Matrix B = L * U; 
	REQUIRE(Near_Match(A, B) == true);
}