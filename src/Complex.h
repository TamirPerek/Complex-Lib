#pragma once

#include <string>
#include <cmath>

template<class T>
struct default_sin
{
    static_assert(!std::is_function_v<T>, "default_sin cannot be instantiated for function types");
    constexpr default_sin() noexcept = default;
    [[nodiscard]] constexpr T operator()(T _in) const noexcept
    {
        return std::sin(_in);
    }
};
template <class T>
struct default_cos
{
    static_assert(!std::is_function_v<T>, "default_cos cannot be instantiated for function types");
    constexpr default_cos() noexcept = default;
    [[nodiscard]] constexpr T operator()(T _in) const noexcept
    {
        return std::cos(_in);
    }
};

template <class T>
struct default_pow2
{
    static_assert(!std::is_function_v<T>, "default_pow2 cannot be instantiated for function types");
    constexpr default_pow2() noexcept = default;
    [[nodiscard]] constexpr T operator()(T _in) const noexcept
    {
        return std::pow(_in, 2);
    }
};

template <class T>
struct default_sqrt
{
    static_assert(!std::is_function_v<T>, "default_sqrt cannot be instantiated for function types");
    constexpr default_sqrt() noexcept = default;
    [[nodiscard]] constexpr T operator()(T _in) const noexcept
    {
        return std::sqrt(_in);
    }
};

template <class T>
struct default_atan
{
    static_assert(!std::is_function_v<T>, "default_atan cannot be instantiated for function types");
    constexpr default_atan() noexcept = default;
    [[nodiscard]] constexpr T operator()(T _in) const noexcept
    {
        return std::atan(_in);
    }
};

template <typename T, class SIN = default_sin<T>, class COS = default_cos<T>, class POW2 = default_pow2<T>, class SQRT = default_sqrt<T>, class ATAN = default_atan<T>>
class Complex
{
private:
    T re = 0;
    T img = 0;
    T abs = 0;
    T phi = 0;
    SIN mSin;
    COS mCos;
    POW2 mPow2;
    SQRT mSqrt;
    ATAN mAtan;

    constexpr void calculatePolarValues() noexcept(std::is_nothrow_copy_assignable_v<T> &&std::is_nothrow_move_assignable_v<T>)
    {
        this->abs = mSqrt(mPow2(this->re) + mPow2(this->img));
        if constexpr (std::is_convertible_v<T, double>)
            this->phi = mAtan(static_cast<double>(this->img) / this->re);
        else if constexpr (std::is_convertible_v<T, long double>)
            this->phi = mAtan(static_cast<long double>(this->img) / this->re);
        else if constexpr (std::is_convertible_v<T, long>)
            this->phi = mAtan(static_cast<long>(this->img) / this->re);
        else
            static_assert(!std::is_convertible_v<T, double> || !std::is_convertible_v<T, long double> || !std::is_convertible_v<T, long>, "Type does not match");
    }
    constexpr void calculateCartesianValues() noexcept(std::is_nothrow_copy_assignable_v<T> &&std::is_nothrow_move_assignable_v<T>)
    {
        this->re = static_cast<T>(this->abs) * mCos(this->phi);
        this->img = static_cast<T>(this->abs) * mSin(this->phi);
    }

public:
    constexpr Complex() noexcept(std::is_nothrow_constructible_v<T>) = default;
    
    explicit constexpr Complex(const T &_re, const T &_img = 0, const T &_abs = 0, const T &_phi = 0) noexcept(std::is_nothrow_constructible_v<T>)
        : re(_re), img(_img), abs(_abs), phi(_phi)
    {
        if (_re != 0 || _img != 0)
            this->calculatePolarValues();
        else if (_abs != 0 || _phi != 0)
            this->calculateCartesianValues();
    }

