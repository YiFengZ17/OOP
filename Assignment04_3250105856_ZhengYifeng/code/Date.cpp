#include "Date.h"

bool Date::parse(const std::string& text, Date& date){
    if(text.size() != 8)return false;
    for(auto& c: text){
        if(c>'9' || c<'0')return false;
    }
    std::string Year = text.substr(0,4);
    std::string Month = text.substr(4,2);
    std::string Day = text.substr(6,2);

    int year = (Year[0]-'0')*1000 + (Year[1]-'0')*100 + (Year[2]-'0')*10 + (Year[3]-'0');
    int month = (Month[0]-'0')*10 + Month[1]-'0';
    int day = (Day[0]-'0')*10 + Day[1]-'0';

    if(year <= 0)return false;
    if(day > 31 || day < 1)return false;
    if(month>12 || month < 1)return false;
    bool isRunYear = false;
    if((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))isRunYear=true;
    if(isRunYear){
        if(month==2 && day>29)return false;
        if((month==4 || month==6 || month==9 || month==11)&&day > 30)return false;
    }else{
        if(month==2 && day>28)return false;
        if((month==4 || month==6 || month==9 || month==11)&&day > 30)return false;
    }

    date.year = year;
    date.month = month;
    date.day = day;
    return true;

}

std::string Date::toString() const{
    std::string y = std::to_string(year);
    while(y.size() < 4)y = "0" + y;
    std::string m = std::to_string(month);
    while(m.size() < 2)m = "0" + m;
    std::string d = std::to_string(day);
    while(d.size() < 2)d = "0" + d;
    return y + m + d;
    
}

// 因为执行map的比较逻辑必须要小于号
bool Date::operator<(const Date& other) const{
    if(year != other.year){
        return year < other.year;
    }else{
    if(month != other.month){
        return month < other.month;
    }else{
        return day < other.day;
    }
    }
}
