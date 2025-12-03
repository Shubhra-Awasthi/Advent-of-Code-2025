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
        auto it1 = max_element(line.begin(), line.end() - 1);
        char c1 = *it1;
        line.erase(it1);

        auto it2 = max_element(it1, line.end());
        char c2 = *it2;

        int digit1 = c1 - '0';
        int digit2 = c2 - '0';
        int num = digit1 * 10 + digit2;

        sum += num;
        // cout << digit1 <<     " " << digit2 << " " << sum << '\n';
    }

    cout << sum << '\n';
    return 0;
}
