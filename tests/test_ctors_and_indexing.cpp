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
    
    // using a vector of 'vectors' for ease of indexed testing
    std::vector<NumericVector> rows;
    rows.push_back(NumericVector{ 15,16,17 });
    rows.push_back(NumericVector{ 22,23,24 });
    rows.push_back(NumericVector{ 19,15,11 });
    rows.push_back(NumericVector{ 37,30,23 });    
    Matrix m{ rows[0],rows[1],rows[2],rows[3] };

    REQUIRE(m.Rows() == 4);
    REQUIRE(m.Columns() == 3);

    bool result = true;

    for (size_t i = 0; i < rows.size(); i++) {
        for (size_t j = 0; j < 3; j++) {
            if (m(i, j) != rows[i](j)) result = false;
            if (!result) break;
        }
        if (!result) break;
    }

    REQUIRE(result == true);

    Matrix m2{
        NumericVector{ 15,16,17 },NumericVector{ 22,23,24 },
        NumericVector{ 19,15,11 },NumericVector{ 37,30,23 }
    };

    result = m == m2;
    REQUIRE(result == true);
}

TEST_CASE("Indexing by row and column returns correct value", "[indexing]") {

    size_t num_rows = 4;
    size_t num_cols = 5;

    Matrix m(num_rows, num_cols);
    size_t curr_entry = 0;

    for (size_t i = 0; i < num_rows; i++) {
        for (size_t j = 0; j < num_cols; j++) {
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
        bool result = true;

        for (size_t i = 0; i < num_rows; i++) {
            for (size_t j = 0; j < num_cols; j++) {
                if (m(i, j) != curr_entry) result = false;
                if (m.At(i, j) != curr_entry) result = false;
                curr_entry++;

                if (!result) break;
            }
            if (!result) break;
        }

        REQUIRE(result == true);
    }
}

TEST_CASE("Single linear index returns correct values", "[indexing]") {

    size_t num_rows = 35;
    size_t num_cols = 17;
    Matrix m = Matrix::Random(num_rows, num_cols);

    SECTION("invalid indices throw an exception") {
        REQUIRE_THROWS_AS(m.At(-1), std::out_of_range);
        REQUIRE_THROWS_AS(m.At(num_rows * num_cols), std::out_of_range);
    }

    SECTION("entry retrieval returns correct values") {

        size_t curr_entry = 0;
        bool result = true;

        for (size_t i = 0; i < num_rows; i++) {
            for (size_t j = 0; j < num_cols; j++) {
                if (m(i, j) != m(curr_entry)) result = false;
                curr_entry++;

                if (!result) break;
            }
            if (!result) break;
        }

        REQUIRE(result == true);
    }
}

TEST_CASE("Identity generator produces diagonal matrix of ones", "[ctors][named-ctor]") {

    size_t size = 18;
    Matrix m = Matrix::Identity(size);

    bool result = true;

    for (size_t i = 0; i<size; i++)    {
        for (size_t j = 0; j < size; j++)        {
            if (i == j && m(i, j) != 1.0) result = false;
            else if (i != j && m(i, j) != 0.0) result = false;

            if (!result) break;
        }
        if (!result) break;
    }

    REQUIRE(result == true);
}

TEST_CASE("Random Symmetric generator produces symmetric matrix", "[ctors][named-ctor]") {

    size_t size = 7;
    Matrix m = Matrix::RandomSymmetric(size);

    REQUIRE(Is_Symmetric(m) == true);
}

TEST_CASE("Random Integer generator produces correct output", "[ctors][named-ctor]") {

    size_t r = 9;
    size_t c = 15;

    int min_val = 23;
    int max_val = 307;

    Matrix m = Matrix::RandomInteger(r, c, min_val, max_val);

    bool result = true;

    for (size_t i = 0; i < r; i++) {
        for (size_t j = 0; j < c; j++) {
            if (m(i, j) < min_val || m(i, j) > max_val) result = false;
            if (m(i, j) != static_cast<int>(m(i, j))) result = false;
            if (!result) break;
        }
        if (!result) break;
    }

    REQUIRE(result == true);
}