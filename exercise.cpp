#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct DSU
{
	vector<int> p;
	DSU(int n)
	{
		p.resize(n);
		for(int i = 0; i < n; i ++ )
			p[i] = i;
	}

	int find(int x)
	{
		if(p[x] != x)
			p[x] = find(p[x]);

		return p[x];
	}

	void merge(int x, int y)
	{
		int rootx = find(x);
		int rooty = find(y);

		if(rootx != rooty)
			p[rootx] = rooty;
	}
};

int main()
{
	int t;
	cin >> t;
	while (t--)
	{
		int n;
		cin >> n;
		string s;
		cin >> s;

		DSU dsu(26);

		for (int i = 0; i < n / 2; i++)
		{
			int l = s[i] - 'a';
			int r = s[n - 1 - i] - 'a';

			dsu.merge(l, r);
		}

		int ans = 0;

		for (int i = 25; i > 0; i --)
		{
			bool is_drop = false;
			for (int j = 0; j < i; j++)
			{
				if (dsu.find(i) == dsu.find(j))
					is_drop = true;
			}

			if (is_drop)
			{
				ans += 1;
				dsu.merge(i, i - 1);
			}
		}
		cout << ans << endl;

	}
	return 0;
}