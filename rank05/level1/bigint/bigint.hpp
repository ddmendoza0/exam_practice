#pragma once

#include <string>
#include <iostream>

class   bigint
{
    private:
        std::string _digits; //here we will store the big int

    public:
        bigint(void);
        bigint(unsigned long long n);
        bigint(const bigint& other);
        bigint& operator=(const bigint other);
        ~bigint(void);

        bigint  operator+(const bigint& other) const; //addition
        bigint& operator+=(const bigint& other);
        bigint& operator++();
        bigint  operator++(int);

        bigint  operator<<(const bigint& other) const;
        bigint& operator<<=(const bigint& other);
        bigint  operator>>(const bigint& other) const;
        bigint& operator>>=(const bigint& other);

        bool operator==(const bigint& other) const;
        bool operator!=(const bigint& other) const;
        bool operator< (const bigint& other) const;
        bool operator<=(const bigint& other) const;
        bool operator> (const bigint& other) const;
        bool operator>=(const bigint& other) const;

        friend std::ostream& operator<<(std::ostream& os, const bigint& b);
};