#pragma once

#include <string>
#include <math.h>

template <typename T>
class Complex
{
private:
    T re = 0;
    T img = 0;
    T abs = 0;
    T phi = 0;

    void calculatePolarValues() noexcept;

    void calculateCartesianValues() noexcept;

public:
    Complex() {}
    Complex(const T &_re, const T &_img = 0, const T &_abs = 0, const T &_phi = 0);
    Complex(const Complex &_complex);

    T getReal() const noexcept;
    T getImaginary() const noexcept;
    T getAbsolute() const noexcept;
    T getPhi() const noexcept;

    void setReal(const T &_re);
    void setImaginary(const T &_img);
    void setAbsolute(const T &_abs);
    void setPhi(const T &_phi);

    std::string toString(void);
    static std::string toString(const Complex &_complex);

    Complex<T> conjugate(void);
    static Complex<T> conjugate(const Complex<T> &_complex);

    Complex<T> &operator=(const Complex<T> &_complex);

    Complex<T> &operator++();
    Complex<T> &operator--();
    Complex<T> operator++(int);
    Complex<T> operator--(int);

    Complex<T> &operator+=(const T &_add);
    Complex<T> &operator+=(const Complex<T> &_complex);
    Complex<T> &operator-=(const Complex<T> &_complex);
    Complex<T> &operator-=(const T &_add);
    Complex<T> &operator*=(const Complex<T> &_complex);
    Complex<T> &operator*=(const T &_add);
    Complex<T> &operator/=(const Complex<T> &_complex);
    Complex<T> &operator/=(const T &_add);
};

template <typename T>
void Complex<T>::calculatePolarValues() noexcept
{
    this->abs = sqrt(pow(this->re, 2) + pow(this->img, 2));
    this->phi = atan(double(this->img) / this->re);
}

template <typename T>
void Complex<T>::calculateCartesianValues() noexcept
{
    this->re = this->abs * cos(this->phi);
    this->img = this->abs * sin(this->phi);
}

template <typename T>
Complex<T>::Complex(const T &_re, const T &_img, const T &_abs, const T &_phi) : re(_re), img(_img), abs(_abs), phi(_phi)
{
    if (_re != 0 && _img != 0)
        this->calculatePolarValues();
    if (_abs != 0 && _phi != 0)
        this->calculateCartesianValues();
}

template <typename T>
Complex<T>::Complex(const Complex &_complex) : re(_complex.getReal()), img(_complex.getImaginary()), abs(_complex.getAbsolute()), phi(_complex.getPhi()) {}

template <typename T>
T Complex<T>::getReal() const noexcept { return this->re; }
template <typename T>
T Complex<T>::getImaginary() const noexcept { return this->img; }
template <typename T>
T Complex<T>::getAbsolute() const noexcept { return this->abs; }
template <typename T>
T Complex<T>::getPhi() const noexcept { return this->phi; }

template <typename T>
void Complex<T>::setReal(const T &_re)
{
    this->re = _re;
    this->calculatePolarValues();
}
template <typename T>
void Complex<T>::setImaginary(const T &_img)
{
    this->img = _img;
    this->calculatePolarValues();
}
template <typename T>
void Complex<T>::setAbsolute(const T &_abs)
{
    this->abs = _abs;
    this->calculateCartesianValues();
}
template <typename T>
void Complex<T>::setPhi(const T &_phi)
{
    this->phi = _phi;
    this->calculateCartesianValues();
}

template <typename T>
std::string Complex<T>::toString(const Complex &_complex)
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

template <typename T>
std::string Complex<T>::toString(void) { return Complex<T>::toString(*this); }

template <typename T>
Complex<T> Complex<T>::conjugate(void)
{
    Complex<T> result(this->re, this->img * (-1));
    return result;
}

template <typename T>
Complex<T> &Complex<T>::operator=(const Complex<T> &_complex)
{
    this->re = _complex.getReal();
    this->img = _complex.getImaginary();
    this->abs = _complex.getAbsolute();
    this->phi = _complex.getPhi();
    return *this;
}

template <typename T>
Complex<T> &Complex<T>::operator++()
{
    this->re++;
    this->calculatePolarValues();
    return *this;
}

template <typename T>
Complex<T> &Complex<T>::operator--()
{
    this->re--;
    this->calculatePolarValues();
    return *this;
}

