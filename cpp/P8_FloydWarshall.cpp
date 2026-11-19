#include <algorithm>
#include <iomanip>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <vector>

constexpr int noEdge = std::numeric_limits<int>::max();
constexpr auto infinity = std::numeric_limits<long long>::max();

std::vector<std::vector<long long>> floydWarshall(
    const std::vector<std::vector<int>>& graph) {
    const int vertices = static_cast<int>(graph.size());
    std::vector<std::vector<long long>> distance(
        vertices, std::vector<long long>(vertices, infinity));

    for (int from = 0; from < vertices; ++from) {
        for (int to = 0; to < vertices; ++to) {
            if (graph[from][to] != noEdge) {
                distance[from][to] = graph[from][to];
            }
        }
        distance[from][from] = std::min(distance[from][from], 0LL);
        if (distance[from][from] < 0) {
            throw std::invalid_argument("The graph contains a negative weight cycle");
        }
    }

    for (int via = 0; via < vertices; ++via) {
        for (int from = 0; from < vertices; ++from) {
            if (distance[from][via] == infinity) {
                continue;
            }

            for (int to = 0; to < vertices; ++to) {
                if (distance[via][to] == infinity) {
                    continue;
                }

                long long candidate = distance[from][via] + distance[via][to];
                if (candidate < distance[from][to]) {
                    if (from == to && candidate < 0) {
                        throw std::invalid_argument("The graph contains a negative weight cycle");
                    }
                    distance[from][to] = candidate;
                }
            }
        }
    }

    return distance;
}

int main() {
    const std::vector<std::vector<int>> graph = {
        {0, 2, 1, noEdge, noEdge, noEdge},
        {noEdge, 0, noEdge, 2, 3, noEdge},
        {noEdge, noEdge, 0, 6, 7, noEdge},
        {noEdge, noEdge, noEdge, 0, noEdge, 1},
        {noEdge, noEdge, noEdge, noEdge, 0, 2},
        {noEdge, noEdge, noEdge, noEdge, noEdge, 0},
    };

    const auto distance = floydWarshall(graph);
    std::cout << "All pairs shortest path distances:\n";
    for (const auto& row : distance) {
        for (std::size_t column = 0; column < row.size(); ++column) {
            if (column != 0) {
                std::cout << ' ';
            }
            std::cout << std::setw(5);
            if (row[column] == infinity) {
                std::cout << "INF";
            } else {
                std::cout << row[column];
            }
        }
        std::cout << '\n';
    }
}
