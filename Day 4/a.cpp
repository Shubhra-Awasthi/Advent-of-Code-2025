#include <bits/stdc++.h>
using namespace std;

vector<vector<char>> lines;

void input()
{
    ifstream file("input.txt");

    string line;
    while (file >> line)
    {
        vector<char> temp;
        for (char c : line)
            temp.push_back(c);
        lines.push_back(temp);
    }

    file.close();
}

int dir[8][2] = {{0, 1}, {1, 0}, {-1, 0}, {0, -1}, {1, -1}, {-1, 1}, {1, 1}, {-1, -1}};

void brute(int n, int m, int &cnt)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (lines[i][j] == '.')
                continue;

            int adj = 0;

            for (int k = 0; k < 8; k++)
            {
                int x = i + dir[k][0];
                int y = j + dir[k][1];

                if (x < 0 || y < 0 || x >= n || y >= m || lines[x][y] == '.')
                    continue;

                adj++;
            }

            if (adj < 4)
            {
                cnt++;
                // cout << "Valid at: " << i << j << endl;
            }
        }
    }
}

void optimal(int n, int m, int &cnt)
{
    // prefix sum
    vector<vector<int>> pref(n + 1, vector<int>(m + 1, 0));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            int val = (lines[i][j] == '.') ? 0 : 1;

            pref[i + 1][j + 1] = pref[i][j + 1] + pref[i + 1][j] - pref[i][j] + val;
        }
    }

    // adj scrolls
    auto adj = [&](int r1, int c1, int r2, int c2) -> int
    {
        r1 = max(r1, 0), c1 = max(c1, 0);
        r2 = min(r2, n - 1), c2 = min(c2, m - 1);

        return pref[r2 + 1][c2 + 1] - pref[r1][c2 + 1] - pref[r2 + 1][c1] + pref[r1][c1];
    };

    // calc ans
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (lines[i][j] == '.')
                continue;

            int neighbours = adj(i - 1, j - 1, i + 1, j + 1);

            if (neighbours - 1 < 4)
                cnt++;
        }
    }
}

int main()
{
    input();
    int n = lines.size();
    int m = lines[0].size();

    int cnt = 0;

    // brute(n,m,cnt);
    optimal(n, m, cnt);

    cout << cnt << endl;
    return 0;
}