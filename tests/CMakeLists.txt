
cmake_minimum_required (VERSION 3.8)

project ("matrix-comps-unit-tests")

include_directories("../src" "/Development/Libraries/")
file(GLOB SOURCES "../src/*.cpp" "../src/*.hpp")

add_executable (unit-tests "test_main.cpp" catch.hpp "test_ctors_and_indexing.cpp" "test_decompositions.cpp" "test_operators.cpp" "test_utility.hpp" "test_utility.cpp" ${SOURCES} "test_unary_operations.cpp")