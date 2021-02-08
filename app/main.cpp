
#include <iostream>
#include "../src/Matrix.hpp"

using std::cout;

int main()
{
    /*
    // output from random constructor
    Matrix m2 = Matrix::Random(5, 7);
    cout << m2 << "\n\n";
    
    // quick test of manual element assignment
    Matrix m(3, 3);
    m(0, 0) = 1;
    m(1, 1) = 2;
    m(2, 2) = 3;

    cout << m;
    m = Matrix::Random(7, 12);
    m.ToFile("test_mat.txt");
    Matrix m3 = Matrix::FromFile("test_mat.txt");

    cout << "\n\nRANDOM MATRIX\n\n";
    cout << m.Rows() << "  x  " << m.Columns() << "\n";
    cout << m;
    cout << "\n\nAFTER READING\n\n";
    cout << m3.Rows() << "  x  " << m3.Columns() << "\n";
    cout << m3;*/

    Matrix m1 = Matrix::FromFile("../tests/matmul_m1.txt", ' ');
    Matrix m2 = Matrix::FromFile("../tests/matmul_m2.txt", ' ');
    Matrix m3 = Matrix::FromFile("../tests/matmul_m3.txt", ' ');

    cout << " M1 : " << m1.Rows() << " x " << m1.Columns() << "\n\n";
    cout << " M2 : " << m2.Rows() << " x " << m2.Columns() << "\n\n";
    cout << " M3 : " << m3.Rows() << " x " << m3.Columns() << "\n\n";

    Matrix m4 = m1 * m2;

    cout << m4(0, 0) << " vs. " << m3(0, 0) << "\n";

    std::cin.get();
    return 0;
}
