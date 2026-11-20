def kruskal(vertices, edges):
    parent = list(range(vertices))
    rank = [0] * vertices
    mst = []
    total_weight = 0

    def find(vertex):
        if parent[vertex] != vertex:
            parent[vertex] = find(parent[vertex])
        return parent[vertex]

    for u, v, weight in sorted(edges, key=lambda edge: edge[2]):
        root_u = find(u)
        root_v = find(v)
        if root_u == root_v:
            continue
        if rank[root_u] < rank[root_v]:
            root_u, root_v = root_v, root_u
        parent[root_v] = root_u
        if rank[root_u] == rank[root_v]:
            rank[root_u] += 1
        mst.append((u, v, weight))
        total_weight += weight
        if len(mst) == vertices - 1:
            break
    if len(mst) != max(0, vertices - 1):
        raise ValueError("The graph is disconnected")

    return mst, total_weight


if __name__ == "__main__":
    vertices = 4
    edges = [(0, 1, 10), (0, 2, 6), (0, 3, 5), (1, 3, 15), (2, 3, 4)]

    mst, total_weight = kruskal(vertices, edges)

    print("Edges in the minimum spanning tree:")
    for u, v, weight in mst:
        print(f"{u} - {v}: {weight}")
    print("Total weight:", total_weight)
