#include "catch.hpp"
#include "test_utility.hpp"

Eigen::MatrixXd Copy_to_Eigen(const Matrix& m)
{
    Eigen::MatrixXd em(m.Rows(), m.Columns());

    for (size_t i = 0; i < m.Rows(); i++) {
        for (size_t j = 0; j < m.Columns(); j++) {
            em(i, j) = m(i, j);
        }
    }

    return em;
}

bool Near_Match(const Matrix& m1, const Matrix& m2, double tol)
{
    // not checking sizes of matrices being compared as this function
    // is only used in unit tests with specifcally constructed matrices

    bool result = true;

    for (size_t i = 0; i < m1.Rows(); i++) {
        for (size_t j = 0; j < m2.Columns(); j++) {
            auto comparer = Catch::Matchers::WithinRel(m2(i, j), tol);
            if (!comparer.match(m1(i, j))) {
                result = false;
                break;
            }
        }
        if (!result) break;
    }

    return result;
}


bool Near_Match(const Matrix& m, const Eigen::MatrixXd& eig_m, double tol) 
{
    // not checking sizes of matrices being compared as this function
    // is only used in unit tests with specifcally constructed matrices

    bool result = true;
    
    for (size_t i = 0; i < m.Rows(); i++) {
        for (size_t j = 0; j < m.Columns(); j++) {
            auto comparer = Catch::Matchers::WithinRel(eig_m(i, j), tol);
            if (!comparer.match(m(i, j))) {
                result = false;
                break;
            }
        }
        if (!result) break;
    }

    return result;
}

bool Is_Symmetric(const Matrix& m)
{
    if (!m.Square()) throw std::invalid_argument("Cannot test non-square matrix for symmetry.");

    bool result = true;
    
    for (size_t i = 0; i < m.Rows(); i++) {
        for (size_t j = i + 1; j < m.Columns(); j++) {
            REQUIRE(m(i, j) == m(j, i));
        }
    }

    return result;
}

bool Is_Upper_Triangular(const Matrix& m)
{
    if (!m.Square()) throw std::invalid_argument("Cannot test non-square matrix for upper triangularity.");

    bool result = true;

    for (size_t i = 0; i < m.Rows(); i++) {
        for (size_t j = 0; j < i; j++) {
            if (m(i, j) != 0.0) result = false;
            if (!result) break;
        }
        if (!result) break;
    }

    return result;
}

bool Is_Strictly_Upper_Triangular(const Matrix& m)
{
    if (!m.Square()) throw std::invalid_argument("Cannot test non-square matrix for upper triangularity.");

    bool result = true;

    for (size_t i = 0; i < m.Rows(); i++) {
        for (size_t j = 0; j <= i; j++) {
            if (m(i, j) != 0.0) result = false;
            if (!result) break;
        }
        if (!result) break;
    }

    return result;
}

bool Is_Lower_Triangular(const Matrix& m)
{
    if (!m.Square()) throw std::invalid_argument("Cannot test non-square matrix for lower triangularity.");

    bool result = true;

    for (size_t i = 0; i < m.Rows(); i++) {
        for (size_t j = i + 1; j < m.Columns(); j++) {
            if (m(i, j) != 0.0) result = false;
            if (!result) break;
        }
        if (!result) break;
    }

    return result;
}

bool Is_Strictly_Lower_Triangular(const Matrix& m)
{
    if (!m.Square()) throw std::invalid_argument("Cannot test non-square matrix for lower triangularity.");

    bool result = true;

    for (size_t i = 0; i < m.Rows(); i++) {
        for (size_t j = i; j < m.Columns(); j++) {
            if (m(i, j) != 0.0) result = false;
            if (!result) break;
        }
        if (!result) break;
    }

    return result;
}