#include "catch.hpp"
#include "tests_utility.hpp"

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

bool Near_Match(const Matrix& m, const Eigen::MatrixXd& eig_m, double tol = 100 * std::numeric_limits<double>::epsilon()) 
{
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