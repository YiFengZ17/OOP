#ifndef DIARY_H
#define DIARY_H

#include"Entry.h"
#include<map>
#include<vector>

class Diary{
private:
    std::map<Date,Entry> entries;

public:
    void add(const Entry& entry);
    bool remove(const Date& date);
    bool find(const Date& date,Entry& out) const;
    bool load(const std::string& path);
    bool save(const std::string& path) const;
    std::vector<Entry> listall() const;
    std::vector<Entry> between(const Date& start, const Date& end) const;
};

#endif
