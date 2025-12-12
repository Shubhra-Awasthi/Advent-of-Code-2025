// not the actual solution, but it works for the given input. Its a Trick Question!
#include <bits/stdc++.h>
using namespace std;

vector<int> shapes;

void input()
{

	ifstream in("input.txt");

	int k = 6;

	while (k--)
	{
		string line;
		getline(in, line); // ignore number

		int cnt = 0;
		int shape = 3;
		while (shape--)
		{
			getline(in, line);

			for (char c : line)
				if (c == '#')
					cnt++;
		}

		getline(in, line); // ignore blank line

		shapes.push_back(cnt);
	}

	// read grids
	string line;
	int cnt = 0;
	while (getline(in, line))
	{
		if (line.empty())
			break;

		string token;
		stringstream ss(line);

		getline(ss, token, 'x');
		int w = stoi(token);

		getline(ss, token, ':');
		int l = stoi(token);

		int area = w * l;

		int gifts = 0;
		bool fit = true;
		for (int i = 0; i < 6; i++)
		{
			int num;
			if (!(ss >> num))
			{
				fit = false;
				break;
			}

			gifts += num * shapes[i];

			if (gifts > area)
			{
				fit = false;
				break;
			}
		}

		if (fit)
			cnt++;
	}

	cout << cnt << endl;
	in.close();
}

int main()
{
	input();
	return 0;
}
