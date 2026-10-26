#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>
#include <cstddef>
#include <stdexcept>

/**
 * @brief Класс динамического вектора целых чисел (Вариант 15, Часть 1)
 */
class Vector {
private:
    int* data;  ///< Указатель на динамический массив элементов
    int size;   ///< Размерность (количество элементов) вектора

public:
    // 1. Конструктор по умолчанию (создает пустой вектор, размер 0)
    Vector();

    // Конструктор вектора заданного размера с одинаковыми значениями элементов
    explicit Vector(int n, int initVal = 0);

    // 2. Конструктор на основе одномерного массива размерности n
    Vector(const int* arr, int n);

    // 3. Конструктор копирования (глубокое копирование)
    Vector(const Vector& other);

    // 4. Конструктор перемещения
    Vector(Vector&& other) noexcept;

    // 5. Деструктор
    ~Vector();

    // 6. Операция присваивания с копированием
    Vector& operator=(const Vector& other);

    // 7. Операция присваивания с перемещением
    Vector& operator=(Vector&& other) noexcept;

    // 8. Перегрузка операции обращения по индексу []
    int& operator[](int index);
    const int& operator[](int index) const;

    // 9. Индивидуальная операция Варианта 15:
    // Побитовая операция XOR (^) с двумя векторами одинаковой размерности
    Vector operator^(const Vector& other) const;

    // Геттеры
    int getSize() const;
    const int* getData() const;

    // Операторы потокового ввода/вывода
    friend std::ostream& operator<<(std::ostream& os, const Vector& vec);
    friend std::istream& operator>>(std::istream& is, Vector& vec);
};

#endif // VECTOR_HPP
