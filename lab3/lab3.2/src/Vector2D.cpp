#include "Vector2D.hpp"
#include <cmath>
#include <iomanip>

Vector2D::Vector2D(double x, double y) : x(x), y(y) {}

double Vector2D::getX() const {
    return x;
}

double Vector2D::getY() const {
    return y;
}

void Vector2D::setX(double newX) {
    x = newX;
}

void Vector2D::setY(double newY) {
    y = newY;
}

double Vector2D::length() const {
    return std::sqrt(x * x + y * y);
}

void Vector2D::print(std::ostream& os) const {
    os << "Вектор 2D: Координаты = (" << std::fixed << std::setprecision(2) << x << ", " << y << ")"
       << " | Длина = " << std::setprecision(4) << length();
}
