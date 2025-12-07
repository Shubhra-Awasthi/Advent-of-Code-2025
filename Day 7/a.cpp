/*
simulate the beams using bfs
when encountering a splitter, add two new directions to the queue.
Keep a set to not add duplicates to the queue
*/

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

vector<vector<char>> grid;
int n, m;
int x, y;

struct PairHash
{
    size_t operator()(const pair<int, int> &p) const noexcept
    {
        return hash<long long>()(((long long)p.first << 32) ^ p.second);
    }
};

void input()
{
    ifstream file("input.txt");

    string line;
    while (getline(file, line))
    {
        vector<char> row;
        for (char c : line)
        {
            row.push_back(c);
        }
        grid.push_back(row);
    }

    n = grid.size();
    m = grid[0].size();

    for (int j = 0; j < m; j++)
        if (grid[0][j] == 'S')
            x = 0, y = j;
}

int main()
{
    input();

    unordered_set<pair<int, int>, PairHash> vis;
    queue<pair<int, int>> q;

    ll cnt = 0;
    q.push({x, y});
    vis.insert({x, y});

    // bfs
    while (!q.empty())
    {
        auto [a, b] = q.front();
        q.pop();

        if (a + 1 >= n)
            continue;
        if (b < 0 || b >= m)
            continue;

        if (grid[a + 1][b] == '^')
        {
            // cout << "Splitter: " << a+1 << "," << b << endl;
            cnt++;

            int a1 = a + 1, b1 = b - 1;
            int a2 = a + 1, b2 = b + 1;

            if (b1 >= 0 && b1 < m)
            {
                if (!vis.count({a1, b1}))
                {
                    q.push({a1, b1});
                    vis.insert({a1, b1});
                }
            }
            if (b2 >= 0 && b2 < m)
            {
                if (!vis.count({a2, b2}))
                {
                    q.push({a2, b2});
                    vis.insert({a2, b2});
                }
            }
        }
        else
        {
            if (!vis.count({a + 1, b}))
            {
                q.push({a + 1, b});
                vis.insert({a + 1, b});
            }
        }

        vis.erase({a, b});
    }

    cout << cnt << endl;
    return 0;
}