#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int n;
int maxr = 0, maxc = 0, minr = INT_MAX, minc = INT_MAX;

vector<pair<int, int>> cords;
vector<pair<int, int>> rawCords;
vector<vector<char>> grid;
vector<vector<ll>> pref;

vector<int> rowVals, colVals;
vector<vector<ll>> cellArea; // area in original tiles represented by compressed cell (1-based indices)

void input()
{
    ifstream file("input.txt");
    string line;
    while (getline(file, line))
    {
        if (line.empty())
            continue;
        string cord;
        stringstream ss(line);

        getline(ss, cord, ',');
        int x = stoi(cord);
        getline(ss, cord, ',');
        int y = stoi(cord);

        swap(x, y);

        rawCords.push_back({x, y});
        maxr = max(maxr, x);
        maxc = max(maxc, y);
        minr = min(minr, x);
        minc = min(minc, y);
    }

    if (rawCords.empty())
    {
        n = 0;
        grid.assign(1, vector<char>(1, '.'));
        pref.assign(1, vector<ll>(1, 0));
        return;
    }

    // normalize raw cords so smallest coordinate becomes 0 (keeps distances)
    for (auto &p : rawCords)
    {
        p.first -= minr;
        p.second -= minc;
    }
    maxr -= minr;
    maxc -= minc;

    n = (int)rawCords.size();

    // --- build coordinate boundaries for compression ---
    rowVals.clear();
    colVals.clear();
    rowVals.reserve(n * 4 + 10);
    colVals.reserve(n * 4 + 10);

    // always include 0 and bounding end
    rowVals.push_back(0);
    rowVals.push_back(maxr + 1);
    colVals.push_back(0);
    colVals.push_back(maxc + 1);

    // include each coordinate and coordinate+1 so inclusive integer ranges map cleanly
    for (int i = 0; i < n; ++i)
    {
        int r = rawCords[i].first;
        int c = rawCords[i].second;
        rowVals.push_back(r);
        rowVals.push_back(r + 1);
        colVals.push_back(c);
        colVals.push_back(c + 1);
    }
    // also include segment endpoints (for axis-aligned edges) so inclusive ranges map
    for (int i = 0; i < n; ++i)
    {
        auto [r1, c1] = rawCords[i];
        auto [r2, c2] = rawCords[(i + 1) % n];
        if (r1 == r2)
        {
            int cl = min(c1, c2), cr = max(c1, c2);
            colVals.push_back(cl);
            colVals.push_back(cr + 1);
            rowVals.push_back(r1);
            rowVals.push_back(r1 + 1);
        }
        else if (c1 == c2)
        {
            int rl = min(r1, r2), rr = max(r1, r2);
            rowVals.push_back(rl);
            rowVals.push_back(rr + 1);
            colVals.push_back(c1);
            colVals.push_back(c1 + 1);
        }
    }

    sort(rowVals.begin(), rowVals.end());
    rowVals.erase(unique(rowVals.begin(), rowVals.end()), rowVals.end());
    sort(colVals.begin(), colVals.end());
    colVals.erase(unique(colVals.begin(), colVals.end()), colVals.end());

    // compressed counts
    int R = (int)rowVals.size() - 1; // number of compressed rows
    int C = (int)colVals.size() - 1; // number of compressed cols

    // prepare cellArea (1-based indexing: 1..R , 1..C)
    cellArea.assign(R + 1, vector<ll>(C + 1, 0));
    for (int i = 1; i <= R; ++i)
    {
        ll height = ll(rowVals[i] - rowVals[i - 1]);
        for (int j = 1; j <= C; ++j)
        {
            ll width = ll(colVals[j] - colVals[j - 1]);
            cellArea[i][j] = height * width;
        }
    }

    // convert raw coordinates to compressed indices (1-based)
    cords.clear();
    cords.reserve(n);
    for (int i = 0; i < n; ++i)
    {
        int r = rawCords[i].first;
        int c = rawCords[i].second;
        int rb = int(lower_bound(rowVals.begin(), rowVals.end(), r) - rowVals.begin()); // boundary index
        int cb = int(lower_bound(colVals.begin(), colVals.end(), c) - colVals.begin());
        int ri = rb + 1; // cell index (1-based)
        int ci = cb + 1; // cell index (1-based)

        ri = max(1, min(ri, R));
        ci = max(1, min(ci, C));
        cords.push_back({ri, ci});
    }

    maxr = R;
    maxc = C;

    // allocate compressed grid and pref (1-based indices)
    grid.assign(maxr + 1, vector<char>(maxc + 1, '.'));
    pref.assign(maxr + 1, vector<ll>(maxc + 1, 0));

    // fill green in compressed
    for (int i = 0; i < n; ++i)
    {
        int r1 = cords[i].first;
        int c1 = cords[i].second;
        int r2 = cords[(i + 1) % n].first;
        int c2 = cords[(i + 1) % n].second;

        if (r1 == r2)
        {
            int raw_r = rowVals[r1 - 1];
            int raw_c1 = colVals[c1 - 1];
            int raw_c2 = colVals[c2 - 1];

            int cl = min(c1, c2);
            int cr = max(c1, c2);

            int idxL = cl;
            int idxR = cr;
            if (idxL < 1)
                idxL = 1;
            if (idxR > maxc)
                idxR = maxc;
            for (int j = idxL; j <= idxR; ++j)
                grid[r1][j] = 'G';
        }

        if (c1 == c2)
        {
            int cl = c1;
            int cr = c1;
            int rl = min(r1, r2);
            int rr = max(r1, r2);
            int idxL = rl;
            int idxR = rr;
            if (idxL < 1)
                idxL = 1;
            if (idxR > maxr)
                idxR = maxr;
            for (int r = idxL; r <= idxR; ++r)
                grid[r][c1] = 'G';
        }
    }

    // fill between
    for (int i = 1; i <= maxr; ++i)
    {
        int mini = maxc + 1, maxi = 0;
        for (int j = 1; j <= maxc; ++j)
            if (grid[i][j] == 'G')
            {
                mini = min(mini, j);
                maxi = max(maxi, j);
            }
        if (mini <= maxi)
            for (int j = mini; j <= maxi; ++j)
                grid[i][j] = 'G';
    }

    // pref sum
    for (int i = 1; i <= maxr; ++i)
        for (int j = 1; j <= maxc; ++j)
            pref[i][j] = pref[i - 1][j] + pref[i][j - 1] - pref[i - 1][j - 1] + (grid[i][j] == 'G' ? cellArea[i][j] : 0);
}

