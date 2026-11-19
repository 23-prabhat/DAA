def fractional_knapsack(items, capacity):
    ordered_items = sorted(items, key=lambda item: item[0] / item[1], reverse=True)
    total_value = 0.0

    for value, weight in ordered_items:
        if capacity == 0:
            break

        amount = min(weight, capacity)
        total_value += amount * value / weight
        capacity -= amount

    return total_value


if __name__ == "__main__":
    items = [(60, 10), (100, 20), (120, 30)]
    capacity = 50
    print(f"Maximum value: {fractional_knapsack(items, capacity):.2f}")
