#include "catch.hpp"
#include "Matrix.hpp"
#include "test_utility.hpp"

TEST_CASE("Equality operator produces correct results", "[binary-ops]") {

    Matrix m1 = Matrix::Random(4, 6);
    bool m_test = m1 == m1;
    REQUIRE(m_test == true);

    Matrix m2 = Matrix::Random(4, 6);
    m_test = m1 == m2;
    REQUIRE(m_test == false);

    Matrix m3 = Matrix::Random(5, 5);
    REQUIRE_THROWS_AS(m1 == m3, std::invalid_argument);
}

TEST_CASE("Addition operator produces correct results", "[binary-ops]") {

    Matrix m1 = Matrix::Random(5, 7);
    Matrix m2 = Matrix::Random(7, 5);
    Matrix m3 = m1 + m1;

    REQUIRE_THROWS_AS(m1 + m2, std::invalid_argument);

    bool result = true;

    for (size_t i = 0; i < m1.Rows(); i++) {
        for (size_t j = 0; j < m1.Columns(); j++) {
            if (m3(i, j) != 2 * m1(i, j)) result = false;
            if (!result) break;
        }
        if (!result) break;
    }

    REQUIRE(result == true);
}

TEST_CASE("Subtraction operator produces correct results", "[binary-ops]") {

    Matrix m1 = Matrix::Random(5, 7);
    Matrix m2 = Matrix::Random(7, 5);
    Matrix m3 = m1 - m1;

    REQUIRE_THROWS_AS(m1 - m2, std::invalid_argument);

    bool result = true;

    for (size_t i = 0; i < m1.Rows(); i++) {
        for (size_t j = 0; j < m1.Columns(); j++) {
            if (m3(i, j) != 0.0) result = false;
            if (!result) break;
        }
        if (!result) break;
    }

    REQUIRE(result == true);
}


TEST_CASE("Multiplication operator produces correct results", "[binary-ops][eig]") {

    size_t r1 = 15;
    size_t c1 = 22;
    size_t c2 = 18;

    Matrix m1 = Matrix::Random(r1, c1);
    Matrix m2 = Matrix::Random(c1, c2);

    SECTION("Multiplication yields appropriate dimensions") {

        Matrix m_sqr = Matrix::Random(r1, r1);
        auto sqr_prod = m_sqr * m_sqr;
        REQUIRE(sqr_prod.Rows() == m_sqr.Rows());
        REQUIRE(sqr_prod.Columns() == m_sqr.Columns());

        REQUIRE_THROWS_AS(m1 * m1, std::invalid_argument);

        auto m_prod = m1 * m2;

        REQUIRE(m_prod.Rows() == r1);
        REQUIRE(m_prod.Columns() == c2);
    }

    SECTION("Multiplication by Identity leaves matrix unchanged") {

        Matrix i1 = Matrix::Identity(r1);
        auto i_prod_left = i1 * m1;
        bool result = i_prod_left == m1;
        REQUIRE(result == true);

        Matrix i2 = Matrix::Identity(c1);
        auto i_prod_right = m1 * i2;
        result = i_prod_right == m1;
        REQUIRE(result == true);
    }

    SECTION("Multiplication reulsts are numerically valid") {

        Matrix m3 = m1 * m2;

        auto eig_m1 = Copy_to_Eigen(m1);
        auto eig_m2 = Copy_to_Eigen(m2);
        auto eig_m3 = eig_m1 * eig_m2;

        REQUIRE(Near_Match(m3, eig_m3) == true);
    }
}