template <typename T>
Complex<T> Complex<T>::operator++(int)
{
    Complex result(*this);
    ++(*this);
    return result;
}

template <typename T>
Complex<T> Complex<T>::operator--(int)
{
    Complex result(*this);
    --(*this);
    return result;
}

template <typename T>
Complex<T> &Complex<T>::operator+=(const T &_add)
{
    this->re += _add;
    this->calculatePolarValues();
    return *this;
}

template <typename T>
Complex<T> &Complex<T>::operator+=(const Complex<T> &_complex)
{
    this->re = this->re + _complex.getReal();
    this->img = this->img + _complex.getImaginary();
    this->calculatePolarValues();
    return *this;
}

template <typename T>
Complex<T> &Complex<T>::operator-=(const Complex<T> &_complex)
{
    this->re = this->re - _complex.getReal();
    this->img = this->img - _complex.getImaginary();
    this->calculatePolarValues();
    return *this;
}

template <typename T>
Complex<T> &Complex<T>::operator-=(const T &_add)
{
    this->re -= _add;
    this->calculatePolarValues();
    return *this;
}

template <typename T>
Complex<T> &Complex<T>::operator*=(const Complex<T> &_complex)
{
    this->re = (this->getReal() * _complex.getReal()) - (this->getImaginary() * _complex.getImaginary());
    this->img = (this->getReal() * _complex.getImaginary()) + (this->getImaginary() * _complex.getReal());
    this->calculatePolarValues();
    return *this;
}

template <typename T>
Complex<T> &Complex<T>::operator*=(const T &_add)
{
    this->re = this->re * _add;
    this->img = this->img * _add;
    this->calculatePolarValues();
    return *this;
}

template <typename T>
Complex<T> &Complex<T>::operator/=(const Complex<T> &_complex)
{
    this->re = double((this->getReal() * _complex.getReal()) + (this->getImaginary() * _complex.getImaginary())) / (pow(_complex.getReal(), 2) + pow(_complex.getImaginary(), 2));
    this->img = double(((this->getReal() * (-1)) * _complex.getImaginary()) + (_complex.getReal() * this->getImaginary())) / (pow(_complex.getReal(), 2) + pow(_complex.getImaginary(), 2));
    this->calculatePolarValues();
    return *this;
}

template <typename T>
Complex<T> &Complex<T>::operator/=(const T &_add)
{
    this->re = double(this->re * _add) / pow(_add, 2);
    this->img = double(_add * this->img) / pow(_add, 2);
    this->calculatePolarValues();
    return *this;
}

// Mulitplication
template <class T>
Complex<T> operator*(const Complex<T> &_complex1, const Complex<T> &_complex2)
{
    T re;
    T img;
    re = (_complex1.getReal() * _complex2.getReal()) - (_complex1.getImaginary() * _complex2.getImaginary());
    img = (_complex1.getReal() * _complex2.getImaginary()) + (_complex1.getImaginary() * _complex2.getReal());
    return Complex<T>(re, img);
}

template <class T>
Complex<T> operator*(const T _add, const Complex<T> &_complex)
{
    T re;
    T img;
    re = _complex.getReal() * _add;
    img = _complex.getImaginary() * _add;
    return Complex<T>(re, img);
}

template <class T>
Complex<T> operator*(const Complex<T> &_complex, const T _add)
{
    T re;
    T img;
    re = _complex.getReal() * _add;
    img = _complex.getImaginary() * _add;
    return Complex<T>(re, img);
}

// Division
template <class T>
Complex<T> operator/(const Complex<T> &_complex1, const Complex<T> &_complex2)
{
    T re;
    T img;
    re = double((_complex1.getReal() * _complex2.getReal()) + (_complex1.getImaginary() * _complex2.getImaginary())) / (pow(_complex2.getReal(), 2) + pow(_complex2.getImaginary(), 2));
    img = double(((_complex1.getReal() * (-1)) * _complex2.getImaginary()) + (_complex2.getReal() * _complex1.getImaginary())) / (pow(_complex2.getReal(), 2) + pow(_complex2.getImaginary(), 2));
    return Complex<T>(re, img);
}

