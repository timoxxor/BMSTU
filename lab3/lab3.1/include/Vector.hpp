#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>
#include <cstddef>
#include <stdexcept>

class Vector {
private:
    int* data;
    int size;

public:
    Vector();
    explicit Vector(int n, int initVal = 0);
    Vector(const int* arr, int n);
    Vector(const Vector& other);
    Vector(Vector&& other) noexcept;
    ~Vector();

    Vector& operator=(const Vector& other);
    Vector& operator=(Vector&& other) noexcept;

    int& operator[](int index);
    const int& operator[](int index) const;

    Vector operator^(const Vector& other) const;

    int getSize() const;
    const int* getData() const;

    friend std::ostream& operator<<(std::ostream& os, const Vector& vec);
    friend std::istream& operator>>(std::istream& is, Vector& vec);
};

#endif
