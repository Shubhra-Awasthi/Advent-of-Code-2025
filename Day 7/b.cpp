// dp count total paths

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

vector<vector<char>> grid;
int n, m;
int x, y;

void input()
{
    ifstream file("input.txt");

    string line;
    while (getline(file, line))
    {
        vector<char> row;
        for (char c : line)
        {
            row.push_back(c);
        }
        grid.push_back(row);
    }

    n = grid.size();
    m = grid[0].size();

    for (int j = 0; j < m; j++)
        if (grid[0][j] == 'S')
            x = 0, y = j;
}

int main()
{
    input();

    vector<ll> cur(m, 0), nxt(m, 0);
    cur[y] = 1;

    for (int r = 0; r < n - 1; r++)
    {
        fill(nxt.begin(), nxt.end(), 0);

        for (int c = 0; c < m; c++)
        {
            if (cur[c] == 0)
                continue;

            ll ways = cur[c];
            int r1 = r + 1;

            if (grid[r1][c] == '^')
            {
                if (c - 1 >= 0)
                    nxt[c - 1] += ways;
                if (c + 1 < m)
                    nxt[c + 1] += ways;
            }
            else
                nxt[c] += ways;
        }

        cur = nxt;
    }

    cout << accumulate(cur.begin(), cur.end(), 0LL) << endl;
    return 0;
}
