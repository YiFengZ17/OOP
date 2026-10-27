#include<iostream>
#include<cstring>
#include<vector>
using namespace std;

//Create the class of Student
class Student{
public:
//Student's information are name and scores
    string name;
    int score1;
    int score2;
    int score3;
    float ave;
// Get name
    void getName(string n){
        name = n;
    }
//Get scores and calculate the average score
    void getScores(int s1, int s2,int s3){
        if(s1<1 || s1>5 || s2<1 || s2>5 || s3<1 || s3>5){
            cout << "score out of range!" << endl;
            exit(1);
        }
        score1 = s1;
        score2 = s2;
        score3 = s3;
        ave = (float)(s1 + s2 + s3) / 3;
    }
};
//Create the class of Course
class Course{
public:
//Use a vector to store one Course's scores
    vector<int>scores;
//add score
    void get_Course_Score(int x){
        scores.emplace_back(x);
    }
//calculate the average score of the course
    float getAve(){
        float sum = 0.0;
        for(auto x: scores){
            sum += x;
        }
        return sum / scores.size();
    }
//get the min score
    int getMin(){
        int m = 6;
        for(auto x:scores){
            m = min(m,x);
        }
        return m;
    }
//get the max score
    int getMax(){
        int m = 0;
        for(auto x:scores){
            m = max(m,x);
        }
        return m;
    }
};


int main(){
    //Create 3 Course, a vector to store different Students
    Course C1;
    Course C2;
    Course C3;
    vector<Student> Students;

    cout << "Please input data with 10 Students' information" << endl;
    //Process the input
    for(int i = 0;i<10;++i){
        Student s;
        string name;
        int s1,s2,s3;
        cin >> name >> s1 >> s2 >> s3;
        s.getScores(s1,s2,s3);
        s.getName(name);
        C1.get_Course_Score(s1);
        C2.get_Course_Score(s2);
        C3.get_Course_Score(s3);
        Students.emplace_back(s);
    }
    //output the result (use AI to help me do the alignment)
    cout << "no\tname\tscore1\tscore2\tscore3\taverage" << endl;
    for(int i = 1;i<11;++i){
        Student s = Students[i-1];
        cout << i << "\t" << s.name << "\t" << s.score1 << "\t" << s.score2 << "\t" << s.score3 << "\t" << s.ave << endl;
    }
    cout << "\t" << "average" << "\t" << C1.getAve() << "\t" << C2.getAve() << "\t" << C3.getAve() << endl;
    cout << "\t" << "min" << "\t" << C1.getMin() << "\t" << C2.getMin() << "\t" << C3.getMin() << endl;
    cout << "\t" << "max" << "\t" << C1.getMax() << "\t" << C2.getMax() << "\t" << C3.getMax() << endl;
    return 0;
}