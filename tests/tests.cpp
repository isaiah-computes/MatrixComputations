#include "Catch.hpp"
#include "../src/Matrix.hpp"


// interesting : catch2 supports vector comparisons
/*for (int i = 0; i < num_rows; i++){
    REQUIRE_THAT(m[i], Catch::Matchers::Equals(t[i]));
}*/

TEST_CASE("Invalid index values throw exception") {

    Matrix m(4, 5);

    REQUIRE_THROWS_AS(m(4, 0), std::out_of_range);
    REQUIRE_THROWS_AS(m(0, 5), std::out_of_range);
}

TEST_CASE("Equality operator functions") {

    Matrix m = Matrix::Random(4, 6);
    bool m_test = m == m;

    REQUIRE(m_test == true);

    Matrix m2 = Matrix::Random(5, 5);
    REQUIRE_THROWS_AS(m == m2, std::invalid_argument);
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

TEST_CASE( "Identity generates diagonal matrix of ones") {

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

TEST_CASE("Illegal multiplication dimensions throw exception"){

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

TEST_CASE("Left ultiplication by identity has no impact") {

    int rows = 4;
    int cols = 5;
    Matrix mat = Matrix::Random(rows, cols);
    Matrix ident = Matrix::Identity(rows);
    Matrix prod = ident * mat;

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            REQUIRE(prod(i, j) == mat(i, j));
        }
    }
}

TEST_CASE("Right ultiplication by identity has no impact") {

    int rows = 4;
    int cols = 5;
    Matrix mat = Matrix::Random(rows, cols);
    Matrix ident = Matrix::Identity(cols);
    Matrix prod = mat * ident;

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            REQUIRE(prod(i, j) == mat(i, j));
        }
    }
}

TEST_CASE("Matrix multiplication products are valid")
{
    // using randomly generated matrices and their product
    // from NumPy :
    Matrix m1 = Matrix::FromFile("matmul_m1.txt", ' ');
    Matrix m2 = Matrix::FromFile("matmul_m2.txt", ' ');
    Matrix m3 = Matrix::FromFile("matmul_m3.txt", ' ');
    Matrix m4 = m1 * m2;

    for (int i = 0; i < m4.Rows(); i++)
    {
        for (int j = 0; j < m4.Columns(); j++) {
            REQUIRE_THAT(m3(i, j), Catch::Matchers::WithinRel(m4(i, j)));
        }
    }
}

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