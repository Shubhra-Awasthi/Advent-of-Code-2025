#include <bits/stdc++.h>
using namespace std;
using ll = long long;

vector<pair<int, int>> cords;
int n;

void input()
{
    ifstream file("input.txt");

    string line;
    while (getline(file, line))
    {
        string cord;
        stringstream ss(line);

        getline(ss, cord, ',');
        int x = stoi(cord);

        getline(ss, cord, ',');
        int y = stoi(cord);

        cords.push_back({x, y});
    }

    n = cords.size();
}

int main()
{
    input();

    ll area = 0;

    for (int i = 0; i < n; i++)
    {
        int r1 = cords[i].first;
        int c1 = cords[i].second;
        // cout << r1 << " " << c1 << endl;

        for (int j = i + 1; j < n; j++)
        {
            int r2 = cords[j].first;
            int c2 = cords[j].second;

            if (r1 == r2 || c1 == c2)
                continue;

            int len = abs(r2 - r1) + 1;
            int wid = abs(c2 - c1) + 1;
            ll cur = 1ll * len * wid;

            // cout << "2: " << r2 << " " << c2 << " -> " << cur << endl;
            area = max(area, cur);
        }
    }

    cout << area << endl;
    return 0;
}