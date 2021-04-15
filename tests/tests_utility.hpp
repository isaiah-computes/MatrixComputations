#ifndef MATRIXCOMPS_TESTS_UTILITY_H
#define MATRIXCOMPS_TESTS_UTILITY_H

#include "Matrix.hpp"
#include "Eigen3/Dense"

Eigen::MatrixXd Copy_to_Eigen(const Matrix& m);
bool Near_Match(const Matrix& m1, const Matrix& m2, double tol = 100 * std::numeric_limits<double>::epsilon());
bool Near_Match(const Matrix& m, const Eigen::MatrixXd& eig_m, double tol = 100 * std::numeric_limits<double>::epsilon());

#endif
