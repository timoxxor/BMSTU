#include <iostream>
#include <vector>
#include <iomanip>
#include "Vector2D.hpp"
#include "Vector3D.hpp"

int main() {
    Vector2D v2d(3.0, 4.0);
    Vector3D v3d(1.0, 2.0, 2.0);

    std::cout << "v2d: ";
    v2d.print();
    std::cout << "\n";

    std::cout << "v3d: ";
    v3d.print();
    std::cout << "\n\n";

    std::cout << "Static polymorphism:\n";
    std::cout << "  v3d len: " << v3d.length() << "\n";
    std::cout << "  v3d base len: " << v3d.Vector2D::length() << "\n\n";

    std::cout << "Dynamic polymorphism:\n";
    Vector2D* p1 = &v2d;
    Vector2D* p2 = &v3d;
    std::cout << "  p1 (v2d): ";
    p1->print();
    std::cout << "\n";
    std::cout << "  p2 (v3d): ";
    p2->print();
    std::cout << " (len: " << p2->length() << ")\n\n";

    Vector2D obj1(6.0, 8.0);
    Vector3D obj2(2.0, 3.0, 6.0);
    Vector2D obj3(0.0, 12.0);
    Vector3D obj4(4.0, 4.0, 7.0);

    std::vector<Vector2D*> vecList = { &v2d, &v3d, &obj1, &obj2, &obj3, &obj4 };

    std::cout << "Vector list:\n";
    double totalLength = 0.0;
    for (size_t i = 0; i < vecList.size(); ++i) {
        std::cout << "  [" << i << "] ";
        vecList[i]->print();
        std::cout << "\n";
        totalLength += vecList[i]->length();
    }

    std::cout << "\nTotal length: " << std::fixed << std::setprecision(4) << totalLength << "\n";
    return 0;
}
