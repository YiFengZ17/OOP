#ifndef ENTRY_H
#define ENTRY_H

#include<vector>
#include<string>
#include"Date.h"

class Entry{
public:
    Date date;
    std::vector<std::string> content;
};

#endif