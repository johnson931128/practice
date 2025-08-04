#include "MyVector.h"

template <typename T>
MyVector<T>::MyVector()
    : _data(new T[4]), _size(0), _capacity(4) {
}

template <typename T>
MyVector<T>::~MyVector() {
    delete[] _data;
}


template <typename T>
size_t MyVector<T>::size() const {
    return _size;
}

template <typename T>
size_t MyVector<T>::capacity() const{
    return _capacity;
}

template <typename T>
void MyVector<T>::push_back(const T& value) {
    if (_size == _capacity){
        size_t new_capacity = (_capacity == 0) ? 1 : _capacity * 2;
        T* new_data = new T[new_capacity];

        for (size_t i = 0; i < _size; i++) {
            new_data[i] = _data[i];
        }

        delete[] _data;

        _data = new_data;
        _capacity = new_capacity;
    }
    _data[_size] = value;
    _size++;
}

template <typename T>
T& MyVector<T>::operator[](size_t index) {
    return _data[index];
}

template <typename T>
const T& MyVector<T>::operator[](size_t index) const {
    return _data[index];

}


