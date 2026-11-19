def binary_search(numbers, target):
    left = 0
    right = len(numbers) - 1

    while left <= right:
        middle = left + (right - left) // 2

        if numbers[middle] == target:
            return middle
        if numbers[middle] < target:
            left = middle + 1
        else:
            right = middle - 1

    return -1


def main():
    numbers = [10, 20, 30, 40, 50, 60, 70]
    print("Sorted array:", *numbers)
    try:
        target = int(input("Enter the number to search: "))
    except (EOFError, ValueError):
        print("Enter a valid integer.")
        return

    index = binary_search(numbers, target)

    if index == -1:
        print("Number not found")
    else:
        print("Number found at index", index)


if __name__ == "__main__":
    main()