inline ll rectSum(int r1, int c1, int r2, int c2)
{
    if (r1 > r2 || c1 > c2)
        return 0;
    return pref[r2][c2] - pref[r1 - 1][c2] - pref[r2][c1 - 1] + pref[r1 - 1][c1 - 1];
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    input();

    ll area = 0;

    for (int i = 0; i < n; i++)
    {
        int r1 = cords[i].first;
        int c1 = cords[i].second;

        for (int j = i + 1; j < n; j++)
        {
            int r2 = cords[j].first;
            int c2 = cords[j].second;

            if (r1 == r2 || c1 == c2)
                continue;

            int rl = min(r1, r2);
            int rr = max(r1, r2);
            int cl = min(c1, c2);
            int cr = max(c1, c2);

            ll raw_left = colVals[cl - 1];
            ll raw_right = colVals[cr] - 1;
            ll raw_top = rowVals[rl - 1];
            ll raw_bottom = rowVals[rr] - 1;
            ll len = raw_bottom - raw_top + 1;
            ll wid = raw_right - raw_left + 1;
            if (len <= 0 || wid <= 0)
                continue;
            ll green_need = len * wid;

            ll green_have = rectSum(rl, cl, rr, cr);

            if (green_need == green_have)
            {
                area = max(area, green_have);
            }
        }
    }

    cout << area << '\n';
    return 0;
}
