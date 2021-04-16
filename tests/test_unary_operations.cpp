#include <cstdio>
#include <string>
#include "catch.hpp"
#include "Matrix.hpp"

TEST_CASE("Writing and reading matrices maintain values", "[unary-ops][io]") {

    std::string fname = "test_matrix.txt";

    Matrix m = Matrix::Random(7, 12);
    m.ToFile(fname);
    Matrix m2 = Matrix::FromFile(fname);
    bool matching_matrices = m == m2;

    REQUIRE(m.Rows() == m2.Rows());
    REQUIRE(m.Columns() == m2.Columns());
    REQUIRE(matching_matrices == true);

    std::remove(fname.c_str());
}

TEST_CASE("Matrix transpose produces correct output", "[unary-ops]") {

    size_t num_rows = 11;
    size_t num_cols = 5;
    Matrix m1 = Matrix::Random(num_rows, num_cols);
    Matrix m2 = m1.Transpose();

    bool result = true;

    for (size_t i = 0; i < num_rows; i++) {
        for (size_t j = 0; j < num_cols; j++) {
            if (m2(j, i) != m1(i, j)) result = false;
            if (!result) break;
        }
        if (!result) break;
    }

    REQUIRE(result == true);
}