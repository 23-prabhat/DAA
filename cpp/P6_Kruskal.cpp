#include <algorithm>
#include <iostream>
#include <numeric>
#include <utility>
#include <vector>

struct Edge {
    int source;
    int destination;
    int weight;
};

int findRoot(int vertex, std::vector<int>& parent) {
    if (parent[vertex] != vertex) {
        parent[vertex] = findRoot(parent[vertex], parent);
    }
    return parent[vertex];
}

int main() {
    const int vertices = 4;
    std::vector<Edge> edges = {
        {0, 1, 10}, {0, 2, 6}, {0, 3, 5}, {1, 3, 15}, {2, 3, 4},
    };
    std::stable_sort(edges.begin(), edges.end(), [](const Edge& first, const Edge& second) {
        return first.weight < second.weight;
    });

    std::vector<int> parent(vertices);
    std::iota(parent.begin(), parent.end(), 0);
    std::vector<int> rank(vertices, 0);
    std::vector<Edge> tree;
    long long totalWeight = 0;

    for (const auto& edge : edges) {
        int firstRoot = findRoot(edge.source, parent);
        int secondRoot = findRoot(edge.destination, parent);
        if (firstRoot == secondRoot) {
            continue;
        }

        if (rank[firstRoot] < rank[secondRoot]) {
            std::swap(firstRoot, secondRoot);
        }
        parent[secondRoot] = firstRoot;
        if (rank[firstRoot] == rank[secondRoot]) {
            ++rank[firstRoot];
        }

        tree.push_back(edge);
        totalWeight += edge.weight;
        if (tree.size() + 1 == vertices) {
            break;
        }
    }

    if (tree.size() + 1 != vertices) {
        std::cout << "The graph is disconnected\n";
        return 0;
    }

    std::cout << "Edges in the minimum spanning tree:\n";
    for (const auto& edge : tree) {
        std::cout << edge.source << " - " << edge.destination << ": " << edge.weight << '\n';
    }
    std::cout << "Total weight: " << totalWeight << '\n';
}
