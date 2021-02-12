#include "catch.hpp"
#include "../src/Matrix.hpp"
#include "../src/RealVector.hpp"

TEST_CASE("Vector ctor generates appropriate length") {
	int size = 9;
	RealVector v(size);

	REQUIRE(v.Length() == size);
}