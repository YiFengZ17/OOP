#include <iostream>
#include <map>
#include <string>
#include <cstring>
using namespace std;

struct full_name {
    const char* first;
    const char* last;

    bool operator<(const full_name& a) const {
        int firstCompare = strcmp(first, a.first);
        if (firstCompare != 0) {
            return firstCompare < 0;
        } else {
            return strcmp(last, a.last) < 0;
        }
    }
};

using PB=map<full_name, int>;

int main() {
    PB phonebook;

    full_name johnName = {"John", "Doe"};
    full_name janeName = {"Jane", "Doe"};
    phonebook[johnName] = 123456789;
    phonebook[janeName] = 987654321;

    full_name searchName = {"John", "Dorre"};
    if (phonebook.find(searchName) != phonebook.end()) {
        cout << "Found John's number: " << phonebook[searchName] << std::endl;
    } else {
        cout << "John's number not found." << std::endl;
    }

    for (const auto& entry : phonebook) {
        cout << entry.first.first << " " << entry.first.last << ": " << entry.second << std::endl;
    }
    
    return 0;
}
