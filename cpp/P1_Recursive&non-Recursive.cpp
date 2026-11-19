#include <iostream>

unsigned long long recursiveFactorial(int n) {
    if (n <= 1) {
        return 1;
    }

    return n * recursiveFactorial(n - 1);
}

unsigned long long iterativeFactorial(int n) {
    unsigned long long result = 1;
    for (int factor = 2; factor <= n; ++factor) {
        result *= factor;
    }
    return result;
}

int main() {
    int n;
    std::cout << "Enter a non-negative integer: ";
    if (!(std::cin >> n)) {
        std::cout << "Enter a valid integer.\n";
        return 0;
    }
    if (n < 0) {
        std::cout << "Factorial is undefined for negative integers.\n";
        return 0;
    }
    if (n > 20) {
        std::cout << "Enter a number from 0 to 20 for a 64-bit factorial.\n";
        return 0;
    }

    std::cout << "Recursive factorial: " << recursiveFactorial(n) << '\n';
    std::cout << "Iterative factorial: " << iterativeFactorial(n) << '\n';
    std::cout << "Recursive: O(n) time, O(n) auxiliary space\n";
    std::cout << "Iterative: O(n) time, O(1) auxiliary space\n";
}
