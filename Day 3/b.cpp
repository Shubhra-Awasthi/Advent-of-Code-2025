#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main()
{
    ifstream infile("input.txt");

    string line;
    ll sum = 0;

    while (infile >> line)
    {
        auto start = line.begin();
        ll num = 0;

        for (int i = 11; i >= 0; i--)
        {
            auto it = max_element(start, line.end() - i);
            start = it + 1;

            int digit = *it - '0';
            num = num * 10 + digit;
        }

        sum += num;
        // cout << num << endl;
    }

    cout << sum << '\n';
    return 0;
}