    [[nodiscard]] constexpr const T &getReal() const noexcept { return this->re; }
    [[nodiscard]] constexpr const T &getImaginary() const noexcept { return this->img; }
    [[nodiscard]] constexpr const T &getAbsolute() const noexcept { return this->abs; }
    [[nodiscard]] constexpr const T &getPhi() const noexcept { return this->phi; }
    
    [[nodiscard]] constexpr const SIN &getSinusFunction() const noexcept {return mSin;}
    [[nodiscard]] constexpr const COS &getCosinusFunction() const noexcept {return mCos;}
    [[nodiscard]] constexpr const POW2 &getPowerOf2Function() const noexcept {return mPow2;}
    [[nodiscard]] constexpr const SQRT &getSquareRootFunction() const noexcept {return mSqrt;}
    [[nodiscard]] constexpr const ATAN &getArcusTangensFunction() const noexcept {return mAtan;}

    constexpr Complex &setReal(const T &_re) noexcept(std::is_nothrow_copy_assignable_v<T> &&std::is_nothrow_move_assignable_v<T>)
    {
        this->re = _re;
        this->calculatePolarValues();
        return *this;
    }
    constexpr Complex &setImaginary(const T &_img) noexcept(std::is_nothrow_copy_assignable_v<T> &&std::is_nothrow_move_assignable_v<T>)
    {
        this->img = _img;
        this->calculatePolarValues();
        return *this;
    }
    constexpr Complex &setAbsolute(const T &_abs) noexcept(std::is_nothrow_copy_assignable_v<T> &&std::is_nothrow_move_assignable_v<T>)
    {
        this->abs = _abs;
        this->calculateCartesianValues();
        return *this;
    }
    constexpr Complex &setPhi(const T &_phi) noexcept(std::is_nothrow_copy_assignable_v<T> &&std::is_nothrow_move_assignable_v<T>)
    {
        this->phi = _phi;
        this->calculateCartesianValues();
        return *this;
    }

    [[nodiscard]] std::string toString(void) const noexcept(false) { return Complex<T, SIN, COS, POW2, SQRT, ATAN>::toString(*this); }
    [[nodiscard]] static std::string toString(const Complex &_complex) noexcept(false)
    {
        if (_complex.getImaginary() < 0)
        {
            return "Cartesian: " + std::to_string(_complex.getReal()) + " -j " + std::to_string(_complex.getImaginary() * (-1)) + "\nPolar: " + std::to_string(_complex.getAbsolute()) + "(cos(" + std::to_string(_complex.getPhi()) + "°) +j sin(" + std::to_string(_complex.getPhi()) + "°))";
        }
        else
        {
            return "Cartesian: " + std::to_string(_complex.getReal()) + " +j " + std::to_string(_complex.getImaginary()) + "\nPolar: " + std::to_string(_complex.getAbsolute()) + "(cos(" + std::to_string(_complex.getPhi()) + "°) +j sin(" + std::to_string(_complex.getPhi()) + "°))";
        }
    }

    constexpr Complex<T, SIN, COS, POW2, SQRT, ATAN> &conjugate(void) noexcept(std::is_nothrow_copy_assignable_v<T> &&std::is_nothrow_move_assignable_v<T>)
    {
        this->img *= (-1);
        this->calculatePolarValues();
        return *this;
    }
    constexpr static Complex<T, SIN, COS, POW2, SQRT, ATAN> conjugate(const Complex<T, SIN, COS, POW2, SQRT, ATAN> &_complex) noexcept(std::is_nothrow_copy_assignable_v<T> &&std::is_nothrow_move_assignable_v<T>)
    {
        _complex.img *= (-1);
        _complex.calculatePolarValues();
        return _complex;
    }

