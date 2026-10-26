#ifndef VECTOR3D_HPP
#define VECTOR3D_HPP

#include "Vector2D.hpp"
#include <iostream>

class Vector3D : public Vector2D {
protected:
    double z;

public:
    Vector3D(double x = 0.0, double y = 0.0, double z = 0.0);
    ~Vector3D() override = default;

    double getZ() const;
    void setZ(double z);

    double length() const override;
    void print(std::ostream& os = std::cout) const override;
};

#endif
