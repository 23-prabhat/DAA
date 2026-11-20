import heapq


def prim(graph, start=0):
    n = len(graph)
    if n == 0:
        return 0, []
    if not 0 <= start < n:
        raise ValueError("The starting vertex is out of range")
    visited = [False] * n
    min_heap = [(0, start, None)]
    mst_weight = 0
    mst_edges = []
    while min_heap:
        weight, u, parent = heapq.heappop(min_heap)
        if visited[u]:
            continue
        visited[u] = True
        mst_weight += weight
        if parent is not None:
            mst_edges.append((parent, u, weight))
        for v, w in graph[u]:
            if not visited[v]:
                heapq.heappush(min_heap, (w, v, u))
    if not all(visited):
        raise ValueError("The graph is disconnected")

    return mst_weight, mst_edges


if __name__ == "__main__":
    graph = [
        [(1, 10), (2, 6), (3, 5)],
        [(0, 10), (3, 15)],
        [(0, 6), (3, 4)],
        [(0, 5), (1, 15), (2, 4)],
    ]
    start_vertex = 0

    total_weight, mst = prim(graph, start_vertex)
    print("Edges in the minimum spanning tree:")
    for u, v, weight in mst:
        print(f"{u} - {v}: {weight}")
    print("Total weight:", total_weight)
