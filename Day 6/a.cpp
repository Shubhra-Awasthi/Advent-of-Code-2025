#include <bits/stdc++.h>
using namespace std;
using ll = long long;

vector<vector<int>> nums;
vector<int> ops;
int n, m;

void input()
{
    ifstream fin("input.txt");
    string line;

    // Read all lines
    vector<string> lines;
    while (getline(fin, line))
    {
        if (!line.empty())
            lines.push_back(line);
    }

    // Last line = operators line
    string opLine = lines.back();
    lines.pop_back();

    // Parse all number lines
    for (string &s : lines)
    {
        stringstream ss(s);
        vector<int> row;
        int x;
        while (ss >> x)
        {
            row.push_back(x);
        }
        nums.push_back(row);
    }

    // Parse operators
    for (char c : opLine)
    {
        if (c == '*')
            ops.push_back(0);
        if (c == '+')
            ops.push_back(1);
    }

    m = nums.size();
    n = nums[0].size();
}

vector<vector<int>> transpose(const vector<vector<int>> &a)
{
    if (a.empty())
        return {};

    int x = a.size();
    int y = a[0].size();

    vector<vector<int>> t(y, vector<int>(x));

    for (int i = 0; i < x; i++)
    {
        for (int j = 0; j < y; j++)
        {
            t[j][i] = a[i][j];
        }
    }

    return t;
}

int main()
{
    input();
    nums = transpose(nums);

    ll sum = 0;
    for (int i = 0; i < n; i++)
    {
        ll cur = nums[i][0];

        for (int j = 1; j < m; j++)
        {
            if (ops[i] == 0)
                cur *= nums[i][j];
            else
                cur += nums[i][j];
        }

        sum += cur;
        // cout << cur << "\n";
    }

    cout << sum << "\n";
    return 0;
}