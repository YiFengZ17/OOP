#ifndef FRACTION_H
#define FRACTION_H

#include<string>
#include<iostream>

class Fraction{
public:
    Fraction(); // default ctor
    Fraction(long long numerator,long long denominator); // normalization ctor
    Fraction(const Fraction& other); //default copy ctor
    Fraction& operator=(const Fraction& other); // '=' overloading must be a member function

    std::string ToString() const;
    static Fraction fromDecimal(const std::string text);
    explicit operator double() const;// T操作符，使用 explicit 避免隐式转换
    
    long long numerator() const{return nume;}
    long long denominator() const{return deno;}

    // protect the numerator and denominator from being edited from outside
    private:
    long long nume;
    long long deno;

};

// overload all the needed operator
Fraction operator+(const Fraction& a, const Fraction& b);
Fraction operator-(const Fraction& a, const Fraction& b);
Fraction operator*(const Fraction& a, const Fraction& b);
Fraction operator/(const Fraction& a, const Fraction& b);
bool operator>(const Fraction& a, const Fraction& b);
bool operator>=(const Fraction& a, const Fraction& b);
bool operator<(const Fraction& a, const Fraction& b);
bool operator<=(const Fraction& a, const Fraction& b);
bool operator==(const Fraction& a, const Fraction& b);
bool operator!=(const Fraction& a, const Fraction& b);

std::ostream& operator<<(std::ostream& os, Fraction& a);
std::istream& operator>>(std::istream& is, Fraction& a);
#endif