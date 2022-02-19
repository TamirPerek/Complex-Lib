#include <iostream>
#include <vector>
#include "Complex.hpp"

#include <gtest/gtest.h>

typedef Complex<double> Comp;

struct ComplexTest : public testing::Test
{
    Comp m_Number;

    void SetUp() final
    {
        m_Number.setReal(8.0);
        m_Number.setImaginary(-7.0);
        // Cartesian: 8.000000 -j 7.000000
        // Polar: 10.63014581273465(cos(-0.71882999962162453°) +j sin(-0.71882999962162453°))
    }

    const Comp &Get() const noexcept
    {
        return m_Number;
    }
};

TEST_F(ComplexTest, Create)
{
    Comp tNumberEmpty{};
    EXPECT_DOUBLE_EQ(tNumberEmpty.getReal(), 0.0);
    EXPECT_DOUBLE_EQ(tNumberEmpty.getImaginary(), 0.0);
    EXPECT_DOUBLE_EQ(tNumberEmpty.getAbsolute(), 0.0);
    EXPECT_DOUBLE_EQ(tNumberEmpty.getPhi(), 0.0);

    Comp tNumber{12.0, 23.0};
    EXPECT_DOUBLE_EQ(tNumber.getReal(), 12.0);
    EXPECT_DOUBLE_EQ(tNumber.getImaginary(), 23.0);
    EXPECT_DOUBLE_EQ(tNumber.getAbsolute(), 25.942243542145693);
    EXPECT_DOUBLE_EQ(tNumber.getPhi(), 1.0899090465995609);

    Comp tNumber2{0, 0, 25.0, 1.08};
    EXPECT_DOUBLE_EQ(tNumber2.getReal(), 11.783209104343499);
    EXPECT_DOUBLE_EQ(tNumber2.getImaginary(), 22.048945172123688);
    EXPECT_DOUBLE_EQ(tNumber2.getAbsolute(), 25.0);
    EXPECT_DOUBLE_EQ(tNumber2.getPhi(), 1.08);

    EXPECT_DOUBLE_EQ(Get().getReal(), 8.0);
    EXPECT_DOUBLE_EQ(Get().getImaginary(), -7.0);
    EXPECT_DOUBLE_EQ(Get().getAbsolute(), 10.63014581273465);
    EXPECT_DOUBLE_EQ(Get().getPhi(), -0.71882999962162453);
}

TEST_F(ComplexTest, Copy)
{
    auto tNumber{Get()};

    EXPECT_DOUBLE_EQ(tNumber.getReal(), 8.0);
    EXPECT_DOUBLE_EQ(tNumber.getImaginary(), -7.0);
    EXPECT_DOUBLE_EQ(tNumber.getAbsolute(), 10.63014581273465);
    EXPECT_DOUBLE_EQ(tNumber.getPhi(), -0.71882999962162453);
}

TEST_F(ComplexTest, CopyAssign)
{
    auto tNumber = Get();

    EXPECT_DOUBLE_EQ(tNumber.getReal(), 8.0);
    EXPECT_DOUBLE_EQ(tNumber.getImaginary(), -7.0);
    EXPECT_DOUBLE_EQ(tNumber.getAbsolute(), 10.63014581273465);
    EXPECT_DOUBLE_EQ(tNumber.getPhi(), -0.71882999962162453);
}

TEST_F(ComplexTest, Move)
{
    auto tNumber_temp{Get()};
    auto tNumber{std::move(tNumber_temp)};

    EXPECT_DOUBLE_EQ(tNumber.getReal(), 8.0);
    EXPECT_DOUBLE_EQ(tNumber.getImaginary(), -7.0);
    EXPECT_DOUBLE_EQ(tNumber.getAbsolute(), 10.63014581273465);
    EXPECT_DOUBLE_EQ(tNumber.getPhi(), -0.71882999962162453);
}

