#include <bits/stdc++.h>
using namespace std;
using ll = long long;

vector<pair<ll, ll>> ranges;
vector<pair<ll, ll>> v;
vector<ll> nums;

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

    while (file >> line)
    {
        nums.push_back(stoll(line));
    }

    file.close();
}

int main()
{
    input();

    ll n = ranges.size();
    ll m = nums.size();

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

    // sort querries to use two pointer
    sort(nums.begin(), nums.end());

    ll cnt = 0;
    ll j = 0;
    for (ll i = 0; i < m; i++)
    {
        ll num = nums[i];

        while (j < v.size() && num > v[j].second)
            j++;

        if (j < v.size() && num >= v[j].first && num <= v[j].second)
            cnt++;
    }

    cout << cnt << endl;
    return 0;
}