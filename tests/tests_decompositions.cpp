#include "Catch.hpp"
#include "../src/Matrix.hpp"
#include "../src/MatrixDecompositions.hpp"

TEST_CASE("LU Decomoposiiton requires square input") {

	Matrix A = Matrix::Random(7, 9);
	Matrix L = Matrix(7, 9); 
	Matrix U = Matrix(7, 9);

	REQUIRE_THROWS_AS(MatrixDecompositions::LU(A, L, U), std::invalid_argument);
}