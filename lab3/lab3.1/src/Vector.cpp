#include "Vector.hpp"
#include <utility>

Vector::Vector() : data(nullptr), size(0) {}

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

Vector::Vector(const Vector& other) : data(nullptr), size(other.size) {
    if (size > 0 && other.data != nullptr) {
        data = new int[size];
        for (int i = 0; i < size; ++i) {
            data[i] = other.data[i];
        }
    }
}

Vector::Vector(Vector&& other) noexcept : data(other.data), size(other.size) {
    other.data = nullptr;
    other.size = 0;
}

Vector::~Vector() {
    delete[] data;
    data = nullptr;
    size = 0;
}

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

std::ostream& operator<<(std::ostream& os, const Vector& vec) {
    os << "[";
    for (int i = 0; i < vec.size; ++i) {
        os << vec.data[i];
        if (i + 1 < vec.size) {
            os << ", ";
        }
    }
    os << "] (size: " << vec.size << ")";
    return os;
}

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
