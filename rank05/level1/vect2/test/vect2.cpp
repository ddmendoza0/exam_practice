#include "vect2.hpp"

vect2::vect2(void) : _st(0), _nd(0) {}

vect2::~vect2(void) {}

vect2::vect2(int st, int nd) : _st(st), _nd(nd) {}

vect2::vect2(const vect2& other) : _st(other._st), _nd(other._nd) {}

vect2& vect2::operator=(const vect2& other)
{
    if (this != &other)
    {
        _st = other._st;
        _nd = other._nd;
    }
    return (*this);
}

std::ostream& operator<<(std::ostream& os, const vect2& v)
{
    os << "{" << v._st << ", " << v._nd << "}";
    return os;
}

int vect2::operator[](int index) const
{
    if (index == 1)
        return _st;
    return _nd;
}

int& vect2::operator[](int index)
{
    if (index == 1)
        return _st;
    return _nd;
}

vect2& vect2::operator++()
{
    _st++;
    _nd++;
    return (*this);
}

vect2   vect2::operator++(int)
{
    vect2 vectn = *this;
    _st++;
    _nd++;
    return vectn;
}

vect2& vect2::operator--()
{
    _st--;
    _nd--;
    return (*this);
}

vect2   vect2::operator--(int)
{
    vect2 vectn = *this;
    _st--;
    _nd--;
    return vectn;
}











