#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int n;
unordered_map<string, list<string>> adj;
unordered_map<string, ll> memo;

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

ll paths(string u, string target)
{
    if (u == target)
        return 1;
    if (memo.count(u))
        return memo[u];

    ll total = 0;
    for (auto &v : adj[u])
    {
        total += paths(v, target);
    }

    return memo[u] = total;
}

// dfs with memoization
ll solve(string start, string end)
{
    memo.clear();
    return paths(start, end);
}

int main()
{
    input();

    ll cnt = 0;

    // 2 paths possible: svr->fft->dac->out and svr->dac->fft->out

    // path 1
    ll svr_fft = solve("svr", "fft");
    ll fft_dac = solve("fft", "dac");
    ll dac_out = solve("dac", "out");
    ll cnt1 = svr_fft * fft_dac * dac_out;

    // path 2
    ll svr_dac = solve("svr", "dac");
    ll dac_fft = solve("dac", "fft");
    ll fft_out = solve("fft", "out");
    ll cnt2 = svr_dac * dac_fft * fft_out;

    cout << cnt1 + cnt2 << endl;
    return 0;
}