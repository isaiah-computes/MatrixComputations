
#include <iostream>
#include "../src/Matrix.hpp"

using std::cout;

int main()
{
    // output from random constructor
    Matrix m2 = Matrix::Random(5, 7);
    cout << m2 << "\n\n";
    
    // quick test of manual element assignment
    Matrix m(3, 3);
    m(0, 0) = 1;
    m(1, 1) = 2;
    m(2, 2) = 3;

    cout << m;

    std::cin.get();
    return 0;
}
