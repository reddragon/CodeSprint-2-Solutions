#include<iostream>
#include<cstdio>
#include<utility>
#include<algorithm>
#include<vector>
#include<cstring>

using namespace std;

long long dist[201000], n;
int cnt[201000];

void add_dist(int pos, int v)
{
	pos++;
	
	while(pos <= n)
	{
		dist[pos] += v;
		pos += pos & -pos;
	}
}

long long sum_upto_dist(int pos)
{
	long long ans = 0;
	pos++;
	
	while(pos > 0)
	{
		ans += dist[pos];
		pos -= pos & -pos;
	}
	
	return ans;
}

void add_city(int pos)
{
	pos++;
	
	while(pos <= n)
	{
		cnt[pos]++;
		pos += pos & -pos;
	}
}

int count_upto(int pos)
{
	pos++;
	int ans = 0;
	
	while(pos > 0)
	{
		ans += cnt[pos];
		pos -= pos & -pos;
	}
	return ans;
}

#define MOD 1000000007
int main()
{
	//freopen("inp.in", "r", stdin);
	int t, ds_index[201000];
	cin >> t;
	while(t--)
	{
		memset(dist, 0, sizeof(dist));
		memset(cnt, 0, sizeof(cnt));
		
		int c;
		cin >> c;
		
		n = c + 10;
		
		vector<int> distance, people;
		for(int i = 0; i < c; i++)
		{
			int x; 
			cin >> x;
			distance.push_back(x);
		}
		
		for(int i = 0; i < c; i++)
		{
			int x; 
			cin >> x;
			people.push_back(x);
		}
		
		// Original pairs
		vector< pair< int, int > > vc;
		
		// Sorted by people
		vector< pair< int, int > > vp;
		
		// Sorted by distance
		vector< pair< int, int > > vd;
		
		for(int i = 0; i < c; i++)
		{
			vp.push_back(make_pair(people[i], i));
			vd.push_back(make_pair(distance[i], i));
			vc.push_back(make_pair(people[i], distance[i]));
		}
		
		
		sort(vp.begin(),vp.end());
		sort(vd.begin(), vd.end());
		
		for(int i = 0; i < c; i++)
			ds_index[vd[i].second] = i;
		
		long long ans = 0;
		for(int i = 0; i < c; i++)
		{
			//cout << i << " " << vp[i].first << " " << vc[vp[i].second].second << " " << ds_index[vp[i].second] << endl;
			int pos = ds_index[vp[i].second];
			long long sum_added_before = sum_upto_dist(pos);
			int cities_before = count_upto(pos);
			long long sum_added_after = sum_upto_dist(n-1) - sum_added_before;
			int cities_after = count_upto(n-1) - cities_before;
			long long tot_dist = 0;
			
			if(cities_before)
				tot_dist = (((long long)vc[vp[i].second].second)*(cities_before) - sum_added_before) % MOD;
			
			if(cities_after)
				tot_dist += (sum_added_after - ((long long)vc[vp[i].second].second)*(cities_after)) % MOD;
			
			long long tot_cable = ((tot_dist % MOD) * (vp[i].first % MOD)) % MOD;
			ans += tot_cable;
			ans %= MOD;
			//cout << sum_added_before << " " << cities_before << " " << sum_added_after << " " << cities_after << " " << tot_dist << " " << tot_cable << endl;
			//cout << endl;
			add_dist(pos, vc[vp[i].second].second);
			add_city(pos);
		}
		
		cout << ans % MOD << endl;
		
	}
}
