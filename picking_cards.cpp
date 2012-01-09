#include<iostream>
#include<cstdio>
#include<cstring>

using namespace std;

int tree[51000], n;

void insert(int pos)
{
	tree[pos]++;
	/*
	int x = pos;
	while(x <= n)
	{
		tree[x]++;
		x += x & -x;
	} */
}

int count(int pos)
{
	return tree[pos];
	/*
	int ans = 0;
	int x = pos;
	while(x > 0)
	{
		ans += tree[x];
		x -= x & -x;
	} 
	return ans; */
}

int cards_at(int pos)
{
	pos++;
	return count(pos);
	//return count(pos) - count(pos-1);
}

#define MOD 1000000007
int main()
{
	
	int t;
	cin>>t;
	while(t--)
	{
		int cards;
		cin>>cards;
		n = cards + 2;
		memset(tree, 0, sizeof(tree));
		
		for(int i = 0; i < cards; i++)
		{
			int ci;
			cin>>ci;
			insert(ci+1);
		}
		
		long long ans = 1;
		int cur_cards = 0;

		for(int cards_picked = 0; cards_picked < cards; cards_picked++)
		{
			cur_cards += cards_at(cards_picked);
			if(cur_cards == 0)
			{
				ans = 0;
				break;
			}

			ans = (ans * cur_cards) % MOD;
			cur_cards--;
		}
		
		ans %= MOD;
		cout << ans << endl;
	}
}
