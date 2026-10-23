#pragma once

#include <iostream>

class vect2
{
    private:
        int     _st;
        int     _nd;

    public:
        vect2(void);
        ~vect2(void);
        vect2(int st, int nd);
        vect2(const vect2& other);
        vect2& operator=(const vect2& other);
        
        friend std::ostream& operator<<(std::ostream& os, const vect2& b);
        int operator[](size_t index) const;

        vect2&  operator++();
        vect2&  operator--();
        vect2   operator++(int);
        vect2   operator--(int);

        vect2&  operator+=(const vect2& other);
        vect2&  operator-=(const vect2& other);
        vect2&  operator*=(const int num);

        vect2   operator*(int num) const;
        friend vect2 operator*(int n, const vect2 &v);
        vect2   operator+(const vect2& other) const;
        vect2   operator-(const vect2& other) const;

        vect2 operator-() const;
        int& operator[](size_t index);

        bool operator==(const vect2& other) const;
        bool operator!=(const vect2& other) const; 


};


