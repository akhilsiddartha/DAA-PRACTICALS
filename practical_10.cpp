#include <iostream>
#include <algorithm>
using namespace std;

struct Edge
{
    int u, v, w;
};

bool compare(Edge a, Edge b)
{
    return a.w < b.w;
}

int parent[10];

int find(int x)
{
    if (parent[x] == x)
        return x;
    return find(parent[x]);
}

int main()
{
    int n, e;

    cout << "Enter number of vertices: ";
    cin >> n;

    cout << "Enter number of edges: ";
    cin >> e;

    Edge edges[20];

    cout << "Enter edges (u v weight):\n";
    for (int i = 0; i < e; i++)
        cin >> edges[i].u >> edges[i].v >> edges[i].w;

    for (int i = 0; i < n; i++)
        parent[i] = i;

    sort(edges, edges + e, compare);

    int total = 0, count = 0;

    cout << "Edges in Minimum Spanning Tree:\n";

    for (int i = 0; i < e && count < n - 1; i++)
    {
        int a = find(edges[i].u);
        int b = find(edges[i].v);

        if (a != b)
        {
            cout << edges[i].u << " - "
                 << edges[i].v << " = "
                 << edges[i].w << endl;

            total += edges[i].w;
            parent[a] = b;
            count++;
        }
    }

    cout << "Minimum cost = " << total;

    return 0;
}