#include "Diary.h"
#include <iostream>

int main(int argc,char* argv[]){
    if(argc != 2){
        std::cerr << "Please input like this : pdremove YYYYMMDD\n";
        return -1;
    }
    Date date;
    if(!Date::parse(argv[1],date)){
        std::cerr << "Invalid date\n";
        return -1;
    }
    Diary diary;
    if(!diary.load("diary.txt")){
        std::cerr << "Failed to load diary\n";
        return -1;
    }
    if(!diary.remove(date)){
        std::cerr << "No entry for this date\n";
        return -1;
    }
    if(!diary.save("diary.txt")){
        std::cerr << "Failed to save diary\n";
        return -1;
    }
    return 0;
}
