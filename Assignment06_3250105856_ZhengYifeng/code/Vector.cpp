#include"Vector.h"
#include<stdexcept>

//default ctor
template <class T>
Vector<T>::Vector() : m_pElements(nullptr),m_nSize(0),m_nCapacity(0){}

//ctor
template <class T>
Vector<T>::Vector(int size) : m_pElements(nullptr),m_nSize(size),m_nCapacity(size){
    if(size < 0){
        throw std::invalid_argument("size can't be a negative number");
    }
    if (size > 0) {
        m_pElements = new T[size]{};
    }
}

// copy ctor, allocate new memory and copy content
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
// delete the memory
template <class T>
Vector<T>::~Vector(){
    delete[] m_pElements;
}

// overload [], without bound check
template <class T>
T& Vector<T>::operator[](int index){
    return m_pElements[index];
}

//overload at, with bound check
template <class T>
T& Vector<T>::at(int index){
    if(index < 0 || index >= m_nSize){
        throw std::out_of_range("invalid index");
    }
    return m_pElements[index];
}
// return the size of vector
template <class T>
int Vector<T>:: size() const{
    return m_nSize;
}
// push_back function, especially deal with v.push_back(v[0])
template <class T>
void Vector<T>::push_back(const T& x) {
    if (m_nSize == m_nCapacity) {
        // x can refer to an element in the array that inflate() will delete.
        // so use a 'saved' to keep the original value
        T saved = x;
        inflate();
        m_pElements[m_nSize++] = saved;
    } else {
        m_pElements[m_nSize++] = x;
    }

}

// clear all the parameter and delete the memory
template<class T>
void Vector<T> :: clear(){
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
    // if vector is empty
    if(m_nCapacity == 0){
        m_pElements = new T[1];
        m_nCapacity+=1;
        return;
    }
    // if vector is not empty, Copy the elements before releasing the old array.
    m_nCapacity*=2;
    T* new_m_p = new T[m_nCapacity];
    for(int i = 0;i<m_nSize;i++){
        new_m_p[i] = m_pElements[i];
    }
    delete[] m_pElements;
    m_pElements = new_m_p;
    
}
