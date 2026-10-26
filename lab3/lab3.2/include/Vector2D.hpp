#ifndef VECTOR2D_HPP
#define VECTOR2D_HPP

#include <iostream>

/**
 * @brief Базовый класс «вектор на плоскости» (Вариант 15, Часть 2)
 */
class Vector2D {
protected:
    double x; ///< Координата X конца вектора (начало в точке (0, 0))
    double y; ///< Координата Y конца вектора (начало в точке (0, 0))

public:
    // Конструктор инициализации полей
    Vector2D(double x = 0.0, double y = 0.0);

    // Виртуальный деструктор для безопасного полиморфного удаления
    virtual ~Vector2D() = default;

    // Геттеры
    double getX() const;
    double getY() const;

    // Сеттеры
    void setX(double x);
    void setY(double y);

    // Функция для вычисления длины вектора
    virtual double length() const;

    // Функция для печати полей и длины вектора
    virtual void print(std::ostream& os = std::cout) const;
};

#endif // VECTOR2D_HPP
