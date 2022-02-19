#pragma once

#include <string>
#include <cmath>

template <typename T,
          typename = std::enable_if_t<std::is_nothrow_constructible_v<T> && std::is_nothrow_copy_constructible_v<T> && std::is_nothrow_move_constructible_v<T> && std::is_nothrow_copy_assignable_v<T> && std::is_nothrow_move_assignable_v<T> && std::is_nothrow_swappable_v<T>>>
class Complex
{
private:
    T re = 0;
    T img = 0;
    T abs = 0;
    T phi = 0;

    void calculatePolarValues() noexcept
    {
        this->abs = std::sqrt(std::pow(this->re, 2) + std::pow(this->img, 2));
        this->phi = std::atan(static_cast<double>(this->img) / this->re);
    }
    void calculateCartesianValues() noexcept
    {
        this->re = this->abs * std::cos(this->phi);
        this->img = this->abs * std::sin(this->phi);
    }

public:
    constexpr Complex() = default;
    explicit constexpr Complex(const T &_re, const T &_img = 0, const T &_abs = 0, const T &_phi = 0) : re(_re), img(_img), abs(_abs), phi(_phi)
    {
        if (_re != 0 || _img != 0)
            this->calculatePolarValues();
        else if (_abs != 0 || _phi != 0)
            this->calculateCartesianValues();
    }

    constexpr const T &getReal() const noexcept { return this->re; }
    constexpr const T &getImaginary() const noexcept { return this->img; }
    constexpr const T &getAbsolute() const noexcept { return this->abs; }
    constexpr const T &getPhi() const noexcept { return this->phi; }

    Complex &setReal(const T &_re) noexcept
    {
        this->re = _re;
        this->calculatePolarValues();
        return *this;
    }
    Complex &setImaginary(const T &_img) noexcept
    {
        this->img = _img;
        this->calculatePolarValues();
        return *this;
    }
    Complex &setAbsolute(const T &_abs) noexcept
    {
        this->abs = _abs;
        this->calculateCartesianValues();
        return *this;
    }
    Complex &setPhi(const T &_phi) noexcept
    {
        this->phi = _phi;
        this->calculateCartesianValues();
        return *this;
    }

    std::string toString(void) { return Complex<T>::toString(*this); }
    static std::string toString(const Complex &_complex)
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

    Complex<T> &conjugate(void)
    {
        this->img *= (-1);
        this->calculatePolarValues();
        return *this;
    }
    static Complex<T> conjugate(const Complex<T> &_complex)
    {
        _complex.img *= (-1);
        _complex.calculatePolarValues();
        return _complex;
    }

    Complex<T> &operator++()
    {
        this->re++;
        this->calculatePolarValues();
        return *this;
    }
    Complex<T> &operator--()
    {
        this->re--;
        this->calculatePolarValues();
        return *this;
    }
    Complex<T> operator++(int)
    {
        Complex result(*this);
        ++(*this);
        return result;
    }
    Complex<T> operator--(int)
    {
        Complex result(*this);
        --(*this);
        return result;
    }

    Complex<T> &operator+=(const T &_add)
    {
        this->re += _add;
        this->calculatePolarValues();
        return *this;
    }
    Complex<T> &operator+=(const Complex<T> &_complex)
    {
        this->re = this->re + _complex.getReal();
        this->img = this->img + _complex.getImaginary();
        this->calculatePolarValues();
        return *this;
    }
    Complex<T> &operator-=(const Complex<T> &_complex)
    {
        this->re = this->re - _complex.getReal();
        this->img = this->img - _complex.getImaginary();
        this->calculatePolarValues();
        return *this;
    }

    Complex<T> &operator-=(const T &_add)
    {
        this->re -= _add;
        this->calculatePolarValues();
        return *this;
    }
    Complex<T> &operator*=(const Complex<T> &_complex)
    {
        const auto re = (this->getReal() * _complex.getReal()) - (this->getImaginary() * _complex.getImaginary());
        const auto img = (this->getReal() * _complex.getImaginary()) + (this->getImaginary() * _complex.getReal());
        this->re = re;
        this->img = img;
        this->calculatePolarValues();
        return *this;
    }
    Complex<T> &operator*=(const T &_add)
    {
        this->re = this->re * _add;
        this->img = this->img * _add;
        this->calculatePolarValues();
        return *this;
    }
    Complex<T> &operator/=(const Complex<T> &_complex)
    {
        const auto re = static_cast<T>((this->getReal() * _complex.getReal()) + (this->getImaginary() * _complex.getImaginary())) / (pow(_complex.getReal(), 2) + pow(_complex.getImaginary(), 2));
        const auto img = static_cast<T>(((this->getReal() * (-1)) * _complex.getImaginary()) + (_complex.getReal() * this->getImaginary())) / (pow(_complex.getReal(), 2) + pow(_complex.getImaginary(), 2));
        this->re = re;
        this->img = img;
        this->calculatePolarValues();
        return *this;
    }
    Complex<T> &operator/=(const T &_add)
    {
        const auto re = static_cast<T>((this->getReal() * _add)) / (pow(_add, 2));
        const auto img = static_cast<T>(((_add * this->getImaginary())) / pow(_add, 2));
        this->re = re;
        this->img = img;
        this->calculatePolarValues();
        return *this;
    }

