// return when dsu size = n

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

    int Union(int u, int v)
    {
        u = find(u);
        v = find(v);

        if (u == v)
            return size[u];
        if (size[v] > size[u])
            swap(u, v);

        parent[v] = u;
        size[u] += size[v];
        return size[u];
    }
};

int main()
{
    input();

    DSU dsu(n);
    ll ans = 0;

    while (!dist.empty())
    {
        auto [d, u, v] = dist.top();
        dist.pop();

        ll Size = dsu.Union(u, v);
        if (Size == n)
        {
            ans = 1ll * nodes[u][0] * nodes[v][0];
            break;
        }
    }

    cout << ans << endl;
    return 0;
}