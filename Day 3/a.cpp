#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using namespace std::chrono;

void optimal(const string &line, ll &sum)
{
    int n = (int)line.size();
    if (n < 2)
        return;

    auto it1 = max_element(line.begin(), line.end() - 1);
    char c1 = *it1;

    auto it2 = max_element(it1 + 1, line.end());
    char c2 = *it2;

    int digit1 = c1 - '0';
    int digit2 = c2 - '0';
    int num = digit1 * 10 + digit2;
    sum += num;
}

void brute(const string &line, ll &sum)
{
    int n = (int)line.size();
    if (n < 2)
        return;

    int max_num = -1;

    for (int i = 0; i < n - 1; ++i)
    {
        for (int j = i + 1; j < n; ++j)
        {
            int digit1 = line[i] - '0';
            int digit2 = line[j] - '0';
            int num = digit1 * 10 + digit2;
            if (num > max_num)
                max_num = num;
        }
    }

    if (max_num >= 0)
        sum += max_num;
}

int main()
{
    ifstream infile("input.txt");

    vector<string> lines;
    string line;
    while (infile >> line)
        lines.push_back(line);

    infile.close();

    ll sum_brute = 0;
    ll sum_opt = 0;

    // Time the brute implementation
    auto t0 = high_resolution_clock::now();
    for (const string &s : lines)
        brute(const_cast<string &>(const_cast<string &>(s)), sum_brute);
    auto t1 = high_resolution_clock::now();

    // Time the optimal implementation
    auto t2 = high_resolution_clock::now();
    for (const string &s : lines)
        optimal(const_cast<string &>(const_cast<string &>(s)), sum_opt);
    auto t3 = high_resolution_clock::now();

    auto dur_brute = duration_cast<microseconds>(t1 - t0).count();
    auto dur_opt = duration_cast<microseconds>(t3 - t2).count();

    cout << "Sum (brute) = " << sum_brute << '\n';
    cout << "Sum (opt)   = " << sum_opt << '\n';
    cout << "Brute time: " << dur_brute << " us\n";
    cout << "Opt   time: " << dur_opt << " us\n";

    return 0;
}
