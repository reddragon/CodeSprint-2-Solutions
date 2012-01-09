#include<iostream>
#include<string>
#include<vector>
#include<cstdio>
#include<algorithm>
#include<cctype>
#include<cstring>
using namespace std;

struct node {
	long long order_id, deal_id;
	string email_id, street_addr, city, state;
	string zipcode, credit_card;
	bool fraud;
};


vector< node > vn;
int n;

long long s2i(string s)
{
	long long ans = 0;
	for(int i = 0; i < s.size(); i++)
	{
		ans *= 10;
		ans += s[i]-'0';
	}

	return ans;
}

vector<string> get_tokens(string s, char delim)
{
	vector<string> ans;
	
	string prev;
	
	for(int i = 0; i < s.size(); i++)
		if(s[i] == delim)
		{
			if(prev != "")
			{
				ans.push_back(prev);
				prev = "";
			}
		}
		else	prev.push_back(s[i]);

	if(prev != "")
		ans.push_back(prev);

	return ans;
}

void tolower(string & s)
{
	for(int i = 0; i < s.size(); i++)
		if(isalpha(s[i]) && isupper(s[i]))
			s[i] = tolower(s[i]);
}

void ignore_plus(string & s)
{
	bool ignore = false, username = true;
	string res = "";
	
	for(int i = 0; i < s.size(); i++)
	{
		if(username && s[i] == '.')
			continue;

		if(s[i] == '@')
		{
			username = false;
			ignore = false;
		}
		
		if(username && s[i] == '+')
			ignore = true;

		if(ignore  && username)
			continue;

		res.push_back(s[i]);
	}

	s = res;
}

void abbreviate_state(string & s)
{
	if(s == "New York")
		s = "NY";
	else if(s == "Illinois")
		s = "IL";
	else if(s == "California")
		s = "CA";
}

void abbreviate_street_addr(string & addr)
{
	vector<string> tok = get_tokens(addr, ' ');
	string res = "";
	for(int i = 0; i < tok.size(); i++)
	{
		if(tok[i] == "st.")
			res += "street";

		else if(tok[i] == "rd.")
			res += "road";

		else
			res += tok[i];

		if(i != tok.size() - 1)
			res += " ";
	}

	addr = res;
}

node getnode(string s)
{
	node nd;
	vector<string> tok = get_tokens(s, ',');
	nd.order_id = s2i(tok[0]);
	nd.deal_id = s2i(tok[1]);
	nd.email_id = tok[2];
	nd.street_addr = tok[3];
	nd.city = tok[4];
	nd.state = tok[5];
	nd.zipcode = tok[6];
	nd.credit_card = tok[7];
	
	tolower(nd.email_id);
	tolower(nd.street_addr);
	ignore_plus(nd.email_id);
	abbreviate_state(nd.state);
	abbreviate_street_addr(nd.street_addr);
	tolower(nd.state);
	tolower(nd.city);
	
	nd.fraud = false;
	/*
	cout << nd.order_id << endl;
	cout << nd.deal_id << endl;
	cout << nd.email_id << endl;
	cout << nd.street_addr << endl;
	cout << nd.city << endl;
	cout << nd.state << endl;
	cout << nd.zipcode << endl;
	cout << nd.credit_card << endl; */ 
	return nd;
}

bool cmp(node a, node b)
{
	if(a.deal_id < b.deal_id)
		return true;
	
	if(a.deal_id > b.deal_id)
		return false;

	return (a.order_id < b.order_id);
}

int main()
{
	scanf("%d", &n);
	vn.resize(n);
	
	string s;
	getline(cin, s);
		
	for(int i = 0; i < n; i++)
	{
		getline(cin, s);
		vn[i] = getnode(s);
		//cout << s << endl;
	}
	
	sort(vn.begin(), vn.end(), &cmp);	
	
	//for(int i = 0; i < n; i++)
	//	cout << vn[i].order_id << " " << vn[i].deal_id << endl;
	//cout << endl;

	for(int i = 0; i < n; i++)
	{
		if(vn[i].fraud) continue;
		for(int j = i+1; j < n; j++)
		{
			if(vn[i].deal_id != vn[j].deal_id)
				break;

			if(vn[j].fraud) continue;
			bool is_fraud = false;
			
			
			if(vn[i].email_id == vn[j].email_id && vn[i].credit_card != vn[j].credit_card)
				is_fraud = true;

			if(vn[i].street_addr == vn[j].street_addr && vn[i].city == vn[j].city && vn[i].state == vn[j].state && vn[i].zipcode == vn[j].zipcode && vn[i].credit_card != vn[j].credit_card)
				is_fraud = true;


			if(is_fraud)
			{
				vn[i].fraud = 1; 
				vn[j].fraud = 1;
			}
		}
	}
	
	vector<int> order_ids;

	for(int i = 0; i < n; i++)
		if(vn[i].fraud)
		{
			order_ids.push_back(vn[i].order_id);
		}
	sort(order_ids.begin(), order_ids.end());

	bool first = 0;
	for(int i = 0; i < order_ids.size(); i++)
	{
		printf("%s%d", (first ? "," : ""), order_ids[i]);
		first = 1;
	} 
	if(first)
		printf("\n");
	
}