TEST_F(ComplexTest, MoveAssign)
{
    auto tNumber_temp{Get()};
    auto tNumber = std::move(tNumber_temp);

    EXPECT_DOUBLE_EQ(tNumber.getReal(), 8.0);
    EXPECT_DOUBLE_EQ(tNumber.getImaginary(), -7.0);
    EXPECT_DOUBLE_EQ(tNumber.getAbsolute(), 10.63014581273465);
    EXPECT_DOUBLE_EQ(tNumber.getPhi(), -0.71882999962162453);
}

TEST_F(ComplexTest, Swap)
{
    auto tNumber_temp{Get()};
    Comp tNumber{12.0, 23.0};

    std::swap(tNumber, tNumber_temp);

    EXPECT_DOUBLE_EQ(tNumber.getReal(), 8.0);
    EXPECT_DOUBLE_EQ(tNumber.getImaginary(), -7.0);
    EXPECT_DOUBLE_EQ(tNumber.getAbsolute(), 10.63014581273465);
    EXPECT_DOUBLE_EQ(tNumber.getPhi(), -0.71882999962162453);

    EXPECT_DOUBLE_EQ(tNumber_temp.getReal(), 12.0);
    EXPECT_DOUBLE_EQ(tNumber_temp.getImaginary(), 23.0);
    EXPECT_DOUBLE_EQ(tNumber_temp.getAbsolute(), 25.942243542145693);
    EXPECT_DOUBLE_EQ(tNumber_temp.getPhi(), 1.0899090465995609);
}

TEST_F(ComplexTest, Conjugate)
{
    auto tNumber = Get();
    tNumber.conjugate();

    EXPECT_DOUBLE_EQ(tNumber.getReal(), 8.0);
    EXPECT_DOUBLE_EQ(tNumber.getImaginary(), 7.0);
    EXPECT_DOUBLE_EQ(tNumber.getAbsolute(), 10.63014581273465);
    EXPECT_DOUBLE_EQ(tNumber.getPhi(), 0.71882999962162453);
}

TEST_F(ComplexTest, Addition)
{
    auto tNumber1 = Get();
    auto tNumber2 = Get();

    auto tResult1 = tNumber1 + tNumber2;
    EXPECT_DOUBLE_EQ(tResult1.getReal(), 16.0);
    EXPECT_DOUBLE_EQ(tResult1.getImaginary(), -14.0);
    EXPECT_DOUBLE_EQ(tResult1.getAbsolute(), 21.2602916254693);
    EXPECT_DOUBLE_EQ(tResult1.getPhi(), -0.71882999962162453);

    auto tResult2 = tNumber1 + 2.5;
    EXPECT_DOUBLE_EQ(tResult2.getReal(), 10.5);
    EXPECT_DOUBLE_EQ(tResult2.getImaginary(), -7.0);
    EXPECT_DOUBLE_EQ(tResult2.getAbsolute(), 12.619429464123963);
    EXPECT_DOUBLE_EQ(tResult2.getPhi(), -0.5880026035475675);

    auto tResult3 = 2.5 + tNumber1;
    EXPECT_DOUBLE_EQ(tResult3.getReal(), 10.5);
    EXPECT_DOUBLE_EQ(tResult3.getImaginary(), -7.0);
    EXPECT_DOUBLE_EQ(tResult3.getAbsolute(), 12.619429464123963);
    EXPECT_DOUBLE_EQ(tResult3.getPhi(), -0.5880026035475675);

    tNumber1 += tNumber2;
    EXPECT_DOUBLE_EQ(tNumber1.getReal(), 16.0);
    EXPECT_DOUBLE_EQ(tNumber1.getImaginary(), -14.0);
    EXPECT_DOUBLE_EQ(tNumber1.getAbsolute(), 21.2602916254693);
    EXPECT_DOUBLE_EQ(tNumber1.getPhi(), -0.71882999962162453);

    tNumber1 = Get();
    tNumber1 += 2.5;
    EXPECT_DOUBLE_EQ(tNumber1.getReal(), 10.5);
    EXPECT_DOUBLE_EQ(tNumber1.getImaginary(), -7.0);
    EXPECT_DOUBLE_EQ(tNumber1.getAbsolute(), 12.619429464123963);
    EXPECT_DOUBLE_EQ(tNumber1.getPhi(), -0.5880026035475675);
}

