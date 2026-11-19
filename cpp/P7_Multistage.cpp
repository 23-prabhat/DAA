#include <iostream>
#include <limits>
#include <queue>
#include <stdexcept>
#include <utility>
#include <vector>

using Graph = std::vector<std::vector<std::pair<int, int>>>;

std::pair<long long, std::vector<int>> multistageShortestPath(
    const Graph& graph, int source, int destination) {
    std::vector<int> indegree(graph.size(), 0);
    for (const auto& edges : graph) {
        for (const auto& edge : edges) {
            ++indegree[edge.first];
        }
    }

    std::queue<int> ready;
    for (int vertex = 0; vertex < static_cast<int>(graph.size()); ++vertex) {
        if (indegree[vertex] == 0) {
            ready.push(vertex);
        }
    }

    std::vector<int> order;
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
        throw std::invalid_argument("A multistage graph must be acyclic");
    }

    constexpr auto infinity = std::numeric_limits<long long>::max();
    std::vector<long long> cost(graph.size(), infinity);
    std::vector<int> nextVertex(graph.size(), -1);
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

    std::vector<int> path = {source};
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

    auto [distance, path] = multistageShortestPath(graph, 0, 5);
    if (path.empty()) {
        std::cout << "No path exists\n";
        return 0;
    }

    std::cout << "Shortest distance: " << distance << '\n';
    std::cout << "Shortest path: " << path.front();
    for (std::size_t index = 1; index < path.size(); ++index) {
        std::cout << " -> " << path[index];
    }
    std::cout << '\n';
}
