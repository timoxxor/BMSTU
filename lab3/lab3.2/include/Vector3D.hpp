#ifndef VECTOR3D_HPP
#define VECTOR3D_HPP

#include "Vector2D.hpp"
#include <iostream>

/**
 * @brief Производный класс «вектор в трехмерном пространстве» (Вариант 15, Часть 2)
 */
class Vector3D : public Vector2D {
protected:
    double z; ///< Дополнительная координата Z

public:
    // Конструктор инициализации полей
    Vector3D(double x = 0.0, double y = 0.0, double z = 0.0);

    // Деструктор
    ~Vector3D() override = default;

    // Геттер и сеттер для Z
    double getZ() const;
    void setZ(double z);

    // Переопределенная функция для вычисления длины вектора
    // (внутри вызывает Vector2D::length())
    double length() const override;

    // Переопределенная функция для печати полей и длины вектора
    // (внутри вызывает функцию из базового класса)
    void print(std::ostream& os = std::cout) const override;
};

#endif // VECTOR3D_HPP
