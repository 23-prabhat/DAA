#include <bits/stdc++.h>
using namespace std;

int binarySearch(const vector<int>& numbers, int target) {
    int left = 0;
    int right = static_cast<int>(numbers.size()) - 1;

    while (left <= right) {
        int middle = left + (right - left) / 2;

        if (numbers[middle] == target) {
            return middle;
        }
        if (numbers[middle] < target) {
            left = middle + 1;
        } else {
            right = middle - 1;
        }
    }

    return -1;
}

int main() {
    const vector<int> numbers = {10, 20, 30, 40, 50, 60, 70};
    const int target = 60;

    cout << "Sorted array:";
    for (int number : numbers) {
        cout << ' ' << number;
    }

    cout << '\n';

    int index = binarySearch(numbers, target);
    if (index == -1) {
        cout << "Number not found\n";
    } else {
        cout << "Number found at index " << index << '\n';
    }
}
