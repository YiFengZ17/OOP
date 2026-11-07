#include "Diary.h"
#include <iostream>
#include <vector>

int main(int argc,char* argv[]){
    if(argc != 1 && argc != 3){
        std::cerr << "Please input like this : pdlist [start end]\n";
        return 1;
    }
    Date start,end;
    if(argc == 3){
        if(!Date::parse(argv[1],start) || !Date::parse(argv[2],end)){
            std::cerr << "Invalid date\n";
            return 1;
        }
        if(end < start){
            std::cerr << "Start date is after end date\n";
            return 1;
        }
    }
    Diary diary;
    if(!diary.load("diary.txt")){
        std::cerr << "Failed to load diary\n";
        return 1;
    }

    std::vector<Entry> result;
    if(argc == 1){
        result = diary.listall();
    }else{
        result = diary.between(start,end);
    }
    // 每篇一行：先日期再第一行正文
    for(const auto& entry : result){
        std::cout << entry.date.toString();
        if(!entry.content.empty()){
            std::cout << '\t' << entry.content[0];
        }
        std::cout << '\n';
    }
    // 只读不改，不写回文件，避免管道中与其他程序同时写
    return 0;
}
