#ifndef MATRIXCOMPS_EIGEN_INTEROP_H
#define MATRIXCOMPS_EIGEN_INTEROP_H

#include "Matrix.hpp"
#include "Eigen3/Dense"

Eigen::MatrixXd Copy_to_Eigen(const Matrix& m);

#endif
