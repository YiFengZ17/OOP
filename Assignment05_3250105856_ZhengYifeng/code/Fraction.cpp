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

// Copying an already reduced fraction preserves its representation.
Fraction::Fraction(const Fraction& other): nume(other.nume), deno(other.deno) {}

// Return the left operand so assignments can be chained.
Fraction& Fraction::operator=(const Fraction& other){
    nume = other.nume;
    deno = other.deno;
    return *this;
}

std::string Fraction::ToString()const{
    return std::to_string(this->nume) + "/" + std::to_string(this->deno);
}
// Remove the decimal point and keep track of its original place value.
Fraction Fraction::fromDecimal(const std::string text) {
    // Allow one leading sign, then only digits and at most one '.'.
    size_t start = (!text.empty() && (text[0] == '+' || text[0] == '-')) ? 1 : 0;
    int digitCount = 0;
    int dotCount = 0;
    for (size_t i = start; i < text.size(); i++) {
        if (text[i] == '.') dotCount++;
        else if (text[i] >= '0' && text[i] <= '9') digitCount++;
        else throw std::invalid_argument("not a finite decimal: " + text);
    }
    // At most 18 digits keeps both the numerator and 10^places inside long long.
    if (digitCount == 0 || dotCount > 1 || digitCount > 18) {
        throw std::invalid_argument("not a finite decimal: " + text);
    }

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

Fraction::operator double() const {
    return static_cast<double>(nume) / static_cast<double>(deno);//because of explicit,using static_cast<double>
}

std::ostream& operator<<(std::ostream& os, const Fraction& a) {
    return os << a.ToString();
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
// Only < and == do real work; the other four are built from them.
// Both denominators are positive, so cross multiplication keeps the order.
bool operator<(const Fraction& a, const Fraction& b){
    return a.numerator() * b.denominator() < b.numerator() * a.denominator();
}
// Both fractions are reduced, so equal values have the same numerator and denominator.
bool operator==(const Fraction& a, const Fraction& b){
    return a.numerator() == b.numerator() && a.denominator() == b.denominator();
}
bool operator!=(const Fraction& a, const Fraction& b){
    return !(a == b);
}
bool operator>(const Fraction& a, const Fraction& b){
    return b < a;
}
bool operator<=(const Fraction& a, const Fraction& b){
    return !(b < a);
}
bool operator>=(const Fraction& a, const Fraction& b){
    return !(a < b);
}
