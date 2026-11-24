#include"Vector.h"
#include<stdexcept>

// default ctor, an empty vector has no array
template <class T>
Vector<T>::Vector() : m_pElements(nullptr),m_nSize(0),m_nCapacity(0){}

// ctor, create 'size' elements with the default value (0 for int)
template <class T>
Vector<T>::Vector(int size) : m_pElements(nullptr),m_nSize(size),m_nCapacity(size){
    if(size < 0){
        throw std::invalid_argument("size can't be a negative number");
    }
    if (size > 0) {
        m_pElements = new T[size]{};
    }
}

// copy ctor, allocate a new array and copy the content of r
template <class T>
Vector<T>::Vector(const Vector& r): m_pElements(nullptr), m_nSize(r.m_nSize),m_nCapacity(r.m_nCapacity){
    // An empty vector with no capacity does not need an array.
    if (m_nCapacity > 0) {
        m_pElements = new T[m_nCapacity];
    }
    for(int i = 0;i<m_nSize;i++){
        m_pElements[i] = r.m_pElements[i];
    }
}

// copy assignment, the default one only copies the pointer,
// so two vectors would delete the same array twice
template <class T>
Vector<T>& Vector<T>::operator=(const Vector& r){
    // a = a should keep the content unchanged
    if(this == &r){
        return *this;
    }
    // build the new array first, then release the old one
    T* new_m_p = nullptr;
    if(r.m_nCapacity > 0){
        new_m_p = new T[r.m_nCapacity];
    }
    for(int i = 0;i<r.m_nSize;i++){
        new_m_p[i] = r.m_pElements[i];
    }
    delete[] m_pElements;
    m_pElements = new_m_p;
    m_nSize = r.m_nSize;
    m_nCapacity = r.m_nCapacity;
    return *this;
}

// dtor, release the array
template <class T>
Vector<T>::~Vector(){
    delete[] m_pElements;
}

// overload [], without bounds checking
template <class T>
T& Vector<T>::operator[](int index){
    return m_pElements[index];
}

// at, with bounds checking
template <class T>
T& Vector<T>::at(int index){
    if(index < 0 || index >= m_nSize){
        throw std::out_of_range("invalid index");
    }
    return m_pElements[index];
}
// return the size of vector
template <class T>
int Vector<T>::size() const{
    return m_nSize;
}
// push_back function, especially deal with v.push_back(v[0])
template <class T>
void Vector<T>::push_back(const T& x) {
    if (m_nSize == m_nCapacity) {
        // x can refer to an element in the old array, which inflate() will delete,
        // so use 'saved' to keep the original value
        T saved = x;
        inflate();
        m_pElements[m_nSize++] = saved;
    } else {
        m_pElements[m_nSize++] = x;
    }

}

// clear the contents and release the memory
template<class T>
void Vector<T>::clear(){
    delete[] m_pElements;
    m_nCapacity = 0;
    m_nSize = 0;
    m_pElements = nullptr;
}
// check whether vector is empty
template<class T>
bool Vector<T>::empty() const{
    return m_nSize == 0;
}
// double the capacity of vector, like dynamic table
template<class T>
void Vector<T>::inflate(){
    // an empty vector starts with one slot
    int newCapacity = (m_nCapacity == 0) ? 1 : m_nCapacity * 2;
    T* new_m_p = new T[newCapacity];
    // Copy the elements before releasing the old array.
    for(int i = 0;i<m_nSize;i++){
        new_m_p[i] = m_pElements[i];
    }
    delete[] m_pElements;
    m_pElements = new_m_p;
    m_nCapacity = newCapacity;
}
