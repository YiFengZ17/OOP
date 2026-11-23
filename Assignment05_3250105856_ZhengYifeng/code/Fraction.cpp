#include"Fraction.h"
#include<stdexcept>
#include<algorithm>


long long gcd(long long a, long long b){
    if(a < 0)a = -a;
    if(a == 0)return b;
    if(a < b){
        long long tmp = a;a=b;b=tmp;
    }
    long long r = a % b;
    while(r != 0){
        a = b;
        b = r;
        r = a % b;
    }
    return b;
}


// default constructor
Fraction::Fraction(): nume(0) ,deno(1){} 

// normalization function
Fraction::Fraction(long long numerator,long long denominator): nume(numerator),deno(denominator){
        if(deno == 0){
        throw std::invalid_argument("denominator cannot be zero");
    }

    // let nume take the negative operator
    if( deno < 0){
        nume = -nume;
        deno = -deno;
    }
    long long Gcd = gcd(nume,deno);
    if(Gcd != 1){
        nume = nume / Gcd;
        deno = deno / Gcd;
    }
}

// default copy ctor
Fraction::Fraction(const Fraction& other): nume(other.nume), deno(other.deno) {}

// '=' overloading must be member function to avoid compiler's confussion
// return type first, in-class later
Fraction& Fraction::operator=(const Fraction& other){
    nume = other.nume;
    deno = other.deno;
    return *this;
}

std::string Fraction::ToString()const{
    return std::to_string(this->nume) + "/" + std::to_string(this->deno);
}
// transform double to Fraction
Fraction Fraction::fromDecimal(const std::string text) {
    std::string digits = text;
    const auto dot = std::find(digits.begin(),digits.end(),'.');//find the position of '.' using iterator
    long long denominator = 1;

    if (dot != digits.end()) {
        auto decimalPlaces = digits.end() - dot - 1;

        for (auto i = 0; i < decimalPlaces; i++) {
            denominator *= 10;
        }

        digits.erase(dot);  // delete the dot
    }

    return Fraction(std::stoll(digits), denominator);//stoll transform string to long long 
}
// transform Fraction to double
Fraction:: operator double() const{
    return static_cast<double>(nume) / deno; // because of the explicit type, use static_cast transform
}

std::ostream& operator<<(std::ostream& os, Fraction& a){
    os << a.numerator() << '/' << a.denominator();
    return os;
}
std::istream& operator>>(std::istream& is, Fraction& a){
    long long numerator;
    long long denominator;
    char div; 

    if(!(is >> numerator >> div) || div != '/' || !(is>>denominator)){
        is.setstate(std::ios::failbit); // set 'is' fail
        return is;
    }
    a = Fraction(numerator,denominator);
    return is;
}

// overload computal operators, which are not member functions
Fraction operator+(const Fraction& a, const Fraction& b){
    long long numerator = a.numerator() * b.denominator() + b.numerator() * a.denominator();
    long long denominator = a.denominator() * b.denominator();
    return Fraction(numerator,denominator);
}

Fraction operator-(const Fraction& a, const Fraction& b){
    long long numerator = a.numerator() * b.denominator() - b.numerator() * a.denominator();
    long long denominator = a.denominator() * b.denominator();
    return Fraction(numerator,denominator);
}
Fraction operator*(const Fraction& a, const Fraction& b){
    long long numerator = a.numerator() * b.numerator();
    long long denominator = a.denominator() * b.denominator();
    return Fraction(numerator,denominator);
}
Fraction operator/(const Fraction& a, const Fraction& b){
    long long numerator = a.numerator() * b.denominator();
    long long denominator = a.denominator() * b.numerator();
    return Fraction(numerator,denominator);
}
bool operator>(const Fraction& a, const Fraction& b){
    long long nume_a = a.numerator() * b.denominator();
    long long nume_b = b.numerator() * a.denominator();
    return nume_a > nume_b;
}
bool operator>=(const Fraction& a, const Fraction& b){
    long long nume_a = a.numerator() * b.denominator();
    long long nume_b = b.numerator() * a.denominator();
    return nume_a >= nume_b; 
}
bool operator<(const Fraction& a, const Fraction& b){
    long long nume_a = a.numerator() * b.denominator();
    long long nume_b = b.numerator() * a.denominator();
    return nume_a < nume_b;
}
bool operator<=(const Fraction& a, const Fraction& b){
    long long nume_a = a.numerator() * b.denominator();
    long long nume_b = b.numerator() * a.denominator();
    return nume_a <= nume_b;
}
bool operator==(const Fraction& a, const Fraction& b){
    long long nume_a = a.numerator() * b.denominator();
    long long nume_b = b.numerator() * a.denominator();
    return nume_a == nume_b;
}
bool operator!=(const Fraction& a, const Fraction& b){
    long long nume_a = a.numerator() * b.denominator();
    long long nume_b = b.numerator() * a.denominator();
    return nume_a != nume_b;
}
