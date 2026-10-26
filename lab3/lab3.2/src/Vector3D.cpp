#include "Vector3D.hpp"
#include <cmath>
#include <iomanip>

Vector3D::Vector3D(double x, double y, double z) : Vector2D(x, y), z(z) {}

double Vector3D::getZ() const {
    return z;
}

void Vector3D::setZ(double newZ) {
    z = newZ;
}

// Внутри переопределенной функции вызывается соответствующая функция из базового класса
double Vector3D::length() const {
    double len2D = Vector2D::length();
    return std::sqrt(len2D * len2D + z * z);
}

// Внутри переопределенной функции печати вызывается функция из базового класса
void Vector3D::print(std::ostream& os) const {
    os << "Вектор 3D: Координаты = (" << std::fixed << std::setprecision(2) << x << ", " << y << ", " << z << ")"
       << " | Длина 3D = " << std::setprecision(4) << length()
       << " [базовая длина 2D: " << Vector2D::length() << "]";
}
