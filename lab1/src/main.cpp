#include <iostream>
#include <cmath>
#include <iomanip>

int main() {
    double a;
    std::cout << "Enter a: ";
    if (!(std::cin >> a) || a <= 0.0) {
        return 1;
    }

    double epsilons[] = {1e-2, 1e-4, 1e-6};
    double exact = std::cbrt(a);

    std::cout << std::fixed << std::setprecision(10);
    std::cout << "Exact = " << exact << "\n\n";

    for (double eps : epsilons) {
        double x_prev = a;
        double x_next = x_prev;
        int iterations = 0;

        while (true) {
            x_next = (x_prev + 2.0 * std::sqrt(a / x_prev)) / 3.0;
            iterations++;
            if (std::abs(x_next - x_prev) <= eps) {
                break;
            }
            x_prev = x_next;
        }

        std::cout << "Epsilon: " << eps << "\n";
        std::cout << "Iterations: " << iterations << "\n";
        std::cout << "Calculated x: " << x_next << "\n";
        std::cout << "Absolute difference: " << std::abs(x_next - exact) << "\n\n";
    }

    return 0;
}
