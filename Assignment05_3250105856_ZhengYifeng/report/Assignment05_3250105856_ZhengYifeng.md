# Assignment 005: Fraction

Program Report  
Zheng Yifeng | Student ID: 3250105856

## 1 Introduction

This assignment implements a C++ class for fractions. It supports arithmetic, comparisons, conversion to `double` and text, stream input and output, and conversion from a finite decimal string.

The program was built with g++ 13.3.0 (C++17) on Ubuntu 24.04.4 LTS under WSL2.

## 2 Program Design

`Fraction` stores a numerator and a denominator as `long long` values. The normalization constructor is the core function of this program from my perspective. What constructor do are rejecting a zero denominator, moving the negative sign to the numerator, and reducing the fraction using the greatest common divisor(gcd). The default constructor gives `0/1`. Arithmetic operators pass their results back to the constructor. Comparison operators use cross multiplication.All by overloading operators outside of the class.

`fromDecimal` is the second important part of this program, which counts the places after the decimal point and multiplies the denominator by ten for each place. It removes the point, reads the numerator with `std::stoll`, and lets the constructor reduce the result. 

Stream input checks the `n/d` format and leaves the zero denominator check to the constructor.

## 3 Testing

Run these commands from the assignment directory. `main.cpp` provides all test inputs.

```bash
g++ -std=c++17 -Wall -Wextra -Wpedantic code/Fraction.cpp code/main.cpp -o ../fraction05-test
../fraction05-test
```

| Test | Input or operation | Observed result |
| --- | --- | --- |
| Construction | Default, `(6, -8)`, `(0, -8)` | `0/1`, `-3/4`, `0/1` |
| Copy and assignment | Copy `-3/4` and assign the copy | `-3/4` and `-3/4` |
| Arithmetic | `1/2` and `1/3` with `+`, `-`, `*`, `/` | `5/6`, `1/6`, `1/6`, `3/2` |
| Comparisons | `-3/4 < 1/3`, `1/3 <= 1/2`, `1/2 == 2/4`, `1/2 != 1/3`, `1/2 >= 2/4`, `1/2 > 1/3` | Six `true` values |
| String and double | `ToString()` on `2/3` and a cast of `1/4` to `double` | `2/3` and `0.25` |
| Decimal strings | `"1.414"`, `"-0.25"`, `"+.5"` | `707/500`, `-1/4`, `1/2` |
| Stream input and output | Read `"6/-8 2/4"`, then print both fractions | `-3/4 1/2` |
| Wrong separator | Read `"6:8"` into the first fraction | `failed: true`, fraction remains `-3/4` |
| Empty decimal | Pass `""` to `fromDecimal` | `invalid_argument` |
| Zero denominator | Construct `Fraction(6, 0)` | `invalid_argument` |
| Division by zero | Divide `1/2` by the default fraction | `invalid_argument` |
| Zero in stream input | Read `"6/0"` into the first fraction | `invalid_argument`, fraction remains `-3/4` |

The program prints the values for manual comparison. The output from the run matched the expected results shown in the table.

## 4 Conclusion

The tests cover the required operations and selected error cases, which tells that the Fraction class is built successfully.

## 5.AI use in the lab
1. debug and learn the errors I made.
2. think up the test cases and the test program
3. check the correctness of my comments and codes
4. fix the handling of invalid input in `fromDecimal`
