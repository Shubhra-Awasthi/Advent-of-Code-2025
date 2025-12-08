/*
n^2 loop to get all edges distances
store edges in a min heap with distance and nodes
use dsu to connect junctions
*/

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

vector<vector<int>> nodes;
priority_queue<tuple<ll, int, int>, vector<tuple<ll, int, int>>, greater<tuple<ll, int, int>>> dist;
int n;

void input()
{
    ifstream in("input.txt");

    string line;
    while (getline(in, line))
    {
        stringstream ss(line);
        string cords;
        vector<int> node;

        while (getline(ss, cords, ','))
            node.push_back(stoi(cords));

        nodes.push_back(node);
    }

    n = nodes.size();
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            ll x = (nodes[i][0] - nodes[j][0]);
            ll y = (nodes[i][1] - nodes[j][1]);
            ll z = (nodes[i][2] - nodes[j][2]);

            ll d = (x * x + y * y + z * z);
            dist.push({d, i, j});
        }
    }
}

// dsu
class DSU
{
public:
    vector<int> parent, size;

    DSU(int n)
    {
        parent.resize(n);
        size.resize(n, 1);
        iota(parent.begin(), parent.end(), 0);
    }

    int find(int u)
    {
        if (parent[u] == u)
            return u;
        return parent[u] = find(parent[u]);
    }

    bool Union(int u, int v)
    {
        u = find(u);
        v = find(v);

        if (u == v)
            return false;
        if (size[v] > size[u])
            swap(u, v);

        parent[v] = u;
        size[u] += size[v];
        return true;
    }
};

int main()
{
    input();

    DSU dsu(n);

    int k = 1000;
    while (k--)
    {
        auto [d, u, v] = dist.top();
        dist.pop();

        dsu.Union(u, v);
    }

    ll total = 1;
    vector<int> vis(n, 0), comp;

    // all comp sizes
    for (int i = 0; i < n; i++)
    {
        int par = dsu.find(i);
        if (vis[par])
            continue;

        vis[par] = 1;
        comp.push_back(dsu.size[par]);
        // cout << "Component of size " << dsu.size[par] << endl;
    }

    sort(comp.begin(), comp.end(), greater<int>());
    // top 3
    for (int i = 0; i < min(3, (int)comp.size()); i++)
    {
        total *= comp[i];
        // cout << "Component of size " << comp[i] << endl;
    }

    cout << total << endl;
    return 0;
}