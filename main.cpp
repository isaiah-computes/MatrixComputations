
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

    try 
    {
        cout << m(3, 2);
    }
    catch (const std::exception& e)
    {
        cout << "\n" << e.what() << "\n";
    }

    Matrix i2 = Matrix::Identity(4);
    
    try
    {
        mPlus = i2 + m;
    }
    catch (const std::exception& e)
    {
        cout << "\n" << e.what() << "\n";
    }

    try 
    {
        mPlus = i2 - m;
    }
    catch (const std::exception& e)
    {
        cout << "\n" << e.what() << "\n";
    }


    std::cin.get();
    return 0;
}
