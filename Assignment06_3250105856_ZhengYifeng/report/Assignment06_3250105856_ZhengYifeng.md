# Assignment 006: Vector
 
Zheng Yifeng | Student ID: 3250105856

## 1 Introduction

This assignment implements a dynamic array as a C++ class template. It was built with g++ 13.3.0 (C++17) on Ubuntu 24.04.4 LTS under WSL2.

## 2 Program Design

### 2.1 Data Layout

`Vector` uses a contiguous array to store data, which grows its capacity like a dynamic table. `m_pElements` points to the array, `m_nSize` counts the elements in use, and `m_nCapacity` counts the allocated slots. 

When an append needs more space, `inflate()` doubles the capacity, copies the elements into a new array, frees the old array, and updates the pointer. If the capacity is zero, it allocates one slot.

### 2.2 Element Access

Both `operator[]` and `at()` return an element by reference. `operator[]` uses the index directly. `at()` throws `std::out_of_range` if the index is outside `[0, m_nSize)`.

### 2.3 Appending an Element

`push_back()` writes at the current size and increases the size by one. If the array is full, it saves the value before growing the array. This keeps `v.push_back(v[0])` safe when growth releases the array that `v[0]` refers to, so the freed array is never read.

### 2.4 Copying

The copy constructor and `operator=` both copy every element into a new array. The given declaration has no `operator=`, and the default one only copies the pointer, so `a = b` freed the same array twice. I added `operator=` (the Rule of Three); it checks self-assignment and builds the new array before releasing the old one.

## 3 Testing

Run from the assignment directory. All test inputs are in `main.cpp`.

```bash
g++ -std=c++17 -Wall -Wextra -Wpedantic code/main.cpp -o ../vector06-test
../vector06-test
```

| Test | Input or operation | Observed result |
| --- | --- | --- |
| Default construction and growth | Start empty and append 100 integers from 0 to 990, in steps of 10 | Size is 100 and every value is preserved |
| Access and bounds | Write through both access functions and call `at(-1)` and `at(size())` | Writes are visible and both invalid indices throw `std::out_of_range` |
| Copy and destruction | Copy two strings, change the copy, and let both objects go out of scope | Original first string remains `hello` |
| Clear and reuse | Clear twice, then append 7 | Empty after clearing. Size is 1 and the first value is 7 after appending |
| Zero and negative sizes | Construct with 0 and append 8. Construct with -1 | Zero-size vector accepts 8. Negative size throws `std::invalid_argument` |
| Positive size | Construct with 3 and check initial values. Write two slots | Three initial zeros. First and last values become 11 and 33 |
| Empty copy | Copy an empty vector and append 21 to the copy | Original stays empty. Copy holds 21 |
| Append an existing element | Call `v.push_back(v[0])` on a full vector containing `hello` | The two elements are both `hello` |
| Copy assignment | Assign {1, 2} to a size-5 vector, change it, self-assign, then assign an empty vector | Source unchanged, self-assignment keeps the data, and the target becomes empty |
| Vector of vectors | Append a size-2 vector ten times, change one inner element | Only that element changes |

## 4 Conclusion

All ten test groups passed. The Vector class is built correctly.

## 5 AI Use in the Lab

1. debug the program, fix small errors, and polish the comments, code style and report wording.
2. fix memory leaks and learn how to manage dynamically allocated memory, including adding `operator=` to avoid the shallow copy.
3. find `v.push_back(v[0])` special case, and handle it.
4. generate test cases and part of the test program, including the copy assignment and vector-of-vectors tests, and keep asserts active under `NDEBUG`.
