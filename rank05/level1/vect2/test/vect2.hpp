#pragma once

#include <iostream>

class vect2
{
    private:
        int _st;
        int _nd;

    public:
        vect2();
        ~vect2();
        vect2(int st, int nd);
        vect2(const vect2& other);
        vect2& operator=(const vect2& other);

        friend std::ostream& operator<<(std::ostream& os, const vect2& v);
        int     operator[](int index) const;
        int&    operator[](int index);

        vect2&  operator++();
        vect2   operator++(int);
        vect2&  operator--();
        vect2   operator--(int);

        vect2&   operator+=(const vect2& other);
        vect2&   operator-=(const vect2& other);
        vect2   operator+(const vect2& other) const;

        vect2   operator*(int n) const;
        friend  vect2 operator*(int n, const vect2& v);
        
        vect2&  operator*=(int n);
        vect2   operator-(const vect2& other) const;
        vect2   operator-() const;

        bool    operator==(const vect2& other) const;
        bool    operator!=(const vect2& other) const;
};