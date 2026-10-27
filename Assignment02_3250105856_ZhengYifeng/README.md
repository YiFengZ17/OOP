# Assignment 02 — Students II

Student ID: 3250105856  
Name: ZhengYifeng

## Files

- `code/Student2.cpp`: the main C++ program.
- `code/Student2_test.txt`: test data with 12 students and 6 courses.
- `report/Assignment02_3250105856_ZhengYifeng.md`: editable report.
- `report/Assignment02_3250105856_ZhengYifeng.pdf`: report PDF.
- `README.md`: README document
## Environment

Linux 6.6.87.2-microsoft-standard-WSL2 
g++ 13.3.0.
The program requires C++11 or later.

## Build and run

Run from this assignment directory:

```sh
g++ -std=c++11 -Wall -Wextra -Wpedantic code/Student2.cpp -o Student2
./Student2 < code/Student2_test.txt
```

## Input format

Each record contains a student name, a course count, many course and score pairs:

```text
Alice   3   Math 5   English 4   Physics 3
Bob     2   Math 3   Programming 5
Carol   1   English 2
David   4   Math 4   English 5   Physics 1   Programming 4
Eve     0
Frank   2   Physics 5   Programming 3
Grace   2   Math 1   Art 5
Henry   1   Math 5
Ivy     3   English 1   Art 1   History 5
Jack    2   Programming 1   History 1
Kate    6   Math 2   English 3   Physics 4   Programming 2   Art 3   History 4
Leo     0
```

Input continues until EOF. Press Ctrl+D to stop the input.
A point worth looking is that a student can take zero courses but cannot repeat a course.

## Output

The table lists student numbers, names, course scores and student averages,
followed by each course's average, minimum and maximum.

