#include "Catch.hpp"
#include "../src/Matrix.hpp"


TEST_CASE( "Identity generates diagonal matrix of ones") {

    int num_rows = 5;

    Matrix m = Matrix::Identity(num_rows);
    Matrix t = Matrix(num_rows,num_rows);

    for (int i = 0; i < num_rows; i++) {
        t(i,i) = 1.0;
    }

    for (int i = 0; i<num_rows; i++)
    {
        for (int j = 0; j < num_rows; j++)
        {
            REQUIRE(m(i,j)==t(i,j));
        }
    }

    /*for (int i = 0; i < num_rows; i++){
        REQUIRE_THAT(m[i], Catch::Matchers::Equals(t[i]));
    }*/
}