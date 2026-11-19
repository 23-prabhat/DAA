#include <algorithm>
#include <iostream>
#include <vector>

void mergeSort(std::vector<int>& numbers, std::vector<int>& buffer,
               int left, int right) {
    if (right - left <= 1) {
        return;
    }

    int middle = left + (right - left) / 2;
    mergeSort(numbers, buffer, left, middle);
    mergeSort(numbers, buffer, middle, right);

    int first = left;
    int second = middle;
    int output = left;

    while (first < middle && second < right) {
        if (numbers[first] <= numbers[second]) {
            buffer[output++] = numbers[first++];
        } else {
            buffer[output++] = numbers[second++];
        }
    }
    while (first < middle) {
        buffer[output++] = numbers[first++];
    }
    while (second < right) {
        buffer[output++] = numbers[second++];
    }

    std::copy(buffer.begin() + left, buffer.begin() + right, numbers.begin() + left);
}

int main() {
    int size;
    std::cout << "Enter the size of the array: ";
    if (!(std::cin >> size) || size < 0) {
        std::cout << "Enter a non-negative array size.\n";
        return 0;
    }

    std::vector<int> numbers(size);
    std::cout << "Enter the elements separated by spaces: ";
    for (int& number : numbers) {
        if (!(std::cin >> number)) {
            std::cout << "Enter the requested number of integers.\n";
            return 0;
        }
    }

    std::vector<int> buffer(size);
    mergeSort(numbers, buffer, 0, size);

    std::cout << "Sorted array:";
    for (int number : numbers) {
        std::cout << ' ' << number;
    }
    std::cout << '\n';
}
