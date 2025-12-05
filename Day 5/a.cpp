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

    // print v
    //  for(auto &p : v)
    //      cout << p.first << " " << p.second << endl;

    ll cnt = 0;
    for (ll i = 0; i < m; i++)
    {
        ll num = nums[i];

        auto it = lower_bound(v.begin(), v.end(), make_pair(num, LLONG_MIN));
        it--;

        ll start = it->first;
        ll end = it->second;

        if (start <= num && num <= end)
            cnt++;

        // cout << start << " " << end << " " << num << endl;
    }

    cout << cnt << endl;
    return 0;
}