
#include <iostream>
#include "Matrix.hpp"

using std::cout;

int main()
{
    // quick test of element assignment
    Matrix m(3, 3);
    m(0, 0) = 1;
    m(1, 1) = 2;
    m(2, 2) = 3;

    m.Print();

    Matrix identity = Matrix::Identity(3);

    Matrix mPlus = identity + m;
    cout << "\n";
    mPlus.Print();

    Matrix mMinus = identity - m;
    cout << "\n";
    mMinus.Print();

    std::cin.get();
    return 0;
}
