#include <algorithm> // For std::copy
#include <cstddef>   // For size_t

class MyClass {
private:
    int* data;
    size_t size;

public:
    // Constructor
    MyClass(size_t sz) : size(sz), data(new int[sz]) {}

    // Copy constructor
    MyClass(const MyClass& other) : size(other.size), data(new int[other.size]) {
        std::copy(other.data, other.data + other.size, data);
    }

    
    // Assignment operator
    MyClass& operator=(const MyClass& other) {
        if (this != &other) { // Protect against self-assignment
            // Allocate new memory and copy the elements
            int* newData = new int[other.size];
            std::copy(other.data, other.data + other.size, newData);

            // Free the old memory
            delete[] data;

            // Assign the new memory
            data = newData;
            size = other.size;
        }
        return *this;
    }
    

    // Destructor
    ~MyClass() {
        delete[] data;
    }

    // To disable the assignment operator, uncomment the following line:
    // MyClass& operator=(const MyClass& other) = delete;
};

int main() {
    // Example usage:
    MyClass a(10); // Create an object of MyClass with size 10
    MyClass b(a);  // Use copy constructor
    //MyClass c(5);  // Another object with different size
    //c = a;         // Use assignment operator

    // If the assignment operator is disabled:
    MyClass d(5);
    d = a;  // This will cause a compile error if the assignment operator is deleted explictly

    return 0;
}