from collections import deque
from math import inf


def multistage_shortest_path(graph, source, destination):
    indegree = [0] * len(graph)
    for edges in graph:
        for vertex, _ in edges:
            indegree[vertex] += 1

    queue = deque(vertex for vertex, degree in enumerate(indegree) if degree == 0)
    order = []
    while queue:
        vertex = queue.popleft()
        order.append(vertex)
        for neighbor, _ in graph[vertex]:
            indegree[neighbor] -= 1
            if indegree[neighbor] == 0:
                queue.append(neighbor)

    if len(order) != len(graph):
        raise ValueError("A multistage graph must be acyclic")

    cost = [inf] * len(graph)
    next_vertex = [None] * len(graph)
    cost[destination] = 0

    for vertex in reversed(order):
        for neighbor, weight in graph[vertex]:
            candidate = weight + cost[neighbor]
            if candidate < cost[vertex]:
                cost[vertex] = candidate
                next_vertex[vertex] = neighbor

    if cost[source] == inf:
        return inf, []

    path = [source]
    while path[-1] != destination:
        path.append(next_vertex[path[-1]])

    return cost[source], path


if __name__ == "__main__":
    graph = [
        [(1, 2), (2, 1)],
        [(3, 2), (4, 3)],
        [(3, 6), (4, 7)],
        [(5, 1)],
        [(5, 2)],
        [],
    ]
    source = 0
    destination = 5

    distance, path = multistage_shortest_path(graph, source, destination)
    if path:
        print("Shortest distance:", distance)
        print("Shortest path:", " -> ".join(map(str, path)))
    else:
        print("No path exists")
