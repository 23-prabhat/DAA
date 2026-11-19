#include <algorithm>
#include <iomanip>
#include <iostream>
#include <vector>

struct Item {
    int value;
    int weight;
};

double fractionalKnapsack(std::vector<Item> items, int capacity) {
    std::sort(items.begin(), items.end(), [](const Item& first, const Item& second) {
        return 1LL * first.value * second.weight > 1LL * second.value * first.weight;
    });

    double totalValue = 0;
    for (const auto& item : items) {
        if (capacity == 0) {
            break;
        }

        int amount = std::min(item.weight, capacity);
        totalValue += static_cast<double>(amount) * item.value / item.weight;
        capacity -= amount;
    }

    return totalValue;
}

int main() {
    const std::vector<Item> items = {{60, 10}, {100, 20}, {120, 30}};
    const int capacity = 50;

    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Maximum value: " << fractionalKnapsack(items, capacity) << '\n';
}