    // Addition
    Complex<T> operator+(const Complex<T> &_complex) const
    {
        const auto re = this->getReal() + _complex.getReal();
        const auto img = this->getImaginary() + _complex.getImaginary();
        return Complex<T>(re, img);
    }

    Complex<T> operator+(const T &_add) const
    {
        const auto re = _add + this->getReal();
        const auto img = this->getImaginary();
        return Complex<T>(re, img);
    }

    // Subtraction
    Complex<T> operator-(const Complex<T> &_complex) const
    {
        const auto re = this->getReal() - _complex.getReal();
        const auto img = this->getImaginary() - _complex.getImaginary();
        return Complex<T>(re, img);
    }

    Complex<T> operator-(const T &_add) const
    {
        const auto re = this->getReal() - _add;
        const auto img = this->getImaginary();
        return Complex<T>(re, img);
    }

    // Mulitplication
    Complex<T> operator*(const Complex<T> &_complex) const
    {
        const auto re = (this->getReal() * _complex.getReal()) - (this->getImaginary() * _complex.getImaginary());
        const auto img = (this->getReal() * _complex.getImaginary()) + (this->getImaginary() * _complex.getReal());
        return Complex<T>(re, img);
    }

    Complex<T> operator*(const T &_add) const
    {
        const auto re = this->getReal() * _add;
        const auto img = this->getImaginary() * _add;
        return Complex<T>(re, img);
    }

    // Division
    Complex<T> operator/(const Complex<T> &_complex) const
    {
        const auto re = static_cast<T>((this->getReal() * _complex.getReal()) + (this->getImaginary() * _complex.getImaginary())) / (pow(_complex.getReal(), 2) + pow(_complex.getImaginary(), 2));
        const auto img = static_cast<T>(((this->getReal() * (-1)) * _complex.getImaginary()) + (_complex.getReal() * this->getImaginary())) / (pow(_complex.getReal(), 2) + pow(_complex.getImaginary(), 2));
        return Complex<T>(re, img);
    }

    Complex<T> operator/(const T &_add) const
    {
        const auto re = static_cast<T>((this->getReal() * _add)) / (pow(_add, 2));
        const auto img = static_cast<T>(((_add * this->getImaginary())) / pow(_add, 2));
        return Complex<T>(re, img);
    }

    void swap(Complex<T> &_lh, Complex<T> &_rh)
    {
        using std::swap;

        swap(_lh.abs, _rh.abs);
        swap(_lh.img, _rh.img);
        swap(_lh.re, _rh.re);
        swap(_lh.phi, _rh.phi);
    }

    bool operator==(const Complex<T> &_complex) const
    {
        return (getReal() == _complex.getReal() && getImaginary() == _complex.getImaginary() && getPhi() == _complex.getPhi() && getAbsolute() == _complex.getAbsolute());
    }

    bool operator!=(const Complex<T> &_complex) const
    {
        return !(*this == _complex);
    }

    bool operator==(const T &_comp) const
    {
        return (getReal() == _comp);
    }

    bool operator!=(const T &_comp) const
    {
        return !(_comp == *this);
    }
};

// Mulitplication
template <typename T>
Complex<T> operator*(const T &_add, const Complex<T> &_complex)
{
    T re;
    T img;
    re = _complex.getReal() * _add;
    img = _complex.getImaginary() * _add;
    return Complex<T>(re, img);
}

// Division
template <typename T>
Complex<T> operator/(const T &_add, const Complex<T> &_complex)
{
    T re;
    T img;
    re = double(_add * _complex.getReal()) / (pow(_complex.getReal(), 2) + pow(_complex.getImaginary(), 2));
    img = double(((_add * (-1)) * _complex.getImaginary())) / (pow(_complex.getReal(), 2) + pow(_complex.getImaginary(), 2));
    return Complex<T>(re, img);
}

// Addition
template <typename T>
Complex<T> operator+(const T &_add, const Complex<T> &_complex)
{
    T re;
    T img;
    re = _add + _complex.getReal();
    img = _complex.getImaginary();
    return Complex<T>(re, img);
}

// Subtraction
template <typename T>
Complex<T> operator-(const T &_add, const Complex<T> &_complex)
{
    T re;
    T img;
    re = _add - _complex.getReal();
    img = 0 - _complex.getImaginary();
    return Complex<T>(re, img);
}

template <typename T>
bool operator==(const T &_comp, const Complex<T> &_complex)
{
    return _complex.getReal() == _comp;
}

template <typename T>
bool operator!=(const T &_comp, const Complex<T> &_complex)
{
    return !(_comp == _complex);
}

template <typename T>
std::ostream &operator<<(std::ostream &os, const Complex<T> &_complex)
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
