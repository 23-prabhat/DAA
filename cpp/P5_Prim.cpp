#include <bits/stdc++.h>
using namespace std;

int main() {
    const vector<vector<pair<int, int>>> graph = {
        {{1, 10}, {2, 6}, {3, 5}},
        {{0, 10}, {3, 15}},
        {{0, 6}, {3, 4}},
        {{0, 5}, {1, 15}, {2, 4}},
    };
    const int startVertex = 0;

    using Edge = tuple<int, int, int>;
    priority_queue<Edge, vector<Edge>, greater<Edge>> candidates;
    vector<bool> visited(graph.size(), false);
    vector<Edge> tree;
    long long totalWeight = 0;

    candidates.emplace(0, startVertex, -1);
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
        cout << "The graph is disconnected\n";
        return 0;
    }

    cout << "Edges in the minimum spanning tree:\n";
    for (const auto& [weight, vertex, parent] : tree) {
        cout << parent << " - " << vertex << ": " << weight << '\n';
    }
    cout << "Total weight: " << totalWeight << '\n';
}
