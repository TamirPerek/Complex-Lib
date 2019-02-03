#include <iostream>
#include "complex.hpp"

int main(void)
{
    complex<double> test(3, 2);
    complex<double> test2(0, 0, 8, 90);
    complex<double> result;

    std::cout << "Test: " << std::endl
              << test.toString() << std::endl
              << std::endl;
    std::cout << "Test2: " << std::endl
              << test.toString(test2) << std::endl
              << std::endl;

    // conjugate
    result = test.conjugate();

    std::cout << "Result conjugate:" << std::endl
              << result.toString() << std::endl
              << std::endl;

    // ++result
    result = test;
    ++result;

    std::cout << "++ Result:" << std::endl
              << result.toString() << std::endl
              << std::endl;

    // ++result
    result = test;
    --result;

    std::cout << "-- Result:" << std::endl
              << result.toString() << std::endl
              << std::endl;

    // result++
    result = test;
    result++;

    std::cout << "Result ++:" << std::endl
              << result.toString() << std::endl
              << std::endl;

    // result--
    result = test;
    result--;

    std::cout << "Result --:" << std::endl
              << result.toString() << std::endl
              << std::endl;

    // result+=test
    result = test;
    result += test;

    std::cout << "Result += test:" << std::endl
              << result.toString() << std::endl
              << std::endl;

    // result-=test2
    result = test;
    result -= test2;

    std::cout << "Result -= test2:" << std::endl
              << result.toString() << std::endl
              << std::endl;

    // result*=test
    result = test;
    result *= test;

    std::cout << "Result *= test:" << std::endl
              << result.toString() << std::endl
              << std::endl;

    // result/=test2
    result = test;
    result /= test2;

    std::cout << "Result /= test2:" << std::endl
              << result.toString() << std::endl
              << std::endl;

    // result = test + test2
    result = test + test2;

    std::cout << "Result = test + test2:" << std::endl
              << result.toString() << std::endl
              << std::endl;

    // result = test + 2.0
    result = test + 2.0;

    std::cout << "Result = test + 2.0:" << std::endl
              << result.toString() << std::endl
              << std::endl;

    // result = 2.0 + test2
    result = 2.0 + test2;

    std::cout << "Result = 2.0 + test2:" << std::endl
              << result.toString() << std::endl
              << std::endl;

    // result = test - test2
    result = test - test2;

    std::cout << "Result = test - test2:" << std::endl
              << result.toString() << std::endl
              << std::endl;

    // result = test - 2.0
    result = test - 2.0;

    std::cout << "Result = test - 2.0:" << std::endl
              << result.toString() << std::endl
              << std::endl;

    // result = 2.0 - test2
    result = 2.0 - test2;

    std::cout << "Result = 2.0 - test2:" << std::endl
              << result.toString() << std::endl
              << std::endl;

    // result = test * test2
    result = test * test2;

    std::cout << "Result = test * test2:" << std::endl
              << result.toString() << std::endl
              << std::endl;

    // result = test * 2.0
    result = test * 2.0;

    std::cout << "Result = test * 2.0:" << std::endl
              << result.toString() << std::endl
              << std::endl;

    // result = 2.0 * test2
    result = 2.0 * test2;

    std::cout << "Result = 2.0 * test2:" << std::endl
              << result.toString() << std::endl
              << std::endl;

    // result = test / test2
    result = test / test2;

    std::cout << "Result = test / test2:" << std::endl
              << result.toString() << std::endl
              << std::endl;

    // result = test / 2.0
    result = test / 2.0;

    std::cout << "Result = test / 2.0:" << std::endl
              << result.toString() << std::endl
              << std::endl;

    // result = 2.0 / test2
    result = 2.0 / test2;

    std::cout << "Result = 2.0 / test2:" << std::endl
              << result.toString() << std::endl
              << std::endl;

    return -1;
}