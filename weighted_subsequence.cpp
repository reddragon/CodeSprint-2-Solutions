#include<iostream>
#include<cstdio>
#include<utility>
#include<vector>
#include<algorithm>
#include<cstring>
using namespace std;

long long tree[151000], e;

void add(long long v, int x)
{
	x++;
	while(x <= e)
	{
		tree[x] = max(tree[x], v);
		x += x & -x;
	}
}

long long max_query(int x)
{
	long long ans = 0;
	x++;
	while(x > 0)
	{
		ans = max(ans, tree[x]);
		x -= x & -x;
	}
	return ans;
}

int main()
{
	int t, sort_loc[151000];
	cin >> t;
	while(t--)
	{
		memset(tree, 0, sizeof(tree));
		vector< pair<int,int> > od, ki;
		vector< int > sk;
		int n;
		cin >> n;
		e = n + 2;
		for(int i = 0; i < n; i++)
		{
			int key; cin >> key;
			od.push_back(make_pair(key, 0));
			ki.push_back(make_pair(key, i));
		}

		for(int i = 0; i < n; i++)
		{
			int wt; cin >> wt;
			od[i].second = wt;
		}

		sort(ki.begin(), ki.end());
		
		for(int i = 0; i < n; i++)
		{
			sort_loc[ki[i].second] = i;
			sk.push_back(ki[i].first);
		}

		long long fans = 0;
		for(int i = 0; i < n; i++)
		{
			int pos = sort_loc[i];
			int less_than = (int)(lower_bound(sk.begin(), sk.end(), od[i].first-1) - sk.begin());
			long long ans = 0;
			if(sk[0] < od[i].first)
			{
				ans = max_query(less_than);
			}
			ans += od[i].second;
			add(ans, pos);
			fans = max(fans, ans);
		}
		cout << fans << endl;
	}
}
