#ifndef FRACTION_H
#define FRACTION_H

#include<string>
class Fraction{
public:
    Fraction();
    Fraction(long long numerator,long long denominator);
    Fraction(const Fraction& other);
    Fraction& operator=(const Fraction& other); // return a referrence

    std::string ToString() const;
    static Fraction fromDecimal(const std::string text);
    explicit operator double() const;// avoid 隐式转换
    
    long long numerator(){return num;}
    long long denominator(){return den;}

    // protect the numerator and denominator from being edited from outside
    private:
    long long num;
    long long den;

};

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

std::ostream& operator<<(const std::ostream os, const Fraction& a);
std::istream& operator>>(const std::istream is, Fraction& a);
#endif