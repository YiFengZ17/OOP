#include <algorithm>
#include <iomanip>
#include <iostream>
#include <map>
#include <numeric>
#include <string>
#include <vector>
using namespace std;

class Student {
public:
    string name;
    map<string, int> scores;

    double average() const {
        double sum = 0;
        for (const auto& entry : scores) {
            sum += entry.second;
        }
        return scores.empty() ? 0 : sum / scores.size();
    }
};

class Course {
public:
    void addScore(int score) {
        scores.push_back(score);
    }

    // A course is created only when an enrolled student's score is read.
    double average() const {
        return accumulate(scores.begin(), scores.end(), 0.0) / scores.size();
    }

    int minimum() const {
        return *min_element(scores.begin(), scores.end());
    }

    int maximum() const {
        return *max_element(scores.begin(), scores.end());
    }

private:
    vector<int> scores;
};

int main() {
    vector<Student> students;
    vector<string> courseNames;
    map<string, Course> courses;
    string name;

    // Input until EOF: name, course count, then (course name, score) pairs.
    // Example: Alice 2 Math 5 English 4
    while (cin >> name) {
        Student student;
        student.name = name;
        int count;
        if (!(cin >> count) || count < 0) {
            cerr << "Invalid course count.\n";
            return 1;
        }

        for (int i = 0; i < count; ++i) {
            string course;
            int score;
            if (!(cin >> course >> score) || score < 1 || score > 5) {
                cerr << "Expected a course name and an integer score from 1 to 5.\n";
                return 1;
            }
            if (!student.scores.emplace(course, score).second) {
                cerr << "Duplicate course for " << name << ".\n";
                return 1;
            }
            // Keep columns in the order courses first appear in the input.
            if (courses.count(course) == 0) {
                courseNames.push_back(course);
            }
            courses[course].addScore(score);
        }
        students.push_back(student);
    }
    if (cin.bad() || !cin.eof()) {
        cerr << "Input error.\n";
        return 1;
    }

    cout << fixed << setprecision(2);
    cout << "no\tname";
    for (const auto& course : courseNames) {
        cout << '\t' << course;
    }
    cout << "\taverage\n";

    for (size_t i = 0; i < students.size(); ++i) {
        const Student& student = students[i];
        cout << i + 1 << '\t' << student.name;
        for (const auto& course : courseNames) {
            const auto score = student.scores.find(course);
            // Missing courses are not zero scores and do not affect averages.
            cout << '\t';
            if (score == student.scores.end()) {
                cout << '-';
            } else {
                cout << score->second;
            }
        }
        cout << '\t';
        if (student.scores.empty()) {
            cout << '-';
        } else {
            cout << student.average();
        }
        cout << '\n';
    }

    // Each course's statistics include only students enrolled in that course.
    cout << "\taverage";
    for (const auto& course : courseNames) {
        cout << '\t' << courses.at(course).average();
    }
    cout << "\n\tmin";
    for (const auto& course : courseNames) {
        cout << '\t' << courses.at(course).minimum();
    }
    cout << "\n\tmax";
    for (const auto& course : courseNames) {
        cout << '\t' << courses.at(course).maximum();
    }
    cout << '\n';
    return 0;
}
