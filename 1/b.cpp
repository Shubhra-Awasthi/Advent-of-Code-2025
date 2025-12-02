#include <bits/stdc++.h>
using namespace std;

int main()
{
    int size = 100;
    int pos = 50;
    int cnt = 0;

    ifstream file("input.txt");
    string s;

    // vector<pair<string, int>> out;

    while (file >> s)
    {
        char dir = s[0];
        int rot = stoi(s.substr(1));
        if (rot >= size)
        {
            cnt += rot / size;
            rot = rot % size;
        }

        if (dir == 'L')
        {
            if (pos != 0 && pos - rot < 0)
                cnt++;
            pos = (pos - rot + size) % size;
        }
        else
        {
            if (pos != 0 && pos + rot > size)
                cnt++;
            pos = (pos + rot) % size;
        }

        if (pos == 0)
            cnt++;

        // cout << "Debug: " << s << " " << pos << " " << cnt << endl;
        // out.push_back({s, pos});
    }

    cout << cnt << endl;

    // ofstream outfile("output.txt");
    // for (auto p : out)
    // {
    //     outfile << p.first << " " << p.second << endl;
    // }
    return 0;
}