    constexpr Complex<T, SIN, COS, POW2, SQRT, ATAN> &operator++() noexcept(std::is_nothrow_copy_assignable_v<T> &&std::is_nothrow_move_assignable_v<T>)
    {
        this->re++;
        this->calculatePolarValues();
        return *this;
    }
    constexpr Complex<T, SIN, COS, POW2, SQRT, ATAN> &operator--() noexcept(std::is_nothrow_copy_assignable_v<T> &&std::is_nothrow_move_assignable_v<T>)
    {
        this->re--;
        this->calculatePolarValues();
        return *this;
    }
    constexpr Complex<T, SIN, COS, POW2, SQRT, ATAN> operator++(int) noexcept(std::is_nothrow_copy_assignable_v<T> &&std::is_nothrow_move_assignable_v<T>)
    {
        Complex result(*this);
        ++(*this);
        return result;
    }
    constexpr Complex<T, SIN, COS, POW2, SQRT, ATAN> operator--(int) noexcept(std::is_nothrow_copy_assignable_v<T> &&std::is_nothrow_move_assignable_v<T>)
    {
        Complex result(*this);
        --(*this);
        return result;
    }

    constexpr Complex<T, SIN, COS, POW2, SQRT, ATAN> &operator+=(const T &_add) noexcept(std::is_nothrow_copy_assignable_v<T> &&std::is_nothrow_move_assignable_v<T>)
    {
        this->re += _add;
        this->calculatePolarValues();
        return *this;
    }
    constexpr Complex<T, SIN, COS, POW2, SQRT, ATAN> &operator+=(const Complex<T, SIN, COS, POW2, SQRT, ATAN> &_complex) noexcept(std::is_nothrow_copy_assignable_v<T> &&std::is_nothrow_move_assignable_v<T>)
    {
        this->re = this->re + _complex.getReal();
        this->img = this->img + _complex.getImaginary();
        this->calculatePolarValues();
        return *this;
    }
    constexpr Complex<T, SIN, COS, POW2, SQRT, ATAN> &operator-=(const Complex<T, SIN, COS, POW2, SQRT, ATAN> &_complex) noexcept(std::is_nothrow_copy_assignable_v<T> &&std::is_nothrow_move_assignable_v<T>)
    {
        this->re = this->re - _complex.getReal();
        this->img = this->img - _complex.getImaginary();
        this->calculatePolarValues();
        return *this;
    }

    constexpr Complex<T, SIN, COS, POW2, SQRT, ATAN> &operator-=(const T &_add) noexcept(std::is_nothrow_copy_assignable_v<T> &&std::is_nothrow_move_assignable_v<T>)
    {
        this->re -= _add;
        this->calculatePolarValues();
        return *this;
    }
    constexpr Complex<T, SIN, COS, POW2, SQRT, ATAN> &operator*=(const Complex<T, SIN, COS, POW2, SQRT, ATAN> &_complex) noexcept(std::is_nothrow_copy_assignable_v<T> &&std::is_nothrow_move_assignable_v<T>)
    {
        const auto tRe = (this->getReal() * _complex.getReal()) - (this->getImaginary() * _complex.getImaginary());
        const auto tImg = (this->getReal() * _complex.getImaginary()) + (this->getImaginary() * _complex.getReal());
        this->re = tRe;
        this->img = tImg;
        this->calculatePolarValues();
        return *this;
    }
    constexpr Complex<T, SIN, COS, POW2, SQRT, ATAN> &operator*=(const T &_add) noexcept(std::is_nothrow_copy_assignable_v<T> &&std::is_nothrow_move_assignable_v<T>)
    {
        this->re = this->re * _add;
        this->img = this->img * _add;
        this->calculatePolarValues();
        return *this;
    }
    constexpr Complex<T, SIN, COS, POW2, SQRT, ATAN> &operator/=(const Complex<T, SIN, COS, POW2, SQRT, ATAN> &_complex) noexcept(std::is_nothrow_copy_assignable_v<T> &&std::is_nothrow_move_assignable_v<T>)
    {
        const auto tRe = static_cast<T>((this->getReal() * _complex.getReal()) + (this->getImaginary() * _complex.getImaginary())) / (mPow2(_complex.getReal()) + mPow2(_complex.getImaginary()));
        const auto tImg = static_cast<T>(((this->getReal() * (-1)) * _complex.getImaginary()) + (_complex.getReal() * this->getImaginary())) / (mPow2(_complex.getReal()) + mPow2(_complex.getImaginary()));
        this->re = tRe;
        this->img = tImg;
        this->calculatePolarValues();
        return *this;
    }
    constexpr Complex<T, SIN, COS, POW2, SQRT, ATAN> &operator/=(const T &_add) noexcept(std::is_nothrow_copy_assignable_v<T> &&std::is_nothrow_move_assignable_v<T>)
    {
        const auto tRe = static_cast<T>((this->getReal() * _add)) / (mPow2(_add));
        const auto tImg = static_cast<T>((_add * this->getImaginary()) / mPow2(_add));
        this->re = tRe;
        this->img = tImg;
        this->calculatePolarValues();
        return *this;
    }

