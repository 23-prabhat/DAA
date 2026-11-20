#include <bits/stdc++.h>
using namespace std;

struct Item {
    int value;
    int weight;
};

double fractionalKnapsack(vector<Item> items, int capacity) {
    sort(items.begin(), items.end(), [](const Item& first, const Item& second) {
        return 1LL * first.value * second.weight > 1LL * second.value * first.weight;
    });

    double totalValue = 0;
    for (const auto& item : items) {
        if (capacity == 0) {
            break;
        }

        int amount = min(item.weight, capacity);
        totalValue += static_cast<double>(amount) * item.value / item.weight;
        capacity -= amount;
    }

    return totalValue;
}

int main() {
    const vector<Item> items = {{60, 10}, {100, 20}, {120, 30}};
    const int capacity = 50;

    cout << fixed << setprecision(2);
    cout << "Maximum value: " << fractionalKnapsack(items, capacity) << '\n';
}
