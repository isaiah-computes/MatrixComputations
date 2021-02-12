#include "catch.hpp"
#include "../src/Matrix.hpp"
#include "../src/RealVector.hpp"

TEST_CASE("Vector ctor generates appropriate length") {
	int size = 9;
	RealVector v(size);

	REQUIRE(v.Length() == size);
}

TEST_CASE("Basis vector ctor functions") {
	int dim = 17;
	int basis = 5;

	RealVector v = RealVector::StandardBasis(dim, basis);

	for (int i = 0; i < dim; i++) {
		if (i != basis) REQUIRE(v[i] == 0);
		else REQUIRE(v[i] == 1.0);
	}
}