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

double Vector3D::length() const {
    double len2D = Vector2D::length();
    return std::sqrt(len2D * len2D + z * z);
}

void Vector3D::print(std::ostream& os) const {
    os << "Vector3D(" << std::fixed << std::setprecision(2) << x << ", " << y << ", " << z << ")"
       << " len: " << std::setprecision(4) << length()
       << " [2D proj: " << Vector2D::length() << "]";
}
