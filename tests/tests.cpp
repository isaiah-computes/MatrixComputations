#include "catch.hpp"
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

TEST_CASE("Indexing by row and column works correctly") {

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
        REQUIRE_THROWS_AS(m(num_rows, 0), std::out_of_range);
        REQUIRE_THROWS_AS(m(0, num_cols), std::out_of_range);
        REQUIRE_THROWS_AS(m(-1, 0), std::out_of_range);
        REQUIRE_THROWS_AS(m(0, -1), std::out_of_range);
    }

    SECTION( "entry retrieval returns correct values" ) {
        curr_entry = 0;
        for (int i = 0; i < num_rows; i++) {
            for (int j = 0; j < num_cols; j++) {
                REQUIRE(m(i, j) == curr_entry);
                curr_entry++;
            }
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