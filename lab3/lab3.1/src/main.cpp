#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include "Vector.hpp"

int main() {
    std::cout << "========================================================\n";
    std::cout << "  Лабораторная работа №3. Часть 1. Классы и перегрузка\n";
    std::cout << "  Вариант №15: Побитовая операция XOR (^) для Vector<int>\n";
    std::cout << "========================================================\n\n";

    // 1. Открытие файлов ввода/вывода
    std::ifstream fin("input.txt");
    if (!fin.is_open()) {
        std::cerr << "Ошибка: не удалось открыть входной файл input.txt\n";
        return 1;
    }

    std::ofstream fout("output.txt");
    if (!fout.is_open()) {
        std::cerr << "Ошибка: не удалось открыть выходной файл output.txt\n";
        return 1;
    }

    fout << "========================================================\n";
    fout << "  Лабораторная работа №3. Часть 1. Отчет о работе\n";
    fout << "  Вариант №15: Побитовая операция XOR (^) для Vector<int>\n";
    fout << "========================================================\n\n";

    // 2. Демонстрация чтения из потока (operator>>)
    std::cout << "[1] Чтение векторов из файла input.txt через operator>>:\n";
    fout << "[1] Чтение векторов из файла input.txt через operator>>:\n";

    Vector v1, v2;
    fin >> v1 >> v2;
    fin.close();

    std::cout << "  Вектор 1 (v1): " << v1 << "\n";
    std::cout << "  Вектор 2 (v2): " << v2 << "\n\n";
    fout << "  Вектор 1 (v1): " << v1 << "\n";
    fout << "  Вектор 2 (v2): " << v2 << "\n\n";

    // 3. Демонстрация индивидуальной операции Варианта 15: v1 ^ v2
    std::cout << "[2] Выполнение операции побитового XOR (v1 ^ v2):\n";
    fout << "[2] Выполнение операции побитового XOR (v1 ^ v2):\n";

    Vector v_xor = v1 ^ v2;
    std::cout << "  Результат (v_xor = v1 ^ v2): " << v_xor << "\n";
    fout << "  Результат (v_xor = v1 ^ v2): " << v_xor << "\n";

    std::cout << "  Поэлементная проверка:\n";
    fout << "  Поэлементная проверка:\n";
    for (int i = 0; i < v1.getSize(); ++i) {
        int a = v1[i];
        int b = v2[i];
        int c = v_xor[i];
        std::cout << "    Индекс " << i << ": " << a << " ^ " << b << " = " << c << "\n";
        fout << "    Индекс " << i << ": " << a << " ^ " << b << " = " << c << "\n";
    }
    std::cout << "\n";
    fout << "\n";

    // 4. Демонстрация конструктора на основе массива
    std::cout << "[3] Создание вектора на основе обычного C-массива:\n";
    fout << "[3] Создание вектора на основе обычного C-массива:\n";
    int rawArr[] = {10, 20, 30, 40, 50};
    Vector v_arr(rawArr, 5);
    std::cout << "  v_arr: " << v_arr << "\n\n";
    fout << "  v_arr: " << v_arr << "\n\n";

    // 5. Демонстрация обращения по индексу []
    std::cout << "[4] Демонстрация оператора индексирования []:\n";
    fout << "[4] Демонстрация оператора индексирования []:\n";
    std::cout << "  До изменения v_arr[2] = " << v_arr[2] << "\n";
    fout << "  До изменения v_arr[2] = " << v_arr[2] << "\n";
    v_arr[2] = 999;
    std::cout << "  После v_arr[2] = 999: " << v_arr << "\n\n";
    fout << "  После v_arr[2] = 999: " << v_arr << "\n\n";

    // 6. Демонстрация разницы между конструктором копирования и перемещения
    std::cout << "[5] Конструктор копирования vs Конструктор перемещения:\n";
    fout << "[5] Конструктор копирования vs Конструктор перемещения:\n";

    // Копирование
    Vector v_source(rawArr, 5);
    std::cout << "  Исходный объект v_source: " << v_source << " (data = " << v_source.getData() << ")\n";
    fout << "  Исходный объект v_source: " << v_source << " (data = " << v_source.getData() << ")\n";

    Vector v_copy(v_source); // Copy constructor
    std::cout << "  После копирования v_copy(v_source):\n";
    std::cout << "    v_source: " << v_source << " (data = " << v_source.getData() << ")\n";
    std::cout << "    v_copy  : " << v_copy << " (data = " << v_copy.getData() << " - выделена новая память)\n";
    fout << "  После копирования v_copy(v_source):\n";
    fout << "    v_source: " << v_source << " (data = " << v_source.getData() << ")\n";
    fout << "    v_copy  : " << v_copy << " (data = " << v_copy.getData() << " - выделена новая память)\n";

    // Перемещение
    Vector v_move(std::move(v_source)); // Move constructor
    std::cout << "  После перемещения v_move(std::move(v_source)):\n";
    std::cout << "    v_source: " << v_source << " (ресурс отдан, data = " << v_source.getData() << ")\n";
    std::cout << "    v_move  : " << v_move << " (получил исходный указатель = " << v_move.getData() << ")\n\n";
    fout << "  После перемещения v_move(std::move(v_source)):\n";
    fout << "    v_source: " << v_source << " (ресурс отдан, data = " << v_source.getData() << ")\n";
    fout << "    v_move  : " << v_move << " (получил исходный указатель = " << v_move.getData() << ")\n\n";

    // 7. Демонстрация присваивания с копированием и перемещением
    std::cout << "[6] Присваивание с копированием vs Присваивание с перемещением:\n";
    fout << "[6] Присваивание с копированием vs Присваивание с перемещением:\n";

    Vector v_target1, v_target2;
    Vector v_for_assign(rawArr, 5);

    // Присваивание с копированием
    v_target1 = v_for_assign;
    std::cout << "  После присваивания с копированием (v_target1 = v_for_assign):\n";
    std::cout << "    v_for_assign: " << v_for_assign << " (data = " << v_for_assign.getData() << ")\n";
    std::cout << "    v_target1   : " << v_target1 << " (data = " << v_target1.getData() << ")\n";
    fout << "  После присваивания с копированием (v_target1 = v_for_assign):\n";
    fout << "    v_for_assign: " << v_for_assign << " (data = " << v_for_assign.getData() << ")\n";
    fout << "    v_target1   : " << v_target1 << " (data = " << v_target1.getData() << ")\n";

    // Присваивание с перемещением
    v_target2 = std::move(v_for_assign);
    std::cout << "  После присваивания с перемещением (v_target2 = std::move(v_for_assign)):\n";
    std::cout << "    v_for_assign: " << v_for_assign << " (ресурс перемещен, data = " << v_for_assign.getData() << ")\n";
    std::cout << "    v_target2   : " << v_target2 << " (data = " << v_target2.getData() << ")\n\n";
    fout << "  После присваивания с перемещением (v_target2 = std::move(v_for_assign)):\n";
    fout << "    v_for_assign: " << v_for_assign << " (ресурс перемещен, data = " << v_for_assign.getData() << ")\n";
    fout << "    v_target2   : " << v_target2 << " (data = " << v_target2.getData() << ")\n\n";

    // 8. Демонстрация обработки исключительной ситуации (несовпадение размерностей)
    std::cout << "[7] Проверка обработки ошибок (разные размерности для XOR):\n";
    fout << "[7] Проверка обработки ошибок (разные размерности для XOR):\n";
    Vector v_small(2, 5);
    try {
        std::cout << "  Попытка выполнить: v1 (размер " << v1.getSize() 
                  << ") ^ v_small (размер " << v_small.getSize() << ")...\n";
        fout << "  Попытка выполнить: v1 (размер " << v1.getSize() 
             << ") ^ v_small (размер " << v_small.getSize() << ")...\n";
        Vector bad = v1 ^ v_small;
        (void)bad;
    } catch (const std::exception& e) {
        std::cout << "  Успешно перехвачено исключение: " << e.what() << "\n\n";
        fout << "  Успешно перехвачено исключение: " << e.what() << "\n\n";
    }

    fout.close();
    std::cout << "Все результаты успешно сохранены в файл output.txt\n";
    return 0;
}