TEST_F(ComplexTest, Subtraction)
{
    auto tNumber1 = Get() + Get();
    auto tNumber2 = Get();

    auto tResult1 = tNumber1 - tNumber2;
    EXPECT_DOUBLE_EQ(tResult1.getReal(), 8.0);
    EXPECT_DOUBLE_EQ(tResult1.getImaginary(), -7.0);
    EXPECT_DOUBLE_EQ(tResult1.getAbsolute(), 10.63014581273465);
    EXPECT_DOUBLE_EQ(tResult1.getPhi(), -0.71882999962162453);

    auto tResult2 = tNumber1 - 2.5;
    EXPECT_DOUBLE_EQ(tResult2.getReal(), 13.5);
    EXPECT_DOUBLE_EQ(tResult2.getImaginary(), -14.0);
    EXPECT_DOUBLE_EQ(tResult2.getAbsolute(), 19.448650338776723);
    EXPECT_DOUBLE_EQ(tResult2.getPhi(), -0.80357797847042656);

    auto tResult3 = 2.5 - tNumber1;
    EXPECT_DOUBLE_EQ(tResult3.getReal(), -13.5);
    EXPECT_DOUBLE_EQ(tResult3.getImaginary(), 14.0);
    EXPECT_DOUBLE_EQ(tResult3.getAbsolute(), 19.448650338776723);
    EXPECT_DOUBLE_EQ(tResult3.getPhi(), -0.80357797847042656);

    tNumber1 -= tNumber2;
    EXPECT_DOUBLE_EQ(tNumber1.getReal(), 8.0);
    EXPECT_DOUBLE_EQ(tNumber1.getImaginary(), -7.0);
    EXPECT_DOUBLE_EQ(tNumber1.getAbsolute(), 10.63014581273465);
    EXPECT_DOUBLE_EQ(tNumber1.getPhi(), -0.71882999962162453);

    tNumber1 = Get() + Get();
    tNumber1 -= 2.5;
    EXPECT_DOUBLE_EQ(tNumber1.getReal(), 13.5);
    EXPECT_DOUBLE_EQ(tNumber1.getImaginary(), -14.0);
    EXPECT_DOUBLE_EQ(tNumber1.getAbsolute(), 19.448650338776723);
    EXPECT_DOUBLE_EQ(tNumber1.getPhi(), -0.80357797847042656);
}

TEST_F(ComplexTest, Mulitplication)
{
    auto tNumber1 = Get();
    auto tNumber2 = Get();

    auto tResult1 = tNumber1 * tNumber2;
    EXPECT_DOUBLE_EQ(tResult1.getReal(), 15.0);
    EXPECT_DOUBLE_EQ(tResult1.getImaginary(), -112.0);
    EXPECT_DOUBLE_EQ(tResult1.getAbsolute(), 113.0);
    EXPECT_DOUBLE_EQ(tResult1.getPhi(), -1.4376599992432491);

    auto tResult2 = tNumber1 * 2.5;
    EXPECT_DOUBLE_EQ(tResult2.getReal(), 20);
    EXPECT_DOUBLE_EQ(tResult2.getImaginary(), -17.5);
    EXPECT_DOUBLE_EQ(tResult2.getAbsolute(), 26.575364531836623);
    EXPECT_DOUBLE_EQ(tResult2.getPhi(), -0.71882999962162453);

    auto tResult3 = 2.5 * tNumber1;
    EXPECT_DOUBLE_EQ(tResult3.getReal(), 20);
    EXPECT_DOUBLE_EQ(tResult3.getImaginary(), -17.5);
    EXPECT_DOUBLE_EQ(tResult3.getAbsolute(), 26.575364531836623);
    EXPECT_DOUBLE_EQ(tResult3.getPhi(), -0.71882999962162453);

    tNumber1 *= tNumber2;
    EXPECT_DOUBLE_EQ(tNumber1.getReal(), 15.0);
    EXPECT_DOUBLE_EQ(tNumber1.getImaginary(), -112.0);
    EXPECT_DOUBLE_EQ(tNumber1.getAbsolute(), 113.0);
    EXPECT_DOUBLE_EQ(tNumber1.getPhi(), -1.4376599992432491);

    tNumber1 = Get();
    tNumber1 *= 2.5;
    EXPECT_DOUBLE_EQ(tNumber1.getReal(), 20);
    EXPECT_DOUBLE_EQ(tNumber1.getImaginary(), -17.5);
    EXPECT_DOUBLE_EQ(tNumber1.getAbsolute(), 26.575364531836623);
    EXPECT_DOUBLE_EQ(tNumber1.getPhi(), -0.71882999962162453);
}

