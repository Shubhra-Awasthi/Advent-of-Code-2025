#include <bits/stdc++.h>
using namespace std;
using ll = long long;

vector<string> lines;
string opLine;
int m = 0, width = 0;

void input()
{
    ifstream fin("input.txt");

    string line;
    vector<string> raw;

    while (getline(fin, line))
    {
        raw.push_back(line);
    }

    int last = (int)raw.size() - 1;
    while (last >= 0 && raw[last].find_first_not_of(" \t\r\n") == string::npos)
        --last;

    opLine = raw[last];
    raw.resize(last);

    for (string &s : raw)
    {
        if (s.find_first_not_of(" \t\r\n") != string::npos)
            lines.push_back(s);
    }

    m = (int)lines.size();
    width = (int)opLine.size();
    for (auto &s : lines)
        if ((int)s.size() > width)
            width = (int)s.size();

    for (auto &s : lines)
        if ((int)s.size() < width)
            s += string(width - s.size(), ' ');
    if ((int)opLine.size() < width)
        opLine += string(width - opLine.size(), ' ');
}

int main()
{
    input();

    // separator columns
    vector<bool> sep(width, false);
    for (int c = 0; c < width; ++c)
    {
        bool allSpace = true;
        for (int r = 0; r < m; ++r)
            if (lines[r][c] != ' ')
            {
                allSpace = false;
                break;
            }
        sep[c] = allSpace;
    }

    vector<pair<int, int>> problems;
    int c = 0;
    while (c < width)
    {
        while (c < width && sep[c])
            ++c;
        if (c >= width)
            break;
        int l = c;
        while (c < width && !sep[c])
            ++c;
        int r = c - 1;
        problems.emplace_back(l, r);
    }

    ll grand = 0;

    for (auto &pr : problems)
    {
        int l = pr.first, r = pr.second;

        char op = '+';
        for (int x = l; x <= r; ++x)
        {
            if (opLine[x] == '+' || opLine[x] == '*')
            {
                op = opLine[x];
                break;
            }
        }

        vector<ll> nums;
        for (int col = r; col >= l; --col)
        {
            string s;
            for (int row = 0; row < m; ++row)
            {
                char ch = lines[row][col];
                if (ch != ' ' && isdigit((unsigned char)ch))
                    s.push_back(ch);
            }
            if (!s.empty())
            {
                ll val = 0;
                for (char ch : s)
                    val = val * 10 + (ch - '0');
                nums.push_back(val);
            }
        }

        ll result = (op == '*') ? 1 : 0;
        if (op == '*')
        {
            for (ll v : nums)
                result *= v;
        }
        else
        {
            for (ll v : nums)
                result += v;
        }

        // cout << result << "\n";
        grand += result;
    }

    cout << grand << "\n";
    return 0;
}