    // Addition
    constexpr Complex<T, SIN, COS, POW2, SQRT, ATAN> operator+(const Complex<T, SIN, COS, POW2, SQRT, ATAN> &_complex) const noexcept(std::is_nothrow_copy_assignable_v<T> &&std::is_nothrow_move_assignable_v<T> && std::is_nothrow_constructible_v<T>)
    {
        const auto tRe = this->getReal() + _complex.getReal();
        const auto tImg = this->getImaginary() + _complex.getImaginary();
        return Complex<T, SIN, COS, POW2, SQRT, ATAN>(tRe, tImg);
    }

    constexpr Complex<T, SIN, COS, POW2, SQRT, ATAN> operator+(const T &_add) const noexcept(std::is_nothrow_copy_assignable_v<T> &&std::is_nothrow_move_assignable_v<T> &&std::is_nothrow_constructible_v<T>)
    {
        const auto tRe = _add + this->getReal();
        const auto tImg = this->getImaginary();
        return Complex<T, SIN, COS, POW2, SQRT, ATAN>(tRe, tImg);
    }

    // Subtraction
    constexpr Complex<T, SIN, COS, POW2, SQRT, ATAN> operator-(const Complex<T, SIN, COS, POW2, SQRT, ATAN> &_complex) const noexcept(std::is_nothrow_copy_assignable_v<T> &&std::is_nothrow_move_assignable_v<T> &&std::is_nothrow_constructible_v<T>)
    {
        const auto tRe = this->getReal() - _complex.getReal();
        const auto tImg = this->getImaginary() - _complex.getImaginary();
        return Complex<T, SIN, COS, POW2, SQRT, ATAN>(tRe, tImg);
    }

    constexpr Complex<T, SIN, COS, POW2, SQRT, ATAN> operator-(const T &_add) const noexcept(std::is_nothrow_copy_assignable_v<T> &&std::is_nothrow_move_assignable_v<T> &&std::is_nothrow_constructible_v<T>)
    {
        const auto tRe = this->getReal() - _add;
        const auto tImg = this->getImaginary();
        return Complex<T, SIN, COS, POW2, SQRT, ATAN>(tRe, tImg);
    }

    // Mulitplication
    constexpr Complex<T, SIN, COS, POW2, SQRT, ATAN> operator*(const Complex<T, SIN, COS, POW2, SQRT, ATAN> &_complex) const noexcept(std::is_nothrow_copy_assignable_v<T> &&std::is_nothrow_move_assignable_v<T> &&std::is_nothrow_constructible_v<T>)
    {
        const auto tRe = (this->getReal() * _complex.getReal()) - (this->getImaginary() * _complex.getImaginary());
        const auto tImg = (this->getReal() * _complex.getImaginary()) + (this->getImaginary() * _complex.getReal());
        return Complex<T, SIN, COS, POW2, SQRT, ATAN>(tRe, tImg);
    }

