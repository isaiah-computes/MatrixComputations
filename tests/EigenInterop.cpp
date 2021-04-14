#include "EigenInterop.hpp"

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