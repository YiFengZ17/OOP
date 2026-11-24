# Assignment 006 — Vector

- Name: Zheng Yifeng
- Student ID: 3250105856
- Language: C++ (C++17)

## Files

| File | Purpose |
| --- | --- |
| `code/Vector.h` | Vector class template declaration |
| `code/Vector.cpp` | Member function definitions |
| `code/main.cpp` | Tests with fixed inputs |
| `report/Assignment06_3250105856_ZhengYifeng.pdf` | Program report with test cases and results |
| `report/Assignment06_3250105856_ZhengYifeng.md`, `.tex` | Editable report sources |

## Environment

Ubuntu 24.04.4 LTS on WSL2, g++ 13.3.0. The program is built directly with g++.

## Build and Run

Run from the assignment directory. Compile `main.cpp`, which includes the template definitions from `Vector.cpp`.

```bash
g++ -std=c++17 -Wall -Wextra -Wpedantic code/main.cpp -o ../vector06-test
../vector06-test
```

The program needs no keyboard input or data files. It uses assertions to check the results and prints ten `PASS` lines when all tests pass. The assertions stay active even if `NDEBUG` is defined.

The given declaration has no copy assignment operator, so `Vector.h` adds `operator=`. Without it, `a = b` and a `Vector` of `Vector`s would copy only the pointer and free the same array twice.
