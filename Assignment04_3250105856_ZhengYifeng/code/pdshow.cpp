#include "Diary.h"
#include <iostream>

int main(int argc,char* argv[]){
    if(argc != 2){
        std::cerr << "Please input like this : pdshow YYYYMMDD\n";
        return 1;
    }
    Date date;
    if(!Date::parse(argv[1],date)){
        std::cerr << "Invalid date\n";
        return 1;
    }
    Diary diary;
    if(!diary.load("diary.txt")){
        std::cerr << "Failed to load diary\n";
        return 1;
    }
    Entry entry;
    if(!diary.find(date,entry)){
        std::cerr << "No entry for this date\n";
        return 1;
    }
    for(const auto& line : entry.content){
        std::cout << line << '\n';
    }
    // 只读不改，不写回文件，避免管道中与其他程序同时写
    return 0;
}
