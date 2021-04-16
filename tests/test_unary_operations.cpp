#include "catch.hpp"
#include "Matrix.hpp"

TEST_CASE("Writing and reading matrices maintain dimensions") {

    Matrix m = Matrix::Random(7, 12);
    m.ToFile("test_mat.txt");
    Matrix m2 = Matrix::FromFile("test_mat.txt");

    REQUIRE(m.Rows() == m2.Rows());
    REQUIRE(m.Columns() == m2.Columns());
}

TEST_CASE("Writing and reading matrices maintain values") {

    Matrix m = Matrix::Random(7, 12);
    m.ToFile("test_mat.txt");
    Matrix m2 = Matrix::FromFile("test_mat.txt");
    bool matching_matrices = m == m2;

    REQUIRE(matching_matrices == true);
}

TEST_CASE("Matrix transpose produces correct output") {

    int num_rows = 11;
    int num_cols = 5;
    Matrix m1 = Matrix::Random(num_rows, num_cols);
    Matrix m2 = m1.Transpose();

    for (int i = 0; i < num_rows; i++)
    {
        for (int j = 0; j < num_cols; j++) {
            REQUIRE(m2(j, i) == m1(i, j));
        }
    }
}