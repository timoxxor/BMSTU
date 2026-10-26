#include <iostream>
#include <fstream>
#include <utility>
#include "Vector.hpp"

int main() {
    std::ifstream fin("input.txt");
    if (!fin.is_open()) {
        std::cerr << "error: cannot open input.txt\n";
        return 1;
    }

    std::ofstream fout("output.txt");
    if (!fout.is_open()) {
        std::cerr << "error: cannot open output.txt\n";
        return 1;
    }

    Vector v1, v2;
    fin >> v1 >> v2;
    fin.close();

    std::cout << "v1: " << v1 << "\n";
    std::cout << "v2: " << v2 << "\n";
    fout << "v1: " << v1 << "\n";
    fout << "v2: " << v2 << "\n";

    Vector v_xor = v1 ^ v2;
    std::cout << "v1 ^ v2: " << v_xor << "\n";
    fout << "v1 ^ v2: " << v_xor << "\n";

    for (int i = 0; i < v1.getSize(); ++i) {
        std::cout << "  [" << i << "] " << v1[i] << " ^ " << v2[i] << " = " << v_xor[i] << "\n";
        fout << "  [" << i << "] " << v1[i] << " ^ " << v2[i] << " = " << v_xor[i] << "\n";
    }

    int arr[] = {10, 20, 30, 40, 50};
    Vector v_arr(arr, 5);
    std::cout << "from array: " << v_arr << "\n";
    v_arr[2] = 999;
    std::cout << "modified [2]: " << v_arr << "\n";

    Vector v_copy(v_arr);
    std::cout << "copy ctor: " << v_copy << "\n";

    Vector v_move(std::move(v_copy));
    std::cout << "move ctor: " << v_move << " (src size: " << v_copy.getSize() << ")\n";

    Vector v_assigned;
    v_assigned = v_move;
    std::cout << "copy assign: " << v_assigned << "\n";

    Vector v_move_assigned;
    v_move_assigned = std::move(v_assigned);
    std::cout << "move assign: " << v_move_assigned << " (src size: " << v_assigned.getSize() << ")\n";

    try {
        Vector small(2);
        Vector bad = v1 ^ small;
        (void)bad;
    } catch (const std::exception& e) {
        std::cout << "exception test: " << e.what() << "\n";
    }

    fout.close();
    return 0;
}
