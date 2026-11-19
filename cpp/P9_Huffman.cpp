#include <functional>
#include <iostream>
#include <map>
#include <queue>
#include <string>
#include <utility>
#include <vector>

struct Node {
    char character;
    int left;
    int right;
};

void assignCodes(const std::vector<Node>& tree, int node, const std::string& code,
                 std::map<char, std::string>& codes) {
    const auto& entry = tree[node];
    if (entry.left == -1) {
        codes[entry.character] = code.empty() ? "0" : code;
        return;
    }

    assignCodes(tree, entry.left, code + '0', codes);
    assignCodes(tree, entry.right, code + '1', codes);
}

std::map<char, std::string> huffmanCodes(const std::map<char, int>& frequencies) {
    using Entry = std::pair<long long, int>;
    std::priority_queue<Entry, std::vector<Entry>, std::greater<Entry>> heap;
    std::vector<Node> tree;

    for (const auto& [character, weight] : frequencies) {
        heap.emplace(weight, static_cast<int>(tree.size()));
        tree.push_back({character, -1, -1});
    }

    while (heap.size() > 1) {
        auto [leftWeight, left] = heap.top();
        heap.pop();
        auto [rightWeight, right] = heap.top();
        heap.pop();

        heap.emplace(leftWeight + rightWeight, static_cast<int>(tree.size()));
        tree.push_back({'\0', left, right});
    }

    std::map<char, std::string> codes;
    if (!heap.empty()) {
        assignCodes(tree, heap.top().second, "", codes);
    }
    return codes;
}

int main() {
    const std::string text = "huffman coding";
    std::map<char, int> frequencies;
    for (char character : text) {
        ++frequencies[character];
    }

    const auto codes = huffmanCodes(frequencies);
    std::cout << "Huffman codes:\n";
    for (const auto& [character, code] : codes) {
        std::cout << '\'' << character << "': " << code << '\n';
    }

    std::cout << "Original text: " << text << '\n';
    std::cout << "Encoded text: ";
    for (char character : text) {
        std::cout << codes.at(character);
    }
    std::cout << '\n';
}
