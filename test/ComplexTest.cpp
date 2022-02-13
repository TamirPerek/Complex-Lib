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
