def floyd_warshall(graph):
    vertices = len(graph)
    distance = [row[:] for row in graph]

    for vertex in range(vertices):
        distance[vertex][vertex] = min(distance[vertex][vertex], 0)

    for k in range(vertices):
        for i in range(vertices):
            for j in range(vertices):
                distance[i][j] = min(distance[i][j], distance[i][k] + distance[k][j])

    if any(distance[vertex][vertex] < 0 for vertex in range(vertices)):
        raise ValueError("The graph contains a negative weight cycle")

    return distance


if __name__ == "__main__":
    inf = float("inf")
    graph = [
        [0, 2, 1, inf, inf, inf],
        [inf, 0, inf, 2, 3, inf],
        [inf, inf, 0, 6, 7, inf],
        [inf, inf, inf, 0, inf, 1],
        [inf, inf, inf, inf, 0, 2],
        [inf, inf, inf, inf, inf, 0],
    ]
    distance = floyd_warshall(graph)

    print("All pairs shortest path distances:")
    for row in distance:
        print(" ".join(f"{value:>5}" if value != inf else "  INF" for value in row))
