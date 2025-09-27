#pragma once

#include <cstddef> // for size_t

template <typename T>
class MyVector {
public:
    MyVector();
    ~MyVector();
    void push_back(const T& value);
    size_t size() const;
    size_t capacity() const;
    T& operator[](size_t index);
    const T& operator[](size_t index) const;
private:
    T* _data;
    size_t _size;
    size_t _capacity;
};

#include "MyVector.tpp"

