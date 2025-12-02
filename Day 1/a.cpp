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
        if (rot > size)
            rot = rot % size;

        if (dir == 'L')
            pos = (pos - rot + size) % size;
        else
            pos = (pos + rot) % size;

        if (pos == 0)
            cnt++;

        // out.push_back({s, pos});
    }

    cout << cnt << endl;

    // output file
    // ofstream outfile("output.txt");
    // for (auto p : out)
    // {
    //     outfile << p.first << " " << p.second << endl;
    // }
    return 0;
}