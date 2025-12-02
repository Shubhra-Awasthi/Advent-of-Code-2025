#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void invalid(ll &a, ll &b, ll &cnt)
{
    // cout << "Range: " << a << "-" << b << "\n";
    for (ll i = a; i <= b; i++)
    {
        string s = to_string(i);
        int n = s.size();

        for (int j = 1; j <= n / 2; j++)
        {
            if (s.substr(0, j) == s.substr(j, j))
            {
                bool ok = true;

                for (int k = j; k < n; k += j)
                {
                    if (s.substr(0, j) != s.substr(k, j))
                    {
                        ok = false;
                        break;
                    }
                }

                if (ok)
                {
                    // cout << i << endl;
                    cnt += i;
                    break;
                }
            }
        }
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
