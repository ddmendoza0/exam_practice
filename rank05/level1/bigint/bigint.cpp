#include "bigint.hpp"

bigint::bigint(void) :_digits("0") {}

bigint::bigint(unsigned long long n) : _digits(std::to_string(n)) {} //trsnaformation to string

bigint::bigint(const bigint& other) : _digits(other._digits) {}

bigint& bigint::operator=(const bigint& other) 
{
    if (*this != other)
        _digits = other._digits;
    return (*this);
}

bigint::~bigint(void) {}

bigint  bigint::operator+(const bigint& other) const
{
    bigint tmp(*this);
    tmp += other;
    return (tmp);
}

bigint& bigint::operator+=(const bigint& other)
{
    std::string result;
    int         carry = 0;
    int         i = (int)_digits.size() - 1;
    int         j = (int)other._digits.size() - 1;

    while (i>=0 || j>=0 || carry)
    {
        int sum = carry;
        if (i>=0)
            sum += _digits[i--] - '0';
        if (j>=0)
            sum += other._digits[j--] - '0';
        result = char('0' + sum % 10) + result;
        carry = sum /10;
    }
    _digits = result;
    return (*this);
}
bigint& bigint::operator++()
{
    *this += bigint(1);
    return (*this);
}
bigint  bigint::operator++(int)
{
    bigint tmp(*this);
    ++(*this);
    return (tmp);
}

bigint  bigint::operator<<(const bigint& other) const
{
    bigint tmp(*this);
    tmp <<= other;
    return (tmp);
}

bigint& bigint::operator<<=(const bigint& other)
{
    size_t n = std::stoul(other._digits);
    _digits.append(n, '0');
    return (*this);
}

bigint  bigint::operator>>(const bigint& other) const
{
    bigint tmp(*this);
    tmp >>= other;
    return (tmp);
}

bigint& bigint::operator>>=(const bigint& other)
{
    size_t n = std::stoul(other._digits);
    if (n >= _digits.size())
        _digits = "0";
    else
        _digits.erase(_digits.size() - n, n);
    return (*this);
}

bool bigint::operator==(const bigint& other) const
{
    return ( _digits == other._digits);
}

bool bigint::operator!=(const bigint& other) const
{
    return ( _digits != other._digits);
}

bool bigint::operator<(const bigint& other) const
{
    if (_digits.size() != other._digits.size())
        return (_digits.size() < other._digits.size());
    return (_digits < other._digits);
}

bool bigint::operator<=(const bigint& other) const
{
    if (_digits.size() != other._digits.size())
        return (_digits.size() <= other._digits.size());
    return (_digits <= other._digits);
}

bool bigint::operator>(const bigint& other) const
{
    if (_digits.size() != other._digits.size())
        return (_digits.size() > other._digits.size());
    return (_digits > other._digits);
}

bool bigint::operator>=(const bigint& other) const
{
    if (_digits.size() != other._digits.size())
        return (_digits.size() >= other._digits.size());
    return (_digits >= other._digits);
}

std::ostream& operator<<(std::ostream& os, const bigint& b)
{
    os << b._digits;
    return (os);
}