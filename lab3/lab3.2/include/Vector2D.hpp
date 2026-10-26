#ifndef VECTOR2D_HPP
#define VECTOR2D_HPP

#include <iostream>

class Vector2D {
protected:
    double x;
    double y;

public:
    Vector2D(double x = 0.0, double y = 0.0);
    virtual ~Vector2D() = default;

    double getX() const;
    double getY() const;
    void setX(double x);
    void setY(double y);

    virtual double length() const;
    virtual void print(std::ostream& os = std::cout) const;
};

#endif
