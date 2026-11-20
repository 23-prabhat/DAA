#include <bits/stdc++.h>
using namespace std;

struct Node {
    char character;
    int left;
    int right;
};

void assignCodes(const vector<Node>& tree, int node, const string& code,
                 map<char, string>& codes) {
    const auto& entry = tree[node];
    if (entry.left == -1) {
        codes[entry.character] = code.empty() ? "0" : code;
        return;
    }

    assignCodes(tree, entry.left, code + '0', codes);
    assignCodes(tree, entry.right, code + '1', codes);
}

map<char, string> huffmanCodes(const map<char, int>& frequencies) {
    using Entry = pair<long long, int>;
    priority_queue<Entry, vector<Entry>, greater<Entry>> heap;
    vector<Node> tree;

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

    map<char, string> codes;
    if (!heap.empty()) {
        assignCodes(tree, heap.top().second, "", codes);
    }
    return codes;
}

int main() {
    const string text = "huffman coding";

    map<char, int> frequencies;
    for (char character : text) {
        ++frequencies[character];
    }

    const auto codes = huffmanCodes(frequencies);
    cout << "Huffman codes:\n";
    for (const auto& [character, code] : codes) {
        cout << '\'' << character << "': " << code << '\n';
    }

    cout << "Original text: " << text << '\n';
    cout << "Encoded text: ";
    for (char character : text) {
        cout << codes.at(character);
    }
    cout << '\n';
}
