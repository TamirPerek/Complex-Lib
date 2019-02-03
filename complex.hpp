#ifndef COMPLEX_H
#define COMPLEX_H

#include <string>
#include <math.h>

template <class T>
class complex
{
  private:
    T re;
    T img;
    T abs;
    T phi;

    void calculatePolarValues()
    {
        this->abs = sqrt(pow(this->re, 2) + pow(this->img, 2));
        this->phi = atan(double(this->img) / this->re);
    }

    void calculateCartesianValues()
    {
        this->re = this->abs * cos(this->phi);
        this->img = this->abs * sin(this->phi);
    }

  public:
    complex(complex *_complex) : re(_complex->getReal()), img(_complex->getImaginary()), abs(_complex->getAbsolute()), phi(_complex->getPhi()) {}
    complex(T _re = 0, T _img = 0, T _abs = 0, T _phi = 0) : re(_re), img(_img), abs(_abs), phi(_phi)
    {
        if (_re != 0 && _img != 0)
            this->calculatePolarValues();
        if (_abs != 0 && _phi != 0)
            this->calculateCartesianValues();
    }

    T getReal() const { return this->re; }
    T getImaginary() const { return this->img; }
    T getAbsolute() const { return this->abs; }
    T getPhi() const { return this->phi; }

    void setReal(T _re)
    {
        this->re = _re;
        this->calculatePolarValues();
    }
    void setImaginary(T _img)
    {
        this->img = _img;
        this->calculatePolarValues();
    }
    void setAbsolute(T _abs)
    {
        this->abs = _abs;
        this->calculateCartesianValues();
    }
    void setPhi(T _phi)
    {
        this->phi = _phi;
        this->calculateCartesianValues();
    }

    std::string toString(void)
    {
        if (this->img < 0)
        {
            return "Cartesian: " + std::to_string(this->re) + " -j " + std::to_string(this->img * (-1)) + "\nPolar: " + std::to_string(this->abs) + "(cos(" + std::to_string(this->phi) + "°) +j sin(" + std::to_string(this->phi) + "°))";
        }
        else
        {
            return "Cartesian: " + std::to_string(this->re) + " +j " + std::to_string(this->img) + "\nPolar: " + std::to_string(this->abs) + "(cos(" + std::to_string(this->phi) + "°) +j sin(" + std::to_string(this->phi) + "°))";
        }
    }

    std::string toString(complex *_complex)
    {
        if (this->img < 0)
        {
            return "Cartesian: " + std::to_string(_complex->getReal()) + " -j " + std::to_string(_complex->getImaginary() * (-1)) + "\nPolar: " + std::to_string(_complex->getAbsolute()) + "(cos(" + std::to_string(_complex->getPhi()) + "°) +j sin(" + std::to_string(_complex->getPhi()) + "°))";
        }
        else
        {
            return "Cartesian: " + std::to_string(_complex->getReal()) + " +j " + std::to_string(_complex->getImaginary()) + "\nPolar: " + std::to_string(_complex->getAbsolute()) + "(cos(" + std::to_string(_complex->getPhi()) + "°) +j sin(" + std::to_string(_complex->getPhi()) + "°))";
        }
    }

    std::string toString(complex _complex)
    {
        if (this->img < 0)
        {
            return "Cartesian: " + std::to_string(_complex.getReal()) + " -j " + std::to_string(_complex.getImaginary() * (-1)) + "\nPolar: " + std::to_string(_complex.getAbsolute()) + "(cos(" + std::to_string(_complex.getPhi()) + "°) +j sin(" + std::to_string(_complex.getPhi()) + "°))";
        }
        else
        {
            return "Cartesian: " + std::to_string(_complex.getReal()) + " +j " + std::to_string(_complex.getImaginary()) + "\nPolar: " + std::to_string(_complex.getAbsolute()) + "(cos(" + std::to_string(_complex.getPhi()) + "°) +j sin(" + std::to_string(_complex.getPhi()) + "°))";
        }
    }

