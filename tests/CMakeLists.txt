
cmake_minimum_required (VERSION 3.8)

project ("matrix-comps-unit-tests")

include_directories("../src" "/Development/Libraries/")
file(GLOB SOURCES "../src/*.cpp" "../src/*.hpp")

add_executable (unit-tests main.cpp catch.hpp tests.cpp tests_decompositions.cpp tests_operators.cpp ${SOURCES})