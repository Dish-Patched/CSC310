#include "uf.h"

weightedQuickUnion::weightedQuickUnion(int n)
{
    this->n = n;
    parent = new int[n];
    size = new int[n];

    //initialize the parent and size arrays
    for(int i = 0; i < n; i++)
    {
        parent[i] = i;
        size[i] = 1;
    }
}

weightedQuickUnion::~weightedQuickUnion()
{
    delete[] parent;
    delete[] size;
}

int weightedQuickUnion::find(int p)
{
    while(p != parent[p])  // root is its own parent
    {
        parent[p] = parent[parent[p]];   // path compression
        p = parent[p];  // follow the parentuntil you reach the root
    }

    return p;
}

void weightedQuickUnion::Union(int p, int q)
{
    int rootp = find(p);
    int rootq = find(q);

    if(rootp == rootq)  // checking if p and q are already connected
        return;

    // Union by Size/Rank - make smaller tree child of larger tree
    if(size[rootp] < size[rootq])
    {
        parent[rootp] = rootq;
        // updating the size
        size[rootq] += size[rootp];
    }
    else
    {
        parent[rootq] = rootp;
        size[rootp] += size[rootq];
    }
}

bool weightedQuickUnion::connected(int p, int q)
{
    return find(p) == find(q);
}

void weightedQuickUnion::print()
{
    cout << "Parent: ";
    for(int i = 0; i < n; i++)
        cout << parent[i] << " ";

    cout << endl;
    cout << "Size:   ";
    for(int i = 0; i < n; i++)
        cout << size[i] << " ";
    cout << endl;
}