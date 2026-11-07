#include"Diary.h"
#include<string>
#include<fstream>
#include<filesystem>


void Diary::add(const Entry& entry){
    entries[entry.date] = entry;
}

bool Diary::remove(const Date& date){
    auto success = entries.erase(date);
    return success;
}
bool Diary::find(const Date& date,Entry& out) const{
    auto it = entries.find(date);
    if(it != entries.end()){
        out = it->second;
        return true;
    }else{
        return false;
    }

}
bool Diary::load(const std::string& path){
    std::ifstream in(path);
    std::map<Date,Entry> loaded;
    std::string line;

    // 第一次运行时文件还不存在，视为空日记
    if(!std::filesystem::exists(path)){
        entries.clear();
        return true;
    }
    if(!in.is_open()){
        return false;
    }
    //共用文件流，外层读Date，内层读内容
    while(std::getline(in,line)){
        Entry entry;
        if(!Date::parse(line,entry.date))return false;
        bool ended = false;//检测是否读到""."
        while(std::getline(in,line)){
            if(line == "."){//遇到.
                ended = true;
                break;
            }else{
                entry.content.push_back(line);
            }
        }

        if(!ended)return false;
        loaded[entry.date] = entry;//插入新map
    }
    // 遇到结尾或发生错误
    if(!in.eof() || in.bad()){
        return false;
    }
    // Finally, update the entries
    entries.swap(loaded);
    return true;
}

bool Diary::save(const std::string& path) const{
    std::ofstream out(path);
    if(!out.is_open()){
        return false;
    }
    // 与load对应
    for(const auto& item : entries){
        out << item.first.toString() << '\n';// 写日期
        for(const auto& line : item.second.content){
            out << line << '\n';//写内容
        }
        out << ".\n";
    }
    out.close();
    if(!out){
        return false;
    }
    return true;
}

std::vector<Entry> Diary::listall() const{
    std::vector<Entry> result;
    for(const auto& item : entries){
        result.push_back(item.second);
    }
    return result;
}


std::vector<Entry> Diary::between(const Date& start, const Date& end) const{
    std::vector<Entry> result;
    for(const auto& item : entries){
        if(item.first < start || end < item.first)continue;
        else result.push_back(item.second);
    }
    return result;
}
