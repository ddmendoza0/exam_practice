#include "bigint.hpp"

bigint::bigint(void) :_digits(0) {}

bigint::bigint(unsigned long long n) : _digits(std::to_string(n)) {} //trsnaformation to string

bigint::bigint(const bigint& other) : _digits(other._digits) {}

bigint& bigint::operator=(const bigint other) 
{
    if (*this != other)
        _digits = other._digits;
    return (*this);
}

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
    int         i = _digits.size() - 1;
    int         j = other._digits.size() - 1;

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
// bigint& operator++();
// bigint  operator++(int);

// bigint  operator<<(const bigint& other) const;
// bigint& operator<<=(const bigint& other);
// bigint  operator>>(const bigint& other) const;
// bigint& operator>>=(const bigint& other);

// bool operator==(const bigint& other) const;
// bool operator!=(const bigint& other) const;
// bool operator< (const bigint& other) const;
// bool operator<=(const bigint& other) const;
// bool operator> (const bigint& other) const;
// bool operator>=(const bigint& other) const;

// friend std::ostream& operator<<(std::ostream& os, const bigint& b);