template <class T>
Complex<T> operator/(const T _add, const Complex<T> &_complex)
{
    T re;
    T img;
    re = double(_add * _complex.getReal()) / (pow(_complex.getReal(), 2) + pow(_complex.getImaginary(), 2));
    img = double(((_add * (-1)) * _complex.getImaginary())) / (pow(_complex.getReal(), 2) + pow(_complex.getImaginary(), 2));
    return Complex<T>(re, img);
}

template <class T>
Complex<T> operator/(const Complex<T> &_complex, const T _add)
{
    T re;
    T img;
    re = double((_complex.getReal() * _add)) / (pow(_add, 2));
    img = double(((_add * _complex.getImaginary())) / pow(_add, 2));
    return Complex<T>(re, img);
}

// Addition
template <class T>
Complex<T> operator+(const Complex<T> &_complex1, const Complex<T> &_complex2)
{
    T re;
    T img;
    re = _complex1.getReal() + _complex2.getReal();
    img = _complex1.getImaginary() + _complex2.getImaginary();
    return Complex<T>(re, img);
}

template <class T>
Complex<T> operator+(const T _add, const Complex<T> &_complex)
{
    T re;
    T img;
    re = _add + _complex.getReal();
    img = _complex.getImaginary();
    return Complex<T>(re, img);
}

template <class T>
Complex<T> operator+(const Complex<T> &_complex, const T _add)
{
    T re;
    T img;
    re = _add + _complex.getReal();
    img = _complex.getImaginary();
    return Complex<T>(re, img);
}

// Subtraction
template <class T>
Complex<T> operator-(const Complex<T> &_complex1, const Complex<T> &_complex2)
{
    T re;
    T img;
    re = _complex1.getReal() - _complex2.getReal();
    img = _complex1.getImaginary() - _complex2.getImaginary();
    return Complex<T>(re, img);
}

template <class T>
Complex<T> operator-(const T _add, const Complex<T> &_complex)
{
    T re;
    T img;
    re = _add - _complex.getReal();
    img = 0 - _complex.getImaginary();
    return Complex<T>(re, img);
}

template <class T>
Complex<T> operator-(const Complex<T> &_complex, const T _add)
{
    T re;
    T img;
    re = _complex.getReal() - _add;
    img = _complex.getImaginary() - 0;
    return Complex<T>(re, img);
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

template <class T>
bool operator==(const Complex<T> &_complex1, const Complex<T> &_complex2)
{
    if (_complex1.getReal() == _complex2.getReal() && _complex1.getImaginary() == _complex2.getImaginary() && _complex1.getPhi() == _complex2.getPhi() && _complex1.getAbsolute() == _complex2.getAbsolute())
    {
        return true;
    }
    return false;
}

template <class T>
bool operator!=(const Complex<T> &_complex1, const Complex<T> &_complex2)
{
    return !(_complex1 == _complex2);
}

template <class T>
bool operator==(const T &_comp, const Complex<T> &_complex2)
{
    if (_complex2.getImaginary() != 0 || _complex2.getPhi() != 0)
        return false;
    else if (_complex2.getReal() == _comp)
        return true;
    else
        return false;
}

template <class T>
bool operator!=(const T &_comp, const Complex<T> &_complex2)
{
    return !(_comp == _complex2);
}

template <class T>
bool operator==(const Complex<T> &_complex1, const T &_comp)
{
    if (_complex1.getImaginary() != 0 || _complex1.getPhi() != 0)
        return false;
    else if (_complex1.getReal() == _comp)
        return true;
    else
        return false;
}

template <class T>
bool operator!=(const Complex<T> &_complex1, const T &_comp)
{
    return !(_complex1 == _comp);
}

template <class T>
bool operator==(const int &_comp, const Complex<T> &_complex2)
{
    if (_complex2.getImaginary() != 0 || _complex2.getPhi() != 0)
        return false;
    else if (_complex2.getReal() == _comp)
        return true;
    else
        return false;
}

template <class T>
bool operator!=(const int &_comp, const Complex<T> &_complex2)
{
    return !(_comp == _complex2);
}

template <class T>
bool operator==(const Complex<T> &_complex1, const int &_comp)
{
    if (_complex1.getImaginary() != 0 || _complex1.getPhi() != 0)
        return false;
    else if (_complex1.getReal() == _comp)
        return true;
    else
        return false;
}

template <class T>
bool operator!=(const Complex<T> &_complex1, const int &_comp)
{
    return !(_complex1 == _comp);
}