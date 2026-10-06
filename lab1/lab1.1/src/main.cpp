#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

// Function using 'while' loop (pre-condition)
void calculateWhile(double a, double eps) {
    double x_curr = a; // x_0 = a
    // Calculate initial x_1 to start the condition check
    double x_next = (1.0 / 3.0) * (x_curr + 2.0 * sqrt(a / x_curr));
    int iterations = 1;
    
    // Loop continues while the difference is greater than the allowed error
    while (abs(x_next - x_curr) > eps) {
        x_curr = x_next;
        x_next = (1.0 / 3.0) * (x_curr + 2.0 * sqrt(a / x_curr));
        iterations++;
    }
    
    cout << "While loop    | eps: " << setw(8) << eps 
         << " | result: " << fixed << setprecision(6) << x_next 
         << " | iterations: " << iterations << endl;
}

// Function using 'do-while' loop (post-condition)
void calculateDoWhile(double a, double eps) {
    double x_curr = a;
    double x_next;
    double diff;
    int iterations = 0;
    
    do {
        x_next = (1.0 / 3.0) * (x_curr + 2.0 * sqrt(a / x_curr));
        diff = abs(x_next - x_curr);
        x_curr = x_next;
        iterations++;
    } while (diff > eps);
    
    cout << "Do-while loop | eps: " << setw(8) << eps 
         << " | result: " << fixed << setprecision(6) << x_curr 
         << " | iterations: " << iterations << endl;
}

// Function using 'for' loop
void calculateFor(double a, double eps) {
    double x_curr = a;
    double x_next;
    int iterations = 0;
    
    // The loop condition is checked before each iteration
    for (double diff = eps + 1.0; diff > eps; iterations++) {
        x_next = (1.0 / 3.0) * (x_curr + 2.0 * sqrt(a / x_curr));
        diff = abs(x_next - x_curr);
        x_curr = x_next;
    }
    
    cout << "For loop      | eps: " << setw(8) << eps 
         << " | result: " << fixed << setprecision(6) << x_curr 
         << " | iterations: " << iterations << endl;
}

int main() {
    double a;
    cout << "--- Part 1: Loop Operators ---" << endl;
    cout << "Enter value a (a > 0): ";
    cin >> a;
    
    if (a <= 0) {
        cout << "Error: 'a' must be strictly greater than 0." << endl;
        return 1;
    }
    
    // Built-in function for exact value check (a^(1/3))
    double exactValue = pow(a, 1.0 / 3.0); 
    cout << "\nExact value (cbrt(a)): " << fixed << setprecision(6) << exactValue << "\n" << endl;
    
    // Array of required precisions
    double epsilons[] = {1e-2, 1e-4, 1e-6};
    
    for (double eps : epsilons) {
        calculateWhile(a, eps);
        calculateDoWhile(a, eps);
        calculateFor(a, eps);
        cout << "--------------------------------------------------------" << endl;
    }
    
    return 0;
}
