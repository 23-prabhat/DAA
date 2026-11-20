#include <bits/stdc++.h>
using namespace std;

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
    const int n = 5;

    if (n < 0) {
        cout << "Factorial is undefined for negative integers.\n";
        return 0;
    }
    if (n > 20) {
        cout << "Enter a number from 0 to 20 for a 64-bit factorial.\n";
        return 0;
    }

    cout << "Recursive factorial: " << recursiveFactorial(n) << '\n';
    cout << "Iterative factorial: " << iterativeFactorial(n) << '\n';
    cout << "Recursive: O(n) time, O(n) auxiliary space\n";
    cout << "Iterative: O(n) time, O(1) auxiliary space\n";
}
