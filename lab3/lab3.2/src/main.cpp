#include <iostream>
#include <vector>
#include <iomanip>
#include "Vector2D.hpp"
#include "Vector3D.hpp"

// Шаблонная функция для демонстрации статического полиморфизма во время компиляции
template <typename T>
void printStatically(const T& obj, const std::string& label) {
    std::cout << "  [" << label << "] (compile-time dispatch):\n    ";
    obj.print();
    std::cout << "\n";
}

int main() {
    std::cout << "========================================================\n";
    std::cout << "  Лабораторная работа №3. Часть 2. Наследование классов\n";
    std::cout << "  Вариант №15: Базовый Vector2D и производный Vector3D\n";
    std::cout << "========================================================\n\n";

    // 1. Создание по 1 объекту каждого из классов
    std::cout << "[1] Создание отдельных объектов базового и производного классов:\n";
    Vector2D v2d(3.0, 4.0);           // Длина = sqrt(3^2 + 4^2) = 5.0
    Vector3D v3d(1.0, 2.0, 2.0);      // Длина = sqrt(1^2 + 2^2 + 2^2) = 3.0

    std::cout << "  Объект базового класса Vector2D:\n    ";
    v2d.print();
    std::cout << "\n";

    std::cout << "  Объект производного класса Vector3D:\n    ";
    v3d.print();
    std::cout << "\n\n";

    // 2. Демонстрация статического полиморфизма (раннее связывание)
    std::cout << "[2] Демонстрация статического полиморфизма (раннее связывание):\n";
    std::cout << "  а) Прямой вызов методов через конкретные типы:\n";
    printStatically(v2d, "Vector2D");
    printStatically(v3d, "Vector3D");

    std::cout << "  б) Явный вызов метода базового класса из объекта производного класса (Vector2D::length):\n";
    std::cout << "    Длина v3d в 3D пространстве: " << v3d.length() << "\n";
    std::cout << "    Длина проекции v3d на плоскость XY (через v3d.Vector2D::length()): " 
              << v3d.Vector2D::length() << "\n\n";

    // 3. Демонстрация динамического полиморфизма (позднее связывание через виртуальные методы)
    std::cout << "[3] Демонстрация динамического полиморфизма (позднее связывание):\n";
    Vector2D* polyPtr1 = &v2d;
    Vector2D* polyPtr2 = &v3d;

    std::cout << "  Указатель Vector2D* указывает на объект Vector2D:\n    ";
    polyPtr1->print();
    std::cout << "\n";

    std::cout << "  Указатель Vector2D* указывает на объект Vector3D:\n    ";
    // Благодаря ключевому слову virtual вызовется метод Vector3D::print()
    polyPtr2->print();
    std::cout << "\n    Вычисленная длина через polyPtr2->length(): " << polyPtr2->length() << "\n\n";

    // 4. Вектор указателей на объекты базового и производного классов
    std::cout << "[4] Коллекция векторов: std::vector<Vector2D*> (гетерогенный контейнер):\n";
    Vector2D obj1(6.0, 8.0);          // length = sqrt(36 + 64) = 10.0
    Vector3D obj2(2.0, 3.0, 6.0);     // length = sqrt(4 + 9 + 36) = 7.0
    Vector2D obj3(0.0, 12.0);         // length = 12.0
    Vector3D obj4(4.0, 4.0, 7.0);     // length = sqrt(16 + 16 + 49) = sqrt(81) = 9.0

    std::vector<Vector2D*> vecList = { &v2d, &v3d, &obj1, &obj2, &obj3, &obj4 };

    double totalLength = 0.0;
    std::cout << std::string(75, '-') << "\n";
    for (size_t i = 0; i < vecList.size(); ++i) {
        std::cout << "  Элемент [" << i << "]: ";
        vecList[i]->print();
        std::cout << "\n";
        totalLength += vecList[i]->length();
    }
    std::cout << std::string(75, '-') << "\n";

    std::cout << "\n[5] Суммарная длина всех векторов в коллекции:\n";
    std::cout << "  Вычисленная программой сумма длин = " << std::fixed << std::setprecision(4) 
              << totalLength << "\n";

    std::cout << "\n[6] Ручной расчет контрольного примера для проверки:\n";
    std::cout << "  1. v2d (3, 4)       -> sqrt(3^2 + 4^2) = 5.0\n";
    std::cout << "  2. v3d (1, 2, 2)    -> sqrt(1^2 + 2^2 + 2^2) = sqrt(9) = 3.0\n";
    std::cout << "  3. obj1 (6, 8)      -> sqrt(6^2 + 8^2) = 10.0\n";
    std::cout << "  4. obj2 (2, 3, 6)   -> sqrt(2^2 + 3^2 + 6^2) = sqrt(49) = 7.0\n";
    std::cout << "  5. obj3 (0, 12)     -> sqrt(0^2 + 12^2) = 12.0\n";
    std::cout << "  6. obj4 (4, 4, 7)   -> sqrt(4^2 + 4^2 + 7^2) = sqrt(81) = 9.0\n";
    std::cout << "  Ожидаемая сумма = 5.0 + 3.0 + 10.0 + 7.0 + 12.0 + 9.0 = 46.0000\n";
    std::cout << "  Совпадение результатов: " << (std::abs(totalLength - 46.0) < 1e-6 ? "УСПЕХ (100% совпадение)" : "ОШИБКА") << "\n\n";

    return 0;
}