TEST_F(ComplexTest, Division)
{
    auto tNumber1 = Get() + Get();
    auto tNumber2 = Get();

    auto tResult1 = tNumber1 / tNumber2;
    EXPECT_DOUBLE_EQ(tResult1.getReal(), 2.0);
    EXPECT_DOUBLE_EQ(tResult1.getImaginary(), 0.0);
    EXPECT_DOUBLE_EQ(tResult1.getAbsolute(), 2.0);
    EXPECT_DOUBLE_EQ(tResult1.getPhi(), 0.0);

    auto tResult2 = tNumber1 / 2.5;
    EXPECT_DOUBLE_EQ(tResult2.getReal(), 6.4000000000000004);
    EXPECT_DOUBLE_EQ(tResult2.getImaginary(), -5.5999999999999996);
    EXPECT_DOUBLE_EQ(tResult2.getAbsolute(), 8.5041166501877203);
    EXPECT_DOUBLE_EQ(tResult2.getPhi(), -0.71882999962162442);

    auto tResult3 = 2.5 / tNumber1;
    EXPECT_DOUBLE_EQ(tResult3.getReal(), 0.088495575221238937);
    EXPECT_DOUBLE_EQ(tResult3.getImaginary(), 0.077433628318584066);
    EXPECT_DOUBLE_EQ(tResult3.getAbsolute(), 0.11759010854794967);
    EXPECT_DOUBLE_EQ(tResult3.getPhi(), 0.71882999962162453);

    tNumber1 /= tNumber2;
    EXPECT_DOUBLE_EQ(tNumber1.getReal(), 2.0);
    EXPECT_DOUBLE_EQ(tNumber1.getImaginary(), 0.0);
    EXPECT_DOUBLE_EQ(tNumber1.getAbsolute(), 2.0);
    EXPECT_DOUBLE_EQ(tNumber1.getPhi(), 0.0);

    tNumber1 = Get() + Get();
    tNumber1 /= 2.5;
    EXPECT_DOUBLE_EQ(tNumber1.getReal(), 6.4000000000000004);
    EXPECT_DOUBLE_EQ(tNumber1.getImaginary(), -5.5999999999999996);
    EXPECT_DOUBLE_EQ(tNumber1.getAbsolute(), 8.5041166501877203);
    EXPECT_DOUBLE_EQ(tNumber1.getPhi(), -0.71882999962162442);
}

TEST_F(ComplexTest, CompareEquals)
{
    const auto tNumber = Get();
    const double tComp = 8.0;

    EXPECT_TRUE(tNumber == tNumber);
    EXPECT_TRUE(tNumber == tComp);
    EXPECT_TRUE(tComp == tNumber);
}

TEST_F(ComplexTest, CompareNotEquals)
{
    const auto tNumber1 = Get();
    const auto tNumber2 = Get() + Get();
    const double tComp = 16.0;

    EXPECT_TRUE(tNumber1 != tNumber2);
    EXPECT_TRUE(tNumber1 != tComp);
    EXPECT_TRUE(tComp != tNumber1);
}

// TEST_F(ComplexTest, DontCompile)
// {
//     Complex<std::string> tNumber;
// }
