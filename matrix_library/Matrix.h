#pragma once

#include <iostream>
#include <stdexcept> 
#include <string> // 為了 main.cpp 中的 using IntMatrix = Matrix<int>;

// Forward declaration for the operator<<
template <typename T>
class Matrix;

template <typename T>
std::ostream& operator<<(std::ostream& os, const Matrix<T>& m);

// --- Class Definition ---
template <typename T>
class Matrix {
private:
    size_t _rows;
    size_t _cols;
    T* _data;

public:
    // 預設建構函式
    Matrix(size_t rows, size_t cols);
    // 解構函式
    ~Matrix();

    // --- The Rule of Five ---
    // 2. 複製建構函式
    Matrix(const Matrix<T>& other);
    // 3. 複製賦值運算子
    Matrix<T>& operator=(const Matrix<T>& other);
    // 4. 移動建構函式
    Matrix(Matrix<T>&& other) noexcept;
    // 5. 移動賦值運算子
    Matrix<T>& operator=(Matrix<T>&& other) noexcept;

    // Getter 函式
    size_t getRows() const;
    size_t getCols() const;

    // 元素存取函式
    T& at(size_t r, size_t c);
    const T& at(size_t r, size_t c) const;
};

// --- Implementations ---

// 預設建構函式
template <typename T>
Matrix<T>::Matrix(size_t rows, size_t cols)
    : _rows(rows), _cols(cols), _data(nullptr)
{
    std::cout << "[INFO] Default Constructor Called. Allocating " << _rows << "x" << _cols << " matrix." << std::endl;
    _data = new T[rows * cols];
}

// 解構函式
template <typename T>
Matrix<T>::~Matrix() {
    std::cout << "[INFO] Destructor Called. Deallocating " << _rows << "x" << _cols << " matrix." << std::endl;
    delete[] _data;
}

// 複製建構函式 (深複製)
template <typename T>
Matrix<T>::Matrix(const Matrix<T>& other)
    : _rows(other._rows), _cols(other._cols), _data(nullptr) 
{
    std::cout << "[INFO] Copy Constructor Called." << std::endl;
    _data = new T[_rows * _cols];
    for (size_t i = 0; i < _rows * _cols; ++i) {
        _data[i] = other._data[i];
    }
}

// 複製賦值運算子 (深複製)
template <typename T>
Matrix<T>& Matrix<T>::operator=(const Matrix<T>& other) {
    std::cout << "[INFO] Copy Assignment Operator Called." << std::endl;
    if (this == &other) { return *this; }
    delete[] _data;
    _rows = other._rows;
    _cols = other._cols;
    _data = new T[_rows * _cols];
    for (size_t i = 0; i < _rows * _cols; ++i) {
        _data[i] = other._data[i];
    }
    return *this;
}

// 移動建構函式 (資源竊取)
template <typename T>
Matrix<T>::Matrix(Matrix<T>&& other) noexcept
    : _rows(other._rows), _cols(other._cols), _data(other._data) 
{
    std::cout << "[INFO] Move Constructor Called." << std::endl;
    other._rows = 0;
    other._cols = 0;
    other._data = nullptr;
}

// 移動賦值運算子 (資源竊取)
template <typename T>
Matrix<T>& Matrix<T>::operator=(Matrix<T>&& other) noexcept {
    std::cout << "[INFO] Move Assignment Operator Called." << std::endl;
    if (this == &other) { return *this; }
    delete[] _data;
    _rows = other._rows;
    _cols = other._cols;
    _data = other._data;
    other._rows = 0;
    other._cols = 0;
    other._data = nullptr;
    return *this;
}

// Getter 函式
template <typename T>
size_t Matrix<T>::getRows() const { return _rows; }

template <typename T>
size_t Matrix<T>::getCols() const { return _cols; }

// at() 函式 (非 const)
template <typename T>
T& Matrix<T>::at(size_t r, size_t c) {
    if (r >= _rows || c >= _cols) {
        throw std::out_of_range("Matrix::at: index is out of range");
    }
    return _data[r * _cols + c];
}

// at() 函式 (const)
template <typename T>
const T& Matrix<T>::at(size_t r, size_t c) const {
    if (r >= _rows || c >= _cols) {
        throw std::out_of_range("Matrix::at: index is out of range");
    }
    return _data[r * _cols + c];
}

// 運算子 +
template <typename T>
Matrix<T> operator+(const Matrix<T>& lhs, const Matrix<T>& rhs) {
    if (lhs.getRows() != rhs.getRows() || lhs.getCols() != rhs.getCols()) {
        throw std::invalid_argument("Matrix::operator+: dimensions of matrices do not match.");
    }
    Matrix<T> result(lhs.getRows(), lhs.getCols());
    for (size_t r = 0; r < result.getRows(); ++r) {
        for (size_t c = 0; c < result.getCols(); ++c) {
            result.at(r, c) = lhs.at(r, c) + rhs.at(r, c);
        }
    }
    return result; // <<<<<<<< 這裡會觸發移動語意！
}

// 運算子 <<
template <typename T>
std::ostream& operator<<(std::ostream& os, const Matrix<T>& m) {
    os << "Matrix (" << m.getRows() << "x" << m.getCols() << "):" << std::endl;
    for (size_t r = 0; r < m.getRows(); ++r) {
        os << "[ ";
        for (size_t c = 0; c < m.getCols(); ++c) {
            os << m.at(r, c) << (c == m.getCols() - 1 ? "" : ", ");
        }
        os << " ]" << std::endl;
    }
    return os;
}
