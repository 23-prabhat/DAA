from collections import Counter
from heapq import heapify, heappop, heappush
from itertools import count


def huffman_codes(frequencies):
    order = count()
    heap = [
        (frequencies[character], next(order), character)
        for character in sorted(frequencies)
    ]
    if not heap:
        return {}

    heapify(heap)
    while len(heap) > 1:
        left_weight, _, left = heappop(heap)
        right_weight, _, right = heappop(heap)
        heappush(heap, (left_weight + right_weight, next(order), (left, right)))

    codes = {}

    def assign_codes(node, code):
        if isinstance(node, str):
            codes[node] = code or "0"
        else:
            left, right = node
            assign_codes(left, code + "0")
            assign_codes(right, code + "1")

    assign_codes(heap[0][2], "")
    return codes


if __name__ == "__main__":
    text = "huffman coding"

    codes = huffman_codes(Counter(text))

    print("Huffman codes:")
    for character, code in sorted(codes.items()):
        print(f"'{character}': {code}")
    print("Original text:", text)
    print("Encoded text:", "".join(codes[character] for character in text))
