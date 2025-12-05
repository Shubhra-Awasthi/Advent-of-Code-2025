#include <bits/stdc++.h>
using namespace std;
using ll = long long;

vector<pair<ll, ll>> ranges;
vector<pair<ll, ll>> v;

void input()
{
    ifstream file("input.txt");

    string line;
    while (getline(file, line))
    {
        if (line.empty())
            break;

        ll a, b;
        char hyphen;
        stringstream ss(line);
        ss >> a >> hyphen >> b;

        ranges.push_back({a, b});
    }

    file.close();
}

int main()
{
    input();

    ll n = ranges.size();

    sort(ranges.begin(), ranges.end());

    // merge intervals
    for (ll i = 0; i < n;)
    {
        ll start = ranges[i].first;
        ll end = ranges[i].second;

        ll j = i;
        while (j < n && ranges[j].first <= end)
            end = max(end, ranges[j++].second);

        v.push_back({start, end});
        i = j;
    }

    // count fresh numbers
    ll m = v.size();
    ll cnt = 0;
    for (ll i = 0; i < m; i++)
    {
        ll start = v[i].first;
        ll end = v[i].second;

        cnt += (end - start + 1);
    }

    cout << cnt << endl;
    return 0;
}