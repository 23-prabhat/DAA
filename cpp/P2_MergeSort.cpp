#include <bits/stdc++.h>
using namespace std;

void mergeSort(vector<int>& numbers, vector<int>& buffer,
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

    copy(buffer.begin() + left, buffer.begin() + right, numbers.begin() + left);
}

int main() {
    vector<int> numbers = {38, 27, 43, 3, 9, 27};

    const int size = static_cast<int>(numbers.size());
    vector<int> buffer(size);
    mergeSort(numbers, buffer, 0, size);

    cout << "Sorted array:";
    for (int number : numbers) {
        cout << ' ' << number;
    }
    cout << '\n';
}
