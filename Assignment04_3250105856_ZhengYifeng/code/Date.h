#ifndef DATE_H
#define DATE_H

#include<string>

class Date{
public:
    static bool parse(const std::string& text, Date& out);
    std::string toString() const;
    bool operator<(const Date& other) const;
private:
    int year = 0;
    int month = 0;
    int day = 0;
};

#endif
