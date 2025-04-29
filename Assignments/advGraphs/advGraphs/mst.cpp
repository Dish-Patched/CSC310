#include "mst.h"
#include "binaryHeap.h"       // Custom binary heap
#include "binomialHeap.h"   // Custom binomial heap

// ===== QuickUnion =====
QuickUnion::QuickUnion(int n) 
{
    parent.resize(n);
    for (int i = 0; i < n; ++i)
        parent[i] = i;
}

int QuickUnion::find(int x) 
{
    while (x != parent[x])
        x = parent[x];
    return x;
}

void QuickUnion::Union(int x, int y) 
{
    int rootX = find(x);
    int rootY = find(y);
    if (rootX != rootY)
        parent[rootX] = rootY;
}

// ===== UnionFind =====
UnionFind::UnionFind(int n) 
{
    parent.resize(n);
    rank.resize(n, 0);
    for (int i = 0; i < n; ++i)
        parent[i] = i;
}

int UnionFind::find(int x) 
{
    if (x != parent[x])
        parent[x] = find(parent[x]);
    return parent[x];
}

void UnionFind::Union(int x, int y) 
{
    int rootX = find(x);
    int rootY = find(y);
    if (rootX == rootY)
        return;

    if (rank[rootX] < rank[rootY])
        parent[rootX] = rootY;
    else if (rank[rootX] > rank[rootY])
        parent[rootY] = rootX;
    else {
        parent[rootY] = rootX;
        rank[rootX]++;
    }
}

// ===== MST =====
MST::MST(int vertices)
{
    n = vertices;
}

void MST::addEdge(int u, int v, int weight) 
{
    edges.push_back({u, v, weight});
}

int MST::kruskalV1() 
{
    HEAP heap((int)edges.size());  

    for (const Edge& e : edges)
        heap.insertH(e);  

    QuickUnion dsu(n);
    int mstWeight = 0;
    int edgeCount = 0;

    while (edgeCount < n - 1 && heap.getSize() > 0) {
        Edge e = heap.peek();    
        heap.deleteMin();        

        if (dsu.find(e.src) != dsu.find(e.dest)) {
            dsu.Union(e.src, e.dest);
            mstWeight += e.weight;
            edgeCount++;
        }
    }

    return (edgeCount == n - 1) ? mstWeight : -1;
}

int MST::kruskalV2() 
{
    BinomialHeap heap;

    for (const Edge& e : edges)
        heap.insert(e);

    UnionFind dsu(n);
    int mstWeight = 0;
    int edgeCount = 0;

    while (edgeCount < n - 1) {
        Edge e = heap.findMin();  
        heap.deleteMin();         

        if (dsu.find(e.src) != dsu.find(e.dest)) {
            dsu.Union(e.src, e.dest);
            mstWeight += e.weight;
            edgeCount++;
        }
    }

    return (edgeCount == n - 1) ? mstWeight : -1;
}
