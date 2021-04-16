#include "catch.hpp"
#include "Matrix.hpp"
#include "test_utility.hpp"

TEST_CASE("Standard constructor generates correct dimensions", "[ctors]") {

    int num_rows = 17;
    int num_cols = 22;
    Matrix m(num_rows, num_cols);

    REQUIRE(m.Rows() == num_rows);
    REQUIRE(m.Columns() == num_cols);
}

TEST_CASE("Initializer list constructor populates matrix correctly", "[ctors]") {

    NumericVector v1{ 15,16,17 };
    NumericVector v2{ 22,23,24 };
    NumericVector v3{ 19,15,11 };
    NumericVector v4{ 37,30,23 };
    Matrix m{ v1,v2,v3,v4 };

    REQUIRE(m.Rows() == 4);
    REQUIRE(m.Columns() == 3);

    REQUIRE(m(0, 0) == 15);
    REQUIRE(m(0, 1) == 16);
    REQUIRE(m(0, 2) == 17);

    REQUIRE(m(1, 0) == 22);
    REQUIRE(m(1, 1) == 23);
    REQUIRE(m(1, 2) == 24);

    REQUIRE(m(2, 0) == 19);
    REQUIRE(m(2, 1) == 15);
    REQUIRE(m(2, 2) == 11);

    REQUIRE(m(3, 0) == 37);
    REQUIRE(m(3, 1) == 30);
    REQUIRE(m(3, 2) == 23);
}

TEST_CASE("Indexing by row and column returns correct value", "[indexing]") {

    int num_rows = 4;
    int num_cols = 5;

    Matrix m(num_rows, num_cols);
    int curr_entry = 0;

    for (int i = 0; i < num_rows; i++) {
        for (int j = 0; j < num_cols; j++) {
            m(i, j) = curr_entry;
            curr_entry++;
        }
    }

    SECTION( "invalid indices throw an exception" ) {
        REQUIRE_THROWS_AS(m.At(num_rows, 0), std::out_of_range);
        REQUIRE_THROWS_AS(m.At(0, num_cols), std::out_of_range);
        REQUIRE_THROWS_AS(m.At(-1, 0), std::out_of_range);
        REQUIRE_THROWS_AS(m.At(0, -1), std::out_of_range);
    }

    SECTION( "entry retrieval returns correct values" ) {
        curr_entry = 0;
        for (int i = 0; i < num_rows; i++) {
            for (int j = 0; j < num_cols; j++) {
                REQUIRE(m(i, j) == curr_entry);
                REQUIRE(m.At(i, j) == curr_entry);
                curr_entry++;
            }
        }
    }
}

TEST_CASE("Single linear index returns correct values", "[indexing]") {

    int num_rows = 35;
    int num_cols = 17;
    Matrix m = Matrix::Random(35, 17);

    int curr_entry = 0;

    for (int i = 0; i < num_rows; i++) {
        for (int j = 0; j < num_cols; j++) {
            REQUIRE(m(i, j) == m(curr_entry));
            REQUIRE(m(i, j) == m[curr_entry]);
            curr_entry++;
        }
    }
}

TEST_CASE("Identity generator produces diagonal matrix of ones", "[ctors][named-ctor]") {

    int size = 5;

    Matrix m = Matrix::Identity(size);

    for (int i = 0; i<size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (i == j) REQUIRE(m(i, j) == 1.0);
            else REQUIRE(m(i, j) == 0.0);
        }
    }
}

TEST_CASE("Random Symmetric generator produces symmetric matrix", "[ctors][named-ctor]") {

    int size = 7;
    Matrix m = Matrix::RandomSymmetric(size);

    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size; j++) {
            REQUIRE(m(i, j) == m(j, i));
        }
    }
}