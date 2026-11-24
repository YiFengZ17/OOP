// Keep assert active even when NDEBUG is defined, or the checks would be removed.
#undef NDEBUG
#include <cassert>
#include <iostream>
#include <stdexcept>
#include <string>

// The template definitions are currently in Vector.cpp.
#include "Vector.cpp"

int main() {
    // Check the empty state, then add enough values to grow several times.
    Vector<int> numbers;
    assert(numbers.empty());
    assert(numbers.size() == 0);

    for (int i = 0; i < 100; ++i) {
        numbers.push_back(i * 10);
    }
    assert(numbers.size() == 100);
    assert(!numbers.empty());
    for (int i = 0; i < numbers.size(); ++i) {
        assert(numbers[i] == i * 10);
    }
    std::cout << "PASS: default constructor, push_back, and growth" << std::endl;

    // Both access functions return a reference that can change an element.
    numbers[0] = 42;
    assert(numbers.at(0) == 42);
    numbers.at(1) = 43;
    assert(numbers[1] == 43);
    int badIndexes[2] = {-1, numbers.size()};
    for (int i = 0; i < 2; ++i) {
        bool threw = false;
        try {
            numbers.at(badIndexes[i]);
        } catch (const std::out_of_range&) {
            threw = true;
        }
        assert(threw);
    }
    std::cout << "PASS: element access and bounds checking" << std::endl;

    // The copy has its own array and can be destroyed independently.
    {
        Vector<std::string> words;
        words.push_back("hello");
        words.push_back("world");
        Vector<std::string> copy(words);
        assert(copy.size() == 2);
        assert(copy[0] == "hello" && copy[1] == "world");
        copy[0] = "changed";
        assert(words[0] == "hello");
    }
    std::cout << "PASS: copy constructor and destruction" << std::endl;

    // Repeated clear calls should be safe, and the vector can be reused.
    numbers.clear();
    numbers.clear();
    assert(numbers.empty());
    assert(numbers.size() == 0);
    numbers.push_back(7);
    assert(numbers.size() == 1 && numbers[0] == 7);
    std::cout << "PASS: clear and reuse" << std::endl;

    Vector<int> zero(0);
    assert(zero.empty());
    zero.push_back(8);
    assert(zero.size() == 1 && zero[0] == 8);

    bool threw = false;
    try {
        Vector<int> invalid(-1);
    } catch (const std::invalid_argument&) {
        threw = true;
    }
    assert(threw);
    std::cout << "PASS: zero and negative constructor sizes" << std::endl;

    Vector<int> sized(3);
    assert(sized.size() == 3 && !sized.empty());
    for (int i = 0; i < sized.size(); ++i) {
        assert(sized[i] == 0);
    }
    sized[0] = 11;
    sized.at(2) = 33;
    assert(sized.at(0) == 11 && sized[2] == 33);
    std::cout << "PASS: positive constructor size" << std::endl;

    // Adding a value to an empty copy should leave the original empty.
    Vector<int> empty;
    Vector<int> emptyCopy(empty);
    assert(emptyCopy.empty());
    emptyCopy.push_back(21);
    assert(emptyCopy.size() == 1 && emptyCopy[0] == 21);
    assert(empty.empty());
    std::cout << "PASS: copy an empty vector and append" << std::endl;

    // The second append grows the array while its argument refers to that array.
    Vector<std::string> repeated;
    repeated.push_back("hello");
    repeated.push_back(repeated[0]);
    assert(repeated.size() == 2);
    assert(repeated[0] == "hello" && repeated[1] == "hello");
    std::cout << "PASS: append an existing element during growth" << std::endl;

    // Assignment gives the left side its own array, so both objects stay independent.
    {
        Vector<int> source;
        source.push_back(1);
        source.push_back(2);
        Vector<int> target(5);
        target = source;
        assert(target.size() == 2 && target[0] == 1 && target[1] == 2);
        target[0] = 100;
        assert(source[0] == 1);

        target = target;
        assert(target.size() == 2 && target[0] == 100);

        Vector<int> nothing;
        target = nothing;
        assert(target.empty());
        target.push_back(9);
        assert(target.size() == 1 && nothing.empty());
    }
    std::cout << "PASS: copy assignment and self-assignment" << std::endl;

    // Growing a vector of vectors copies each inner vector with operator=.
    {
        Vector<int> inner(2);
        Vector<Vector<int>> table;
        for (int i = 0; i < 10; ++i) {
            table.push_back(inner);
        }
        table[0][0] = 5;
        assert(table.size() == 10 && table[0][0] == 5);
        assert(table[9][0] == 0 && inner[0] == 0);
    }
    std::cout << "PASS: vector of vectors" << std::endl;

    return 0;
}
