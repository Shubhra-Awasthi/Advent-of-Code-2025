#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int n;
unordered_map<string, list<string>> adj;

void input()
{
    ifstream in("input.txt");

    string line;
    while (getline(in, line))
    {
        stringstream ss(line);

        string start;
        getline(ss, start, ':');

        string edge;
        while (ss >> edge)
        {
            if (edge.empty())
                continue;
            adj[start].push_back(edge);
        }
    }

    in.close();
}

int main()
{
    input();

    ll cnt = 0;
    queue<string> q;
    q.push("you");

    // bfs
    while (q.size())
    {
        string node = q.front();
        q.pop();

        // cout << "Visiting: " << node << endl;

        if (node == "out")
        {
            cnt++;
            continue;
        }

        for (auto &edge : adj[node])
            q.push(edge);
    }

    cout << cnt << endl;
    return 0;
}