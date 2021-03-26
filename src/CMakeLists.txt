
cmake_minimum_required (VERSION 3.8)

project ("matrix-comps-unit-tests")

add_executable (matcomps main.cpp Matrix.hpp Matrix.cpp MatrixDecompositions.hpp MatrixDecompositions.cpp)