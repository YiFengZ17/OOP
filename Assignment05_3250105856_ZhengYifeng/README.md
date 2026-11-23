# Assignment 005 — Fraction

- Name: Zheng Yifeng
- Student ID: 3250105856
- Language: C++ (C++17)

## Files

| File | Purpose |
| --- | --- |
| `code/Fraction.h` | Fraction class and operator declarations |
| `code/Fraction.cpp` | Fraction operations, conversion, and stream input and output |
| `code/main.cpp` | Demonstration with fixed inputs for manual checking |
| `report/Assignment05_3250105856_ZhengYifeng.pdf` | Program report with test cases and results |
| `report/Assignment05_3250105856_ZhengYifeng.md`, `.tex` | Editable report sources |

## Environment

Ubuntu 24.04.4 LTS on WSL2, g++ 13.3.0. The program is built directly with g++.

## Build and Run

Run from the assignment directory. The executable goes in the parent directory.

```bash
g++ -std=c++17 -Wall -Wextra -Wpedantic code/Fraction.cpp code/main.cpp -o ../fraction05-test
../fraction05-test
```

## Testing

The program prints each result so you can check it against the test table in the report. For example, the addition of `1/2` and `1/3` should print `Addition: 5/6`. All test inputs are in `main.cpp`, so the program does not need any input files or keyboard input.

Stream input and output use `numerator/denominator`. For example, `6/-8` is read as `-3/4`. A wrong separator sets the stream's failure flag. A zero denominator is rejected by the constructor, including when the fraction is read from a stream.

Pass valid finite decimal text to `fromDecimal`, such as `1.414`, `-0.25`, and `+.5`. The digits and the power-of-ten denominator must fit in the supported integer range. The parser can read only the numeric prefix of malformed input. The full list of test cases is in the report.
