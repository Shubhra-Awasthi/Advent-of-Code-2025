#include <bits/stdc++.h>
using namespace std;
using namespace std::chrono;

vector<vector<char>> lines;
int dir[8][2] = {{0, 1}, {1, 0}, {-1, 0}, {0, -1}, {1, -1}, {-1, 1}, {1, 1}, {-1, -1}};
int n, m;

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

    n = lines.size();
    m = lines[0].size();

    file.close();
}

// -------------------BRUTE FORCE SOLUTION-------------------------

int simulate()
{
    int cnt = 0;

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
                lines[i][j] = '.';
            }
        }
    }

    return cnt;
}

void brute(int &cnt)
{
    int iteration;

    while (true)
    {
        iteration = simulate();

        if (!iteration)
            break;
        else
            cnt += iteration;
    }
}

// -------------------OPTIMIAL SOLUTION-------------------------
void optimal(int &cnt)
{
    deque<pair<int, int>> dq;

    // adj count
    vector<vector<int>> adj(n, vector<int>(m, 0));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (lines[i][j] == '.')
                continue;

            int val = 0;
            for (int k = 0; k < 8; k++)
            {
                int ni = i + dir[k][0];
                int nj = j + dir[k][1];

                if (ni < 0 || nj < 0 || ni >= n || nj >= m || lines[ni][nj] == '.')
                    continue;
                val++;
            }

            adj[i][j] = val;
            if (val < 4)
                dq.push_back({i, j});
        }
    }

    // simulation
    while (!dq.empty())
    {
        auto [i, j] = dq.front();
        dq.pop_front();

        if (lines[i][j] == '.' || adj[i][j] >= 4)
            continue;

        // remove
        lines[i][j] = '.';
        cnt++;

        // update adj
        for (int k = 0; k < 8; k++)
        {
            int ni = i + dir[k][0];
            int nj = j + dir[k][1];

            if (ni < 0 || nj < 0 || ni >= n || nj >= m || lines[ni][nj] == '.')
                continue;

            if (--adj[ni][nj] < 4)
                dq.push_back({ni, nj});
        }
    }
}

int main()
{
    input();

    int cnt = 0;

    // Time the brute implementation
    auto t0 = high_resolution_clock::now();
    brute(cnt);
    auto t1 = high_resolution_clock::now();

    // Time the optimal implementation
    auto t2 = high_resolution_clock::now();
    optimal(cnt);
    auto t3 = high_resolution_clock::now();

    auto dur_brute = duration_cast<microseconds>(t1 - t0).count();
    auto dur_opt = duration_cast<microseconds>(t3 - t2).count();

    cout << "Brute time: " << dur_brute << " us\n";
    cout << "Opt   time: " << dur_opt << " us\n";

    cout << cnt << endl;
    return 0;
}