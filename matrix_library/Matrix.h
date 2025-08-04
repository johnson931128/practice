#pragma once

#include <iostream>
#include <stdexcept> 

template <typename T>
class Matrix {
private:
    size_t _rows;
    size_t _cols;
    T* _data;

public:
    // 建構函式
    Matrix(size_t rows, size_t cols);
    // 解構函式
    ~Matrix();

    // Getter 函式
    size_t getRows() const;
    size_t getCols() const;

    // 元素存取函式
    T& at(size_t r, size_t c);
    const T& at(size_t r, size_t c) const;

    // sloving shallow copy
    Matrix(const Matrix<T>& other);
    Matrix<T>& operator=(const Matrix<T>& other);
};

// --- 以下是原本在 .cpp 檔案中的實作 ---

// 建構函式實作
template <typename T>
Matrix<T>::Matrix(size_t rows, size_t cols)
    : _rows(rows), _cols(cols), _data(nullptr)
{
    _data = new T[rows * cols];
}

// 解構函式實作
template <typename T>
Matrix<T>::~Matrix() {
    delete[] _data;
}

// Getter 函式實作
template <typename T>
size_t Matrix<T>::getRows() const {
    return _rows;
}

template <typename T>
size_t Matrix<T>::getCols() const {
    return _cols;
}

// at() 函式實作 (非 const 版本，用於讀寫)
template <typename T>
T& Matrix<T>::at(size_t r, size_t c) {
    if (r >= _rows || c >= _cols) {
        throw std::out_of_range("Matrix::at: index is out of range");
    }
    return _data[r * _cols + c];
}

// at() 函式實作 (const 版本，用於唯讀)
template <typename T>
const T& Matrix<T>::at(size_t r, size_t c) const {
    if (r >= _rows || c >= _cols) {
        throw std::out_of_range("Matrix::at: index is out of range");
    }
    return _data[r * _cols + c];
}

// 運算子 << 的重載實作 (非成員函式)
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

template <typename T>
Matrix<T> operator+(const Matrix<T>& lhs, const Matrix<T>& rhs){
    if (lhs.getRows() != rhs.getRows() || lhs.getCols() != rhs.getCols()){
        throw std::invalid_argument("Matrix::operator+: dimensions of matrices do not match.");
    }
    Matrix<T> result(lhs.getRows(), lhs.getCols());

    for (size_t r = 0; r < result.getRows(); ++r){
        for (size_t c = 0; c < result.getCols(); ++c){
            result.at(r, c) = lhs.at(r, c) + rhs.at(r, c);
        }
    }
    return result;
}

// 複製建構函式 (Copy Constructor) 的實作
template <typename T>
Matrix<T>::Matrix(const Matrix<T>& other)
    : _rows(other._rows), _cols(other._cols), _data(nullptr) 
{
    // 為新物件配置自己的記憶體
    _data = new T[_rows * _cols];
    // 將來源物件的資料複製過來 (深複製)
    for (size_t i = 0; i < _rows * _cols; ++i) {
        _data[i] = other._data[i];
    }
}

// 複製賦值運算子 (Copy Assignment Operator) 的實作
template <typename T>
Matrix<T>& Matrix<T>::operator=(const Matrix<T>& other) {
    // 1. 檢查自我賦值 (例如 m = m;)
    if (this == &other) {
        return *this;
    }

    // 2. 釋放現有的舊記憶體
    delete[] _data;

    // 3. 複製維度並配置新的記憶體
    _rows = other._rows;
    _cols = other._cols;
    _data = new T[_rows * _cols];

    // 4. 複製來源物件的資料
    for (size_t i = 0; i < _rows * _cols; ++i) {
        _data[i] = other._data[i];
    }

    // 5. 回傳自身的參考以支援鏈式賦值 (例如 a = b = c;)
    return *this;
}














