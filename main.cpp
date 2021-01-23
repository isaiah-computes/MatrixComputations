
#include <iostream>
#include "Matrix.hpp"

using std::cout;

int main()
{
    // quick test of element assignment
    Matrix m = Matrix::Matrix(3, 3);
    m(0, 0) = 1;
    m(1, 1) = 2;
    m(2, 2) = 3;

    for (int i = 0; i < m.Rows(); i++)
    {
        for (int j = 0; j < m.Columns(); j++)
        {
            cout << " " << m(i, j) << " ";
        }
        cout << "\n";
    }

    std::cin.get();
    return 0;
}