    constexpr Complex<T, SIN, COS, POW2, SQRT, ATAN> operator*(const T &_add) const noexcept(std::is_nothrow_copy_assignable_v<T> &&std::is_nothrow_move_assignable_v<T> &&std::is_nothrow_constructible_v<T>)
    {
        const auto tRe = this->getReal() * _add;
        const auto tImg = this->getImaginary() * _add;
        return Complex<T, SIN, COS, POW2, SQRT, ATAN>(tRe, tImg);
    }

    // Division
    constexpr Complex<T, SIN, COS, POW2, SQRT, ATAN> operator/(const Complex<T, SIN, COS, POW2, SQRT, ATAN> &_complex) const noexcept(std::is_nothrow_copy_assignable_v<T> &&std::is_nothrow_move_assignable_v<T> &&std::is_nothrow_constructible_v<T>)
    {
        const auto tRe = static_cast<T>((this->getReal() * _complex.getReal()) + (this->getImaginary() * _complex.getImaginary())) / (mPow2(_complex.getReal()) + mPow2(_complex.getImaginary()));
        const auto tImg = static_cast<T>(((this->getReal() * (-1)) * _complex.getImaginary()) + (_complex.getReal() * this->getImaginary())) / (mPow2(_complex.getReal()) + mPow2(_complex.getImaginary()));
        return Complex<T, SIN, COS, POW2, SQRT, ATAN>(tRe, tImg);
    }

    constexpr Complex<T, SIN, COS, POW2, SQRT, ATAN> operator/(const T &_add) const noexcept(std::is_nothrow_copy_assignable_v<T> &&std::is_nothrow_move_assignable_v<T> &&std::is_nothrow_constructible_v<T>)
    {
        const auto tRe = static_cast<T>((this->getReal() * _add)) / (mPow2(_add));
        const auto tImg = static_cast<T>((_add * this->getImaginary()) / mPow2(_add));
        return Complex<T, SIN, COS, POW2, SQRT, ATAN>(tRe, tImg);
    }

    constexpr void swap(Complex<T, SIN, COS, POW2, SQRT, ATAN> &_lh, Complex<T, SIN, COS, POW2, SQRT, ATAN> &_rh) const noexcept(std::is_nothrow_copy_assignable_v<T> &&std::is_nothrow_move_assignable_v<T> &&std::is_nothrow_constructible_v<T>)
    {
        std::swap(_lh.abs, _rh.abs);
        std::swap(_lh.img, _rh.img);
        std::swap(_lh.re, _rh.re);
        std::swap(_lh.phi, _rh.phi);
    }

    constexpr bool operator==(const Complex<T, SIN, COS, POW2, SQRT, ATAN> &_complex) const noexcept
    {
        return (getReal() == _complex.getReal() && getImaginary() == _complex.getImaginary() && getPhi() == _complex.getPhi() && getAbsolute() == _complex.getAbsolute());
    }

    constexpr bool operator!=(const Complex<T, SIN, COS, POW2, SQRT, ATAN> &_complex) const noexcept
    {
        return !(*this == _complex);
    }

    constexpr bool operator==(const T &_comp) const noexcept
    {
        return (getReal() == _comp);
    }

    constexpr bool operator!=(const T &_comp) const noexcept
    {
        return !(_comp == *this);
    }
};

// Mulitplication
template <typename T, class SIN = default_sin<T>, class COS = default_cos<T>, class POW2 = default_pow2<T>, class SQRT = default_sqrt<T>, class ATAN = default_atan<T>>
constexpr Complex<T, SIN, COS, POW2, SQRT, ATAN> operator*(const T &_add, const Complex<T, SIN, COS, POW2, SQRT, ATAN> &_complex) noexcept(std::is_nothrow_copy_assignable_v<T> &&std::is_nothrow_move_assignable_v<T> &&std::is_nothrow_constructible_v<T>)
{
    T re;
    T img;
    re = _complex.getReal() * _add;
    img = _complex.getImaginary() * _add;
    return Complex<T, SIN, COS, POW2, SQRT, ATAN>(re, img);
}

