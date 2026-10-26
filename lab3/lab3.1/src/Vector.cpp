#include "Vector.hpp"
#include <iostream>
#include <utility>
#include <cstring>

// 1. Конструктор по умолчанию (пустой вектор)
Vector::Vector() : data(nullptr), size(0) {}

// Конструктор вектора заданного размера
Vector::Vector(int n, int initVal) : data(nullptr), size(0) {
    if (n < 0) {
        throw std::invalid_argument("Vector size cannot be negative");
    }
    if (n > 0) {
        size = n;
        data = new int[size];
        for (int i = 0; i < size; ++i) {
            data[i] = initVal;
        }
    }
}

// 2. Конструктор на основе одномерного массива размерности n
Vector::Vector(const int* arr, int n) : data(nullptr), size(0) {
    if (n < 0) {
        throw std::invalid_argument("Array size cannot be negative");
    }
    if (n > 0 && arr != nullptr) {
        size = n;
        data = new int[size];
        for (int i = 0; i < size; ++i) {
            data[i] = arr[i];
        }
    }
}

// 3. Конструктор копирования (глубокое копирование)
Vector::Vector(const Vector& other) : data(nullptr), size(other.size) {
    if (size > 0 && other.data != nullptr) {
        data = new int[size];
        for (int i = 0; i < size; ++i) {
            data[i] = other.data[i];
        }
    }
}

// 4. Конструктор перемещения
Vector::Vector(Vector&& other) noexcept : data(other.data), size(other.size) {
    other.data = nullptr;
    other.size = 0;
}

// 5. Деструктор
Vector::~Vector() {
    delete[] data;
    data = nullptr;
    size = 0;
}

// 6. Операция присваивания с копированием
Vector& Vector::operator=(const Vector& other) {
    if (this == &other) {
        return *this;
    }

    int* newData = nullptr;
    if (other.size > 0 && other.data != nullptr) {
        newData = new int[other.size];
        for (int i = 0; i < other.size; ++i) {
            newData[i] = other.data[i];
        }
    }

    delete[] data;
    data = newData;
    size = other.size;

    return *this;
}

// 7. Операция присваивания с перемещением
Vector& Vector::operator=(Vector&& other) noexcept {
    if (this == &other) {
        return *this;
    }

    delete[] data;

    data = other.data;
    size = other.size;

    other.data = nullptr;
    other.size = 0;

    return *this;
}

// 8. Перегрузка операции обращения по индексу []
int& Vector::operator[](int index) {
    if (index < 0 || index >= size) {
        throw std::out_of_range("Vector index out of range");
    }
    return data[index];
}

const int& Vector::operator[](int index) const {
    if (index < 0 || index >= size) {
        throw std::out_of_range("Vector index out of range");
    }
    return data[index];
}

// 9. Индивидуальная операция Варианта 15:
// Побитовая операция XOR (^) с двумя векторами одинаковой размерности
Vector Vector::operator^(const Vector& other) const {
    if (size != other.size) {
        throw std::invalid_argument("Vectors must have the same dimension for XOR operation (^)");
    }

    Vector result(size);
    for (int i = 0; i < size; ++i) {
        result.data[i] = data[i] ^ other.data[i];
    }
    return result;
}

int Vector::getSize() const {
    return size;
}

const int* Vector::getData() const {
    return data;
}

// Оператор вставки в поток (std::ostream)
std::ostream& operator<<(std::ostream& os, const Vector& vec) {
    os << "[";
    for (int i = 0; i < vec.size; ++i) {
        os << vec.data[i];
        if (i + 1 < vec.size) {
            os << ", ";
        }
    }
    os << "] (размер: " << vec.size << ")";
    return os;
}

// Оператор извлечения из потока (std::istream)
std::istream& operator>>(std::istream& is, Vector& vec) {
    int newSize = 0;
    if (is >> newSize) {
        if (newSize < 0) {
            is.setstate(std::ios::failbit);
            return is;
        }

        int* newElements = nullptr;
        if (newSize > 0) {
            newElements = new int[newSize];
            for (int i = 0; i < newSize; ++i) {
                if (!(is >> newElements[i])) {
                    delete[] newElements;
                    is.setstate(std::ios::failbit);
                    return is;
                }
            }
        }

        delete[] vec.data;
        vec.data = newElements;
        vec.size = newSize;
    }
    return is;
}
