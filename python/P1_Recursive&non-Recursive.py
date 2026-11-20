def recursive_factorial(n):
    if n <= 1:
        return 1
    return n * recursive_factorial(n - 1)


def iterative_factorial(n):
    result = 1
    for factor in range(2, n + 1):
        result *= factor
    return result


def main():
    n = 5

    if n < 0:
        print("Factorial is undefined for negative integers.")
        return

    try:
        print("Recursive factorial:", recursive_factorial(n))
    except RecursionError:
        print("Recursive factorial exceeds Python's recursion limit.")

    print("Iterative factorial:", iterative_factorial(n))
    print("Recursive: O(n) time, O(n) auxiliary space")
    print("Iterative: O(n) time, O(1) auxiliary space")


if __name__ == "__main__":
    main()
