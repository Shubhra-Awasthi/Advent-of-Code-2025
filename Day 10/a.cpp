#include <bits/stdc++.h>
using namespace std;
using ll = long long;

vector<int> indicator;
vector<vector<int>> buttons;
int n;

void input()
{
    ifstream file("input.txt");

    // machines
    string line;
    while (getline(file, line))
    {
        string token;
        stringstream ss(line);

        // indicator
        getline(ss, token, ' ');
        int sz = token.size();
        int mask = 0;

        for (int i = 1; i < sz - 1; i++)
            if (token[i] == '#')
                mask |= (1 << (i - 1));

        indicator.push_back(mask);

        // buttons
        vector<int> button;
        while (ss >> token)
        {
            if (token[0] == '{')
                break; // ignore joltage

            int sz2 = token.size();
            mask = 0;

            string inner = token.substr(1, sz2 - 2);
            string num;
            stringstream ns(inner);
            while (getline(ns, num, ','))
            {
                if (num.empty())
                    continue;
                int idx = stoi(num);
                mask |= (1 << idx);
            }

            button.push_back(mask);
        }
        buttons.push_back(button);
    }

    file.close();

    n = indicator.size();

    // print input
    //  for (int i = 0; i < n; i++)
    //  {
    //      cout << bitset<sizeof(indicator[i])>(indicator[i]) << " : ";
    //      for (int btn : buttons[i])
    //          cout << bitset<sizeof(btn)>(btn) << " ";
    //      cout << "\n";
    //  }
}

int main()
{
    input();

    ll total = 0;

    // machines
    for (int i = 0; i < n; i++)
    {
        int m = buttons[i].size();
        int target = indicator[i];
        bool solved = false;

        // press k buttons and check all their combinations
        for (int k = 0; k <= m; k++)
        {
            vector<int> comb(m, 0);
            fill(comb.end() - k, comb.end(), 1);

            // check all permutations
            do
            {
                int cur = 0;
                for (int j = 0; j < m; j++)
                    if (comb[j])
                        cur ^= buttons[i][j];

                if (cur == target)
                {
                    solved = true;

                    total += (ll)k;
                    // cout << "Machine " << i << " - " << k << "\n";

                    break;
                }

            } while (next_permutation(comb.begin(), comb.end()));

            if (solved)
                break;
        }
    }

    cout << total << endl;
    return 0;
}