#include "vect2.hpp"

vect2::vect2(void) : _st(0), _nd(0) {}

vect2::vect2(int st, int nd) : _st(st), _nd(nd) {}

vect2::~vect2(void) {}

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

std::ostream& operator<<(std::ostream& os, const vect2& b)
{
    os << "{" << b._st << ", " << b._nd << "}";
    return (os);
}

int vect2::operator[](size_t index) const
{
    if (index == 0)
        return (_st);
    return (_nd);
}

vect2&  vect2::operator++()
{
    _st++;
    _nd++;
    return (*this);
}

vect2   vect2::operator++(int)
{
    vect2 tmp = *this;
    _st++;
    _nd++;
    return (tmp);
}

vect2&  vect2::operator--()
{
    _st--;
    _nd--;
    return (*this);
}

vect2   vect2::operator--(int)
{
    vect2 tmp = *this;
    _st--;
    _nd--;
    return (tmp);
}

vect2&   vect2::operator+=(const vect2& other)
{
    _st += other._st;
    _nd += other._nd;
    return (*this);
}

vect2&   vect2::operator-=(const vect2& other)
{
    _st -= other._st;
    _nd -= other._nd;
    return (*this);
}

vect2&   vect2::operator*=(const int num)
{
    _st *= num;
    _nd *= num;
    return (*this);
}

vect2   vect2::operator*(int num) const
{
    return vect2(_st*num, _nd*num) ;
}

vect2   operator*(int n, const vect2 &v)
{
    return v * n;
}

vect2   vect2::operator+(const vect2& other) const
{
    return vect2(_st+other._st, _nd+other._nd) ;
}

vect2   vect2::operator-(const vect2& other) const
{
    return vect2(_st-other._st, _nd-other._nd) ;
}

vect2   vect2::operator-() const
{
    return vect2(_st*-1, _nd*-1) ;
}

int& vect2::operator[](size_t index)
{
    if (index == 0)
        return (_st);
    return (_nd);
}

bool vect2::operator==(const vect2& other) const
{
    if (other._nd == _nd && other._st == _st)
        return true;
    return false;
}

bool vect2::operator!=(const vect2& other) const
{
    if (other._nd == _nd && other._st == _st)
        return false;
    return true;
}