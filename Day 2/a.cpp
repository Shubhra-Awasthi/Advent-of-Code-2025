#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void invalid(ll &a, ll &b, ll &cnt)
{
    for (ll i = a; i <= b; i++)
    {
        string s = to_string(i);
        int n = s.size();

        if (n & 1)
            continue;
        if (s.substr(0, n / 2) == s.substr(n / 2))
            cnt += i;
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    ifstream infile("input.txt");
    string line;
    getline(infile, line);

    ll cnt = 0;

    string range;
    stringstream ss(line);

    while (getline(ss, range, ','))
    {
        int dash = range.find('-');
        ll a = stoll(range.substr(0, dash));
        ll b = stoll(range.substr(dash + 1));

        invalid(a, b, cnt);
    }

    cout << cnt << "\n";
    return 0;
}