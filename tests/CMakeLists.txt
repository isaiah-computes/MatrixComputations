
cmake_minimum_required (VERSION 3.8)

project ("matrix-comps-unit-tests")

include_directories("../src")
file(GLOB SOURCES "../src/*.cpp")

add_executable (unit-tests main.cpp catch.hpp tests.cpp tests_decompositions.cpp tests_operators.cpp ${SOURCES})

# copy text files for matrix multiplication unit tests
file(GLOB TEST_MAT_FILES "${CMAKE_SOURCE_DIR}/*.txt")
add_custom_command(
	TARGET unit-tests PRE_BUILD 
	COMMAND ${CMAKE_COMMAND} -E copy
	${TEST_MAT_FILES} $<TARGET_FILE_DIR:unit-tests>)