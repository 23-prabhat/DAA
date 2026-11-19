def merge(arr, left, mid, right):
    left_half = arr[left:mid + 1]
    right_half = arr[mid + 1:right + 1]
    i = 0
    j = 0
    k = left
    while i < len(left_half) and j < len(right_half):
        if left_half[i] <= right_half[j]:
            arr[k] = left_half[i]
            i += 1
        else:
            arr[k] = right_half[j]
            j += 1
        k += 1
    while i < len(left_half):
        arr[k] = left_half[i]
        i += 1
        k += 1
    while j < len(right_half):
        arr[k] = right_half[j]
        j += 1
        k += 1


def merge_sort(arr, left, right):
    if left >= right:
        return
    mid = left + (right - left) // 2
    merge_sort(arr, left, mid)
    merge_sort(arr, mid + 1, right)
    merge(arr, left, mid, right)


def main():
    try:
        n = int(input("Enter the size of the array: "))
    except (EOFError, ValueError):
        n = -1

    if n < 0:
        print("Enter a non-negative array size.")
        return

    print("Enter the elements separated by spaces: ", end="", flush=True)
    try:
        arr = list(map(int, input().split())) if n else []
    except (EOFError, ValueError):
        arr = []

    if len(arr) != n:
        print("Enter the requested number of integers.")
        return

    merge_sort(arr, 0, n - 1)
    print("Sorted array:", *arr)


if __name__ == "__main__":
    main()
