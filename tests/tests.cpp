#include "Catch.hpp"
#include "../src/Matrix.hpp"


// interesting : catch2 supports vector comparisons
/*for (int i = 0; i < num_rows; i++){
    REQUIRE_THAT(m[i], Catch::Matchers::Equals(t[i]));
}*/

TEST_CASE("Constructor generates correct dimensions") {

    int num_rows = 17;
    int num_cols = 22;
    Matrix m(num_rows, num_cols);

    REQUIRE(m.Rows() == num_rows);
    REQUIRE(m.Columns() == num_cols);
}

TEST_CASE("Invalid index values throw exception") {

    Matrix m(4, 5);

    REQUIRE_THROWS_AS(m(4, 0), std::out_of_range);
    REQUIRE_THROWS_AS(m(0, 5), std::out_of_range);
    REQUIRE_THROWS_AS(m(-1, 0), std::out_of_range);
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