#include <iostream>
#include <vector>
#include "complex.hpp"
#include "matrix/matrix.hpp"

#define MATRIXROW 5
#define MATRIXCOLUMNS 2

int main(void)
{
    std::vector<std::vector<Complex<double>>> vector;

    std::srand(static_cast<unsigned int>(time(NULL)));
    for (size_t i = 0; i < MATRIXROW; i++)
    {
        std::vector<Complex<double>> newRow;
        for (size_t j = 0; j < MATRIXCOLUMNS; j++)
        {
            Complex<double> element((static_cast<double>((std::rand()) % 10000000)) / 100000, (static_cast<double>((std::rand()) % 10000000)) / 100000);
            newRow.push_back(element);
        }
        vector.push_back(newRow);
    }

    Matrix<Complex<double>> matrix_a = Matrix<Complex<double>>::create(vector);
    std::cout << "Matrix A\n"
              << matrix_a << "\n\n";

    vector.clear();

    for (size_t i = 0; i < MATRIXROW; i++)
    {
        std::vector<Complex<double>> newRow;
        for (size_t j = 0; j < MATRIXCOLUMNS; j++)
        {
            Complex<double> element((static_cast<double>((std::rand()) % 10000000)) / 100000, (static_cast<double>((std::rand()) % 10000000)) / 100000);
            newRow.push_back(element);
        }
        vector.push_back(newRow);
    }
    Matrix<Complex<double>> matrix_b = Matrix<Complex<double>>::create(vector);
    std::cout << "Matrix B\n"
              << matrix_b << "\n\n";

    Matrix<Complex<double>> result = Matrix<Complex<double>>::create(matrix_a + matrix_b);
    std::cout << "Result = Matrix A + Matrix B\n"
              << result << "\n\n";

    matrix_a += matrix_b;
    std::cout << "Matrix A += Matrix B\n"
              << result << "\n\n";

    if (result == matrix_a)
        std::cout << "Result == Matrix A\n\n";
    else
        std::cout << "Result != Matrix A\n\n";

    result = Matrix<Complex<double>>::create(matrix_b + Complex<double>(42.0, 34));
    std::cout << "Result = Matrix B + 42.0 j 34\n"
              << result << "\n\n";

    // Subtraction
    result = Matrix<Complex<double>>::create(matrix_a - matrix_b);
    std::cout << "Result = Matrix A - Matrix B\n"
              << result << "\n\n";

    matrix_a -= matrix_b;
    std::cout << "Matrix A -= Matrix B\n"
              << result << "\n\n";

    if (result == matrix_a)
        std::cout << "Result == Matrix A\n\n";
    else
        std::cout << "Result != Matrix A\n\n";

    result = Matrix<Complex<double>>::create(matrix_b - Complex<double>(42.0, 34));
    std::cout << "Result = Matrix B - 42.0 j 34\n"
              << result << "\n\n";

    // Multiplication
    result = Matrix<Complex<double>>::create(matrix_a * matrix_b);
    std::cout << "Result = Matrix A * Matrix B\n"
              << result << "\n\n";

    matrix_a *= matrix_b;
    std::cout << "Matrix A *= Matrix B\n"
              << result << "\n\n";

    if (result == matrix_a)
        std::cout << "Result == Matrix A\n\n";
    else
        std::cout << "Result != Matrix A\n\n";

    result = Matrix<Complex<double>>::create(matrix_b * Complex<double>(42.0, 34));
    std::cout << "Result = Matrix B * 42.0 j 34\n"
              << result << "\n\n";

    // Equals
    result = Matrix<Complex<double>>::create(matrix_b);
    if (result == matrix_b)
        std::cout << "Result == Matrix B\n\n";
    else
        std::cout << "Result != Matrix B\n\n";
    if (result != matrix_a)
        std::cout << "Result != Matrix B\n\n";
    else
        std::cout << "Result == Matrix B\n\n";

    // Matrix<Complex<double>> result = Matrix<Complex<double>>::create(matrix_a - matrix_b);
    // std::cout << "Matrix A - Matrix B\n"
    //           << result << "\n\n";

    // Matrix<Complex<double>> result = Matrix<Complex<double>>::create(matrix_a * matrix_b);
    // std::cout << "Matrix A * Matrix B\n"
    //           << result << "\n\n";

    // Complex<double> test = Complex<double>::create(3, 2);
    // Complex<double> test2 = Complex<double>::create(0, 0, 8, 90);
    // Complex<double> result = Complex<double>::create();

    // std::cout << "Test: " << '\n'
    //           << test << '\n'
    //           << '\n';
    // std::cout << "Test2: " << '\n'
    //           << Complex<double>::toString(test2) << '\n'
    //           << '\n';

    // // conjugate
    // result = test.conjugate();

    // std::cout << "Result conjugate:" << '\n'
    //           << result << '\n'
    //           << '\n';

    // // ++result
    // result = test;
    // ++result;

    // std::cout << "++ Result:" << '\n'
    //           << result << '\n'
    //           << '\n';

    // // ++result
    // result = test;
    // --result;

    // std::cout << "-- Result:" << '\n'
    //           << result << '\n'
    //           << '\n';

    // // result++
    // result = test;
    // result++;

    // std::cout << "Result ++:" << '\n'
    //           << result << '\n'
    //           << '\n';

    // // result--
    // result = test;
    // result--;

    // std::cout << "Result --:" << '\n'
    //           << result << '\n'
    //           << '\n';

    // // result+=test
    // result = test;
    // result += test;

    // std::cout << "Result += test:" << '\n'
    //           << result << '\n'
    //           << '\n';

    // // result-=test2
    // result = test;
    // result -= test2;

    // std::cout << "Result -= test2:" << '\n'
    //           << result << '\n'
    //           << '\n';

    // // result*=test
    // result = test;
    // result *= test;

    // std::cout << "Result *= test:" << '\n'
    //           << result << '\n'
    //           << '\n';

    // // result/=test2
    // result = test;
    // result /= test2;

    // std::cout << "Result /= test2:" << '\n'
    //           << result << '\n'
    //           << '\n';

    // // result = test + test2
    // result = test + test2;

    // std::cout << "Result = test + test2:" << '\n'
    //           << result << '\n'
    //           << '\n';

    // // result = test + 2.0
    // result = test + 2.0;

    // std::cout << "Result = test + 2.0:" << '\n'
    //           << result << '\n'
    //           << '\n';

    // // result = 2.0 + test2
    // result = 2.0 + test2;

    // std::cout << "Result = 2.0 + test2:" << '\n'
    //           << result << '\n'
    //           << '\n';

    // // result = test - test2
    // result = test - test2;

    // std::cout << "Result = test - test2:" << '\n'
    //           << result << '\n'
    //           << '\n';

    // // result = test - 2.0
    // result = test - 2.0;

    // std::cout << "Result = test - 2.0:" << '\n'
    //           << result << '\n'
    //           << '\n';

    // // result = 2.0 - test2
    // result = 2.0 - test2;

    // std::cout << "Result = 2.0 - test2:" << '\n'
    //           << result << '\n'
    //           << '\n';

    // // result = test * test2
    // result = test * test2;

    // std::cout << "Result = test * test2:" << '\n'
    //           << result << '\n'
    //           << '\n';

    // // result = test * 2.0
    // result = test * 2.0;

    // std::cout << "Result = test * 2.0:" << '\n'
    //           << result << '\n'
    //           << '\n';

    // // result = 2.0 * test2
    // result = 2.0 * test2;

    // std::cout << "Result = 2.0 * test2:" << '\n'
    //           << result << '\n'
    //           << '\n';

    // // result = test / test2
    // result = test / test2;

    // std::cout << "Result = test / test2:" << '\n'
    //           << result << '\n'
    //           << '\n';

    // // result = test / 2.0
    // result = test / 2.0;

    // std::cout << "Result = test / 2.0:" << '\n'
    //           << result << '\n'
    //           << '\n';

    // // result = 2.0 / test2
    // result = 2.0 / test2;

    // std::cout << "Result = 2.0 / test2:" << '\n'
    //           << result << '\n'
    //           << '\n';

    return EXIT_SUCCESS;
}