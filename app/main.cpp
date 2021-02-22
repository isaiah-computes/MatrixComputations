#include <algorithm>
#include <chrono>
#include <execution>
#include <iostream>
#include <numeric>
#include "../src/Matrix.hpp"

using std::cout;

int main()
{

    int num_observations = 2500;
    int num_dimensions = 175;

    Matrix m1 = Matrix::Random(num_observations, num_dimensions);
    Matrix m2 = Matrix::RandomSymmetric(num_dimensions);

    std::cout << "Executing standard multiplication..." << "\n";
    auto t1 = std::chrono::high_resolution_clock::now();
    Matrix rotated_data = m1 * m2;
    auto t2 = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::seconds>(t2 - t1).count();
    std::cout << "Data rotated. Time elapsed " << duration << "\n";
    
    std::vector<int> row_indices(num_observations);
    std::iota(row_indices.begin(), row_indices.end(), 0);

    std::cout << "\nExecuting parallel multiplication..." << "\n";

    t1 = std::chrono::high_resolution_clock::now();

    Matrix output(num_observations, num_dimensions);

    std::for_each(
        std::execution::par_unseq, row_indices.begin(), row_indices.end(), [&](int i)
        {
            for (int j = 0; j < num_dimensions; j++) {
                for (int k = 0; k < num_dimensions; k++) {
                    output(i, j) += m1(i, j) * m2(k, j);
                }
            }
        });

    t2 = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::seconds>(t2 - t1).count();
    std::cout << "Data rotated. Time elapsed " << duration << "\n";
    std::cin.get();
    

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

    /*
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
    */
}
