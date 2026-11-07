#include "Diary.h"
#include <iostream>
#include <string>

int main(int argc,char* argv[]){
    if(argc != 2){
        std::cerr << "Please input like this : pdadd YYYYMMDD\n";
        return 1;
    }

    Entry entry;
    if(!Date::parse(argv[1],entry.date)){
        std::cerr << "Invalid date\n";
        return 1;
    }

    Diary diary;
    if(!diary.load("diary.txt")){
        std::cerr << "Failed to load diary\n";
        return 1;
    }

    std::string line;
    while(std::getline(std::cin,line)){
        if(line == ".")break;
        entry.content.push_back(line);
    }
    
    if(std::cin.bad() || (std::cin.fail() && !std::cin.eof())){
        std::cerr << "Failed to read content\n";
        return 1;
    }

    diary.add(entry);
    if(!diary.save("diary.txt")){
        std::cerr << "Failed to save diary\n";
        return 1;
    }
    return 0;
}
