#include <bits/stdc++.h>
using namespace std;

using Graph = vector<vector<pair<int, int>>>;

pair<long long, vector<int>> multistageShortestPath(
    const Graph& graph, int source, int destination) {
    vector<int> indegree(graph.size(), 0);
    for (const auto& edges : graph) {
        for (const auto& edge : edges) {
            ++indegree[edge.first];
        }
    }

    queue<int> ready;
    for (int vertex = 0; vertex < static_cast<int>(graph.size()); ++vertex) {
        if (indegree[vertex] == 0) {
            ready.push(vertex);
        }
    }

    vector<int> order;
    while (!ready.empty()) {
        int vertex = ready.front();
        ready.pop();
        order.push_back(vertex);

        for (const auto& edge : graph[vertex]) {
            if (--indegree[edge.first] == 0) {
                ready.push(edge.first);
            }
        }
    }

    if (order.size() != graph.size()) {
        throw invalid_argument("A multistage graph must be acyclic");
    }

    constexpr auto infinity = numeric_limits<long long>::max();
    vector<long long> cost(graph.size(), infinity);
    vector<int> nextVertex(graph.size(), -1);
    cost[destination] = 0;

    for (auto it = order.rbegin(); it != order.rend(); ++it) {
        int vertex = *it;
        for (const auto& [neighbor, weight] : graph[vertex]) {
            if (cost[neighbor] != infinity && weight + cost[neighbor] < cost[vertex]) {
                cost[vertex] = weight + cost[neighbor];
                nextVertex[vertex] = neighbor;
            }
        }
    }

    if (cost[source] == infinity) {
        return {infinity, {}};
    }

    vector<int> path = {source};
    while (path.back() != destination) {
        path.push_back(nextVertex[path.back()]);
    }
    return {cost[source], path};
}

int main() {
    const Graph graph = {
        {{1, 2}, {2, 1}},
        {{3, 2}, {4, 3}},
        {{3, 6}, {4, 7}},
        {{5, 1}},
        {{5, 2}},
        {},
    };
    const int source = 0;
    const int destination = 5;

    auto [distance, path] = multistageShortestPath(graph, source, destination);
    if (path.empty()) {
        cout << "No path exists\n";
        return 0;
    }

    cout << "Shortest distance: " << distance << '\n';
    cout << "Shortest path: " << path.front();
    for (size_t index = 1; index < path.size(); ++index) {
        cout << " -> " << path[index];
    }
    cout << '\n';
}