    complex<T> conjugate(void)
    {
        complex<T> result(this->re, this->img * (-1));
        return result;
    }

    complex &operator=(complex *_complex)
    {
        this->re = _complex->getReal();
        this->img = _complex->getImaginary();
        this->abs = _complex->getAbsolute();
        this->phi = _complex->getPhi();
        return *this;
    }

    complex &operator++()
    {
        this->re++;
        this->calculatePolarValues();
        return *this;
    }

    complex &operator--()
    {
        this->re--;
        this->calculatePolarValues();
        return *this;
    }

    complex operator++(int)
    {
        complex result(*this);
        ++(*this);
        return result;
    }

    complex operator--(int)
    {
        complex result(*this);
        --(*this);
        return result;
    }

    complex &operator+=(complex *_complex)
    {
        this->re = this->re + _complex->getReal();
        this->img = this->img + _complex->getImaginary();
        this->calculatePolarValues();
        return *this;
    }

    complex &operator+=(const T _add)
    {
        this->re += _add;
        this->calculatePolarValues();
        return *this;
    }

    complex &operator+=(complex _complex)
    {
        this->re = this->re + _complex.getReal();
        this->img = this->img + _complex.getImaginary();
        this->calculatePolarValues();
        return *this;
    }

    complex &operator-=(complex *_complex)
    {
        this->re = this->re - _complex->getReal();
        this->img = this->img - _complex->getImaginary();
        this->calculatePolarValues();
        return *this;
    }

    complex &operator-=(complex _complex)
    {
        this->re = this->re - _complex.getReal();
        this->img = this->img - _complex.getImaginary();
        this->calculatePolarValues();
        return *this;
    }

    complex &operator-=(const T _add)
    {
        this->re -= _add;
        this->calculatePolarValues();
        return *this;
    }

    complex &operator*=(complex *_complex)
    {
        complex<T> temp(this);
        this->re = (temp.getReal() * _complex->getReal()) - (temp.getImaginary() * _complex->getImaginary());
        this->img = (temp.getReal() * _complex->getImaginary()) + (temp.getImaginary() * _complex->getReal());
        this->calculatePolarValues();
        return *this;
    }

    complex &operator*=(complex _complex)
    {
        complex<T> temp(this);
        this->re = (temp.getReal() * _complex.getReal()) - (temp.getImaginary() * _complex.getImaginary());
        this->img = (temp.getReal() * _complex.getImaginary()) + (temp.getImaginary() * _complex.getReal());
        this->calculatePolarValues();
        return *this;
    }

    complex &operator*=(const T _add)
    {
        this->re = this->re * _add;
        this->img = this->img * _add;
        this->calculatePolarValues();
        return *this;
    }

    complex &operator/=(complex *_complex)
    {
        complex<T> temp(this);
        this->re = double((temp.getReal() * _complex->getReal()) + (temp.getImaginary() * _complex->getImaginary())) / (pow(_complex->getReal(), 2) + pow(_complex->getImaginary(), 2));
        this->img = double(((temp.getReal() * (-1)) * _complex->getImaginary()) + (_complex->getReal() * temp.getImaginary())) / (pow(_complex->getReal(), 2) + pow(_complex->getImaginary(), 2));
        this->calculatePolarValues();
        return *this;
    }

    complex &operator/=(complex _complex)
    {
        complex<T> temp(this);
        this->re = double((temp.getReal() * _complex.getReal()) + (temp.getImaginary() * _complex.getImaginary())) / (pow(_complex.getReal(), 2) + pow(_complex.getImaginary(), 2));
        this->img = double(((temp.getReal() * (-1)) * _complex.getImaginary()) + (_complex.getReal() * temp.getImaginary())) / (pow(_complex.getReal(), 2) + pow(_complex.getImaginary(), 2));
        this->calculatePolarValues();
        return *this;
    }

    complex &operator/=(const T _add)
    {
        this->re = double(this->re * _add) / pow(_add, 2);
        this->img = double(_add * this->img) / pow(_add, 2);
        this->calculatePolarValues();
        return *this;
    }
};

