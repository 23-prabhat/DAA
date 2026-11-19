#include <functional>
#include <iostream>
#include <queue>
#include <tuple>
#include <utility>
#include <vector>

int main() {
    const std::vector<std::vector<std::pair<int, int>>> graph = {
        {{1, 10}, {2, 6}, {3, 5}},
        {{0, 10}, {3, 15}},
        {{0, 6}, {3, 4}},
        {{0, 5}, {1, 15}, {2, 4}},
    };

    using Edge = std::tuple<int, int, int>;
    std::priority_queue<Edge, std::vector<Edge>, std::greater<Edge>> candidates;
    std::vector<bool> visited(graph.size(), false);
    std::vector<Edge> tree;
    long long totalWeight = 0;

    candidates.emplace(0, 0, -1);
    while (!candidates.empty()) {
        auto [weight, vertex, parent] = candidates.top();
        candidates.pop();

        if (visited[vertex]) {
            continue;
        }
        visited[vertex] = true;

        if (parent != -1) {
            tree.emplace_back(weight, vertex, parent);
            totalWeight += weight;
        }
        for (const auto& [neighbor, edgeWeight] : graph[vertex]) {
            if (!visited[neighbor]) {
                candidates.emplace(edgeWeight, neighbor, vertex);
            }
        }
    }

    if (tree.size() + 1 != graph.size()) {
        std::cout << "The graph is disconnected\n";
        return 0;
    }

    std::cout << "Edges in the minimum spanning tree:\n";
    for (const auto& [weight, vertex, parent] : tree) {
        std::cout << parent << " - " << vertex << ": " << weight << '\n';
    }
    std::cout << "Total weight: " << totalWeight << '\n';
}