// Division
template <typename T, class SIN = default_sin<T>, class COS = default_cos<T>, class POW2 = default_pow2<T>, class SQRT = default_sqrt<T>, class ATAN = default_atan<T>>
constexpr Complex<T, SIN, COS, POW2, SQRT, ATAN> operator/(const T &_add, const Complex<T, SIN, COS, POW2, SQRT, ATAN> &_complex) noexcept(std::is_nothrow_copy_assignable_v<T> &&std::is_nothrow_move_assignable_v<T> &&std::is_nothrow_constructible_v<T>)
{
    T re;
    T img;
    re = double(_add * _complex.getReal()) / (_complex.getPowerOf2Function()(_complex.getReal()) + _complex.getPowerOf2Function()(_complex.getImaginary()));
    img = double(((_add * (-1)) * _complex.getImaginary())) / (_complex.getPowerOf2Function()(_complex.getReal()) + _complex.getPowerOf2Function()(_complex.getImaginary()));
    return Complex<T, SIN, COS, POW2, SQRT, ATAN>(re, img);
}

// Addition
template <typename T, class SIN = default_sin<T>, class COS = default_cos<T>, class POW2 = default_pow2<T>, class SQRT = default_sqrt<T>, class ATAN = default_atan<T>>
constexpr Complex<T, SIN, COS, POW2, SQRT, ATAN> operator+(const T &_add, const Complex<T, SIN, COS, POW2, SQRT, ATAN> &_complex) noexcept(std::is_nothrow_copy_assignable_v<T> &&std::is_nothrow_move_assignable_v<T> &&std::is_nothrow_constructible_v<T>)
{
    T re;
    T img;
    re = _add + _complex.getReal();
    img = _complex.getImaginary();
    return Complex<T, SIN, COS, POW2, SQRT, ATAN>(re, img);
}

// Subtraction
template <typename T, class SIN = default_sin<T>, class COS = default_cos<T>, class POW2 = default_pow2<T>, class SQRT = default_sqrt<T>, class ATAN = default_atan<T>>
constexpr Complex<T, SIN, COS, POW2, SQRT, ATAN> operator-(const T &_add, const Complex<T, SIN, COS, POW2, SQRT, ATAN> &_complex) noexcept(std::is_nothrow_copy_assignable_v<T> &&std::is_nothrow_move_assignable_v<T> &&std::is_nothrow_constructible_v<T>)
{
    T re;
    T img;
    re = _add - _complex.getReal();
    img = 0 - _complex.getImaginary();
    return Complex<T, SIN, COS, POW2, SQRT, ATAN>(re, img);
}

template <typename T, class SIN = default_sin<T>, class COS = default_cos<T>, class POW2 = default_pow2<T>, class SQRT = default_sqrt<T>, class ATAN = default_atan<T>>
constexpr bool operator==(const T &_comp, const Complex<T, SIN, COS, POW2, SQRT, ATAN> &_complex) noexcept
{
    return _complex.getReal() == _comp;
}

template <typename T, class SIN = default_sin<T>, class COS = default_cos<T>, class POW2 = default_pow2<T>, class SQRT = default_sqrt<T>, class ATAN = default_atan<T>>
constexpr bool operator!=(const T &_comp, const Complex<T, SIN, COS, POW2, SQRT, ATAN> &_complex) noexcept
{
    return !(_comp == _complex);
}

template <typename T, class SIN = default_sin<T>, class COS = default_cos<T>, class POW2 = default_pow2<T>, class SQRT = default_sqrt<T>, class ATAN = default_atan<T>>
std::ostream &operator<<(std::ostream &os, const Complex<T, SIN, COS, POW2, SQRT, ATAN> &_complex) noexcept(false)
{
    if (_complex.getImaginary() < 0)
    {
        os << _complex.getReal() << " -j " << _complex.getImaginary() * (-1);
    }
    else
    {
        os << _complex.getReal() << " +j " << _complex.getImaginary();
    }
    return os;
}
