#include "Fraction.h"
#include <iostream>
#include <sstream>
#include <stdexcept>

int main() {
    // Test construction, reduction, and copying.
    Fraction a(1, 2);
    Fraction b(1, 3);
    Fraction negative(6, -8);

    std::cout << "Default, reduced, zero: "
              << Fraction() << ' ' << negative << ' ' << Fraction(0, -8) << '\n';

    Fraction copied(negative);
    Fraction assigned;
    assigned = copied;
    std::cout << "Copied and assigned: " << copied << ' ' << assigned << '\n';

    // Print the arithmetic and comparison results.
    std::cout << "Addition: " << a + b << '\n';
    std::cout << "Subtraction: " << a - b << '\n';
    std::cout << "Multiplication: " << a * b << '\n';
    std::cout << "Division: " << a / b << '\n';

    std::cout << std::boolalpha
              << "Comparisons (< <= == != >= >): "
              << (negative < b) << ' ' << (b <= a) << ' '
              << (a == Fraction(2, 4)) << ' ' << (a != b) << ' '
              << (a >= Fraction(2, 4)) << ' ' << (a > b) << '\n';

    // Test conversion to and from other types.
    std::cout << "As string: " << Fraction(2, 3).toString() << '\n';
    std::cout << "As double: " << static_cast<double>(Fraction(1, 4)) << '\n';
    std::cout << "Decimals (1.414, -0.25, +.5): "
              << Fraction::fromDecimal("1.414") << ' '
              << Fraction::fromDecimal("-0.25") << ' '
              << Fraction::fromDecimal("+.5") << '\n';

    // Use a string stream so the test needs no keyboard input.
    std::istringstream input("6/-8 2/4");
    Fraction first;
    Fraction second;
    input >> first >> second;
    std::cout << "Read and print: " << first << ' ' << second << '\n';

    std::istringstream badInput("6:8");
    badInput >> first;
    std::cout << "Bad separator, failed: " << badInput.fail()
              << ", fraction: " << first << '\n';

    // Print the exceptions raised by invalid inputs.
    std::cout << "Empty decimal: ";
    try {
        std::cout << Fraction::fromDecimal("") << '\n';
    } catch (const std::invalid_argument&) {
        std::cout << "invalid_argument\n";
    }

    std::cout << "Decimal with trailing letters (1.23abc): ";
    try {
        std::cout << Fraction::fromDecimal("1.23abc") << '\n';
    } catch (const std::invalid_argument&) {
        std::cout << "invalid_argument\n";
    }

    std::cout << "Construct 6/0: ";
    try {
        std::cout << Fraction(6, 0) << '\n';
    } catch (const std::invalid_argument&) {
        std::cout << "invalid_argument\n";
    }

    std::cout << "Divide by zero: ";
    try {
        std::cout << a / Fraction() << '\n';
    } catch (const std::invalid_argument&) {
        std::cout << "invalid_argument\n";
    }

    std::istringstream zeroInput("6/0");
    std::cout << "Read 6/0: ";
    try {
        zeroInput >> first;
        std::cout << first << '\n';
    } catch (const std::invalid_argument&) {
        std::cout << "invalid_argument, fraction still " << first << '\n';
    }
}