// Mulitplication
template <class T>
complex<T> operator*(const complex<T> &_complex1, const complex<T> &_complex2)
{
    T re;
    T img;
    re = (_complex1.getReal() * _complex2.getReal()) - (_complex1.getImaginary() * _complex2.getImaginary());
    img = (_complex1.getReal() * _complex2.getImaginary()) + (_complex1.getImaginary() * _complex2.getReal());
    return complex<T>(re, img);
}

template <class T>
complex<T> operator*(const T _add, const complex<T> &_complex)
{
    T re;
    T img;
    re = _complex.getReal() * _add;
    img = _complex.getImaginary() * _add;
    return complex<T>(re, img);
}

template <class T>
complex<T> operator*(const complex<T> &_complex, const T _add)
{
    T re;
    T img;
    re = _complex.getReal() * _add;
    img = _complex.getImaginary() * _add;
    return complex<T>(re, img);
}

// Division
template <class T>
complex<T> operator/(const complex<T> &_complex1, const complex<T> &_complex2)
{
    T re;
    T img;
    re = double((_complex1.getReal() * _complex2.getReal()) + (_complex1.getImaginary() * _complex2.getImaginary())) / (pow(_complex2.getReal(), 2) + pow(_complex2.getImaginary(), 2));
    img = double(((_complex1.getReal() * (-1)) * _complex2.getImaginary()) + (_complex2.getReal() * _complex1.getImaginary())) / (pow(_complex2.getReal(), 2) + pow(_complex2.getImaginary(), 2));
    return complex<T>(re, img);
}

template <class T>
complex<T> operator/(const T _add, const complex<T> &_complex)
{
    T re;
    T img;
    re = double(_add * _complex.getReal()) / (pow(_complex.getReal(), 2) + pow(_complex.getImaginary(), 2));
    img = double(((_add * (-1)) * _complex.getImaginary())) / (pow(_complex.getReal(), 2) + pow(_complex.getImaginary(), 2));
    return complex<T>(re, img);
}

template <class T>
complex<T> operator/(const complex<T> &_complex, const T _add)
{
    T re;
    T img;
    re = double((_complex.getReal() * _add)) / (pow(_add, 2));
    img = double(((_add * _complex.getImaginary())) / pow(_add, 2));
    return complex<T>(re, img);
}

// Addition
template <class T>
complex<T> operator+(const complex<T> &_complex1, const complex<T> &_complex2)
{
    T re;
    T img;
    re = _complex1.getReal() + _complex2.getReal();
    img = _complex1.getImaginary() + _complex2.getImaginary();
    return complex<T>(re, img);
}

template <class T>
complex<T> operator+(const T _add, const complex<T> &_complex)
{
    T re;
    T img;
    re = _add + _complex.getReal();
    img = _complex.getImaginary();
    return complex<T>(re, img);
}

template <class T>
complex<T> operator+(const complex<T> &_complex, const T _add)
{
    T re;
    T img;
    re = _add + _complex.getReal();
    img = _complex.getImaginary();
    return complex<T>(re, img);
}

// Subtraction
template <class T>
complex<T> operator-(const complex<T> &_complex1, const complex<T> &_complex2)
{
    T re;
    T img;
    re = _complex1.getReal() - _complex2.getReal();
    img = _complex1.getImaginary() - _complex2.getImaginary();
    return complex<T>(re, img);
}

template <class T>
complex<T> operator-(const T _add, const complex<T> &_complex)
{
    T re;
    T img;
    re = _add - _complex.getReal();
    img = 0 - _complex.getImaginary();
    return complex<T>(re, img);
}

template <class T>
complex<T> operator-(const complex<T> &_complex, const T _add)
{
    T re;
    T img;
    re = _complex.getReal() - _add;
    img = _complex.getImaginary() - 0;
    return complex<T>(re, img);
}

#endif // COMPLEX_H