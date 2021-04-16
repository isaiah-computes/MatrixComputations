#include "catch.hpp"
#include "Matrix.hpp"
#include "test_utility.hpp"

TEST_CASE("Equality operator tests") {

    Matrix m1 = Matrix::Random(4, 6);
    bool m_test = m1 == m1;
    REQUIRE(m_test == true);

    Matrix m2 = Matrix::Random(4, 6);
    m_test = m1 == m2;
    REQUIRE(m_test == false);

    Matrix m3 = Matrix::Random(5, 5);
    REQUIRE_THROWS_AS(m1 == m3, std::invalid_argument);
}

TEST_CASE("Addition and subtraction require same dimensions") {

    Matrix m1 = Matrix::Random(5, 7);
    Matrix m2 = Matrix::Random(7, 5);

    REQUIRE_THROWS_AS(m1 + m2, std::invalid_argument);
    REQUIRE_THROWS_AS(m1 - m2, std::invalid_argument);
}

TEST_CASE("Addition and subtraction function properly") {

    int rows = 5;
    int columns = 6;

    Matrix m = Matrix::Random(rows, columns);

    Matrix m_sum = m + m;
    Matrix m_diff = m - m;

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            REQUIRE(m_sum(i, j) == 2 * m(i, j));
            REQUIRE(m_diff(i, j) == 0);
        }
    }
}

TEST_CASE("Illegal multiplication dimensions throw exception") {

    Matrix m1 = Matrix::Random(4, 5);

    REQUIRE_THROWS_AS(m1 * m1, std::invalid_argument);
}

TEST_CASE("Matrix multiplication products have correct dimensions") {

    int dim_one = 2 + rand() % 15;
    int dim_two = 2 + rand() % 20;
    int dim_three = 2 + rand() % 15;

    Matrix m1 = Matrix::Random(dim_one, dim_one);
    Matrix m_prod = m1 * m1;

    REQUIRE(m_prod.Rows() == dim_one);
    REQUIRE(m_prod.Columns() == dim_one);

    m1 = Matrix::Random(dim_one, dim_two);
    Matrix m2 = Matrix::Random(dim_two, dim_three);
    m_prod = m1 * m2;

    REQUIRE(m_prod.Rows() == dim_one);
    REQUIRE(m_prod.Columns() == dim_three);
}

TEST_CASE("Left multiplication by identity has no impact") {

    int rows = 4;
    int cols = 5;
    Matrix mat = Matrix::Random(rows, cols);
    Matrix ident = Matrix::Identity(rows);
    Matrix prod = ident * mat;

    REQUIRE(Near_Match(mat, prod) == true);
}

TEST_CASE("Right multiplication by identity has no impact") {

    int rows = 4;
    int cols = 5;
    Matrix mat = Matrix::Random(rows, cols);
    Matrix ident = Matrix::Identity(cols);
    Matrix prod = mat * ident;

    REQUIRE(Near_Match(mat, prod) == true);
}

TEST_CASE("Matrix multiplication produces correct resutls")
{
    size_t r1 = 18;
    size_t c1 = 3;
    size_t c2 = 7;

    Matrix m1 = Matrix::Random(r1, c1);
    Matrix m2 = Matrix::Random(c1, c2);
    Matrix m3 = m1 * m2;

    auto eig_m1 = Copy_to_Eigen(m1);
    auto eig_m2 = Copy_to_Eigen(m2);
    auto eig_m3 = eig_m1 * eig_m2;

    REQUIRE(Near_Match(m3, eig_m3) == true);
}

TEST_CASE("Single index returns correct values") {

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