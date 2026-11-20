#include <bits/stdc++.h>
using namespace std;

constexpr int noEdge = numeric_limits<int>::max();
constexpr auto infinity = numeric_limits<long long>::max();

vector<vector<long long>> floydWarshall(
    const vector<vector<int>>& graph) {
    const int vertices = static_cast<int>(graph.size());
    vector<vector<long long>> distance(
        vertices, vector<long long>(vertices, infinity));

    for (int from = 0; from < vertices; ++from) {
        for (int to = 0; to < vertices; ++to) {
            if (graph[from][to] != noEdge) {
                distance[from][to] = graph[from][to];
            }
        }
        distance[from][from] = min(distance[from][from], 0LL);
        if (distance[from][from] < 0) {
            throw invalid_argument("The graph contains a negative weight cycle");
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
                        throw invalid_argument("The graph contains a negative weight cycle");
                    }
                    distance[from][to] = candidate;
                }
            }
        }
    }

    return distance;
}

int main() {
    const vector<vector<int>> graph = {
        {0, 2, 1, noEdge, noEdge, noEdge},
        {noEdge, 0, noEdge, 2, 3, noEdge},
        {noEdge, noEdge, 0, 6, 7, noEdge},
        {noEdge, noEdge, noEdge, 0, noEdge, 1},
        {noEdge, noEdge, noEdge, noEdge, 0, 2},
        {noEdge, noEdge, noEdge, noEdge, noEdge, 0},
    };

    const auto distance = floydWarshall(graph);
    cout << "All pairs shortest path distances:\n";
    for (const auto& row : distance) {
        for (size_t column = 0; column < row.size(); ++column) {
            if (column != 0) {
                cout << ' ';
            }
            cout << setw(5);
            if (row[column] == infinity) {
                cout << "INF";
            } else {
                cout << row[column];
            }
        }
        cout << '\n';
    }
}
