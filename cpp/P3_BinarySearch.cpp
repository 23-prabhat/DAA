#include <iostream>
#include <vector>

int binarySearch(const std::vector<int>& numbers, int target) {
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
    const std::vector<int> numbers = {10, 20, 30, 40, 50, 60, 70};
    std::cout << "Sorted array:";
    for (int number : numbers) {
        std::cout << ' ' << number;
    }

    int target;
    std::cout << "\nEnter the number to search: ";
    if (!(std::cin >> target)) {
        std::cout << "Enter a valid integer.\n";
        return 0;
    }

    int index = binarySearch(numbers, target);
    if (index == -1) {
        std::cout << "Number not found\n";
    } else {
        std::cout << "Number found at index " << index << '\n';
    }
}
