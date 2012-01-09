#include<iostream>
#include<vector>
#include<algorithm>
#include<cmath>
#include<set>
#include<cstring>
#include<utility>
#include<cstdio>
#include<queue>
using namespace std;

struct topic {
	int topic_id;
	double x, y;
	double dis;
	vector<int> questions;
	
	bool operator < (topic b)
	{
		if(dis < b.dis)
			return true;
		
		if(dis > b.dis)
			return false;
		
		if(topic_id > b.topic_id)
			return true;
		
		return false;
	}
};

class cmp
{
	public:
	bool operator ()(topic & a, topic & b)
	{
		if(a.dis < b.dis)
			return true;
		
		if(a.dis > b.dis)
			return false;
		
		if(a.topic_id > b.topic_id)
			return true;
		
		return false;
	}
};

struct question {
	int question_id;
	int tn;
	double dt;
	vector<int> topics;
	
	bool operator < (question b)
	{
		if(dt < b.dt)
			return true;
		
		if(dt > b.dt)
			return false;
		
		if(question_id > b.question_id)
			return true;
		
		return false;
	}
};

class cmp2
{
	public:
	bool operator ()(question & a, question & b)
	{
		if(a.dt < b.dt)
			return true;
		
		if(a.dt > b.dt)
			return false;
		
		if(a.question_id > b.question_id)
			return true;
		
		return false;
	}
};

int t, q, n;
double targ_x, targ_y;
double dis[1100];

bool cmp_topic(topic a, topic b)
{
	if(a.dis < b.dis)
		return true;
	
	if(a.dis > b.dis)
		return false;
	
	if(a.topic_id > b.topic_id)
		return true;
	
	return false;
}

bool cmp_question(question a, question b)
{
	if(a.dt < b.dt)
		return true;
	
	if(a.dt > b.dt)
		return false;
	
	if(a.question_id > b.question_id)
		return true;
	
	return false;
}


priority_queue< topic, vector<topic>, cmp > pq;
int cnt = 0;

priority_queue< question, vector<question>, cmp2 > pq2;
int cnt2 = 0;

void queue_push(topic nn, int cap)
{
	if(cnt < cap)
	{
		pq.push(nn);
		cnt++;
	}
	else
	{
		topic tt = pq.top();
		if(nn < tt)
		{
			pq.pop();
			pq.push(nn);
		}
	}
}

void queue_push2(question nn, int cap)
{
	if(cnt2 < cap)
	{
		pq2.push(nn);
		cnt2++;
	}
	else
	{
		question tt = pq2.top();
		if(nn < tt)
		{
			pq2.pop();
			pq2.push(nn);
		}
	}
}

int main()
{
	scanf("%d%d%d", &t, &q, &n);
	
	vector<topic> topics;
	vector<question> questions;

	for(int i = 0; i < t; i++)
	{
		topic top;
		scanf("%d%lf%lf", &top.topic_id, &top.x, &top.y);
		topics.push_back(top);
	}

	for(int i = 0; i < q; i++)
	{
		question que;
		scanf("%d%d", &que.question_id, &que.tn);
		que.dt = -1.0;
		//cout << que.question_id << " " << que.tn << " ";
		for(int j = 0; j < que.tn; j++)
		{
			int x = 0;
			scanf("%d", &x);
			topics[x].questions.push_back((int)questions.size());
			//cout << x << " " ;
			que.topics.push_back(x);
		}
		//cout << endl;
		
		if(que.tn)
			questions.push_back(que);
	}
	
	cnt = 0;

	for(int i = 0; i < n; i++)
	{
		char qtype;
		int num;
		
		cin >> qtype >> num >> targ_x >> targ_y;
		//cout << qtype << " " << num << " " << targ_x << " " << targ_y << endl;
		
		for(int j = 0; j < t; j++)
		{
			topics[j].dis = (targ_x - topics[j].x) * (targ_x - topics[j].y);
			topics[j].dis += (targ_y - topics[j].y) * (targ_y - topics[j].y); 
		}
		
		if(qtype == 't')
		{
			cnt = 0;
			while(!pq.empty()) pq.pop();
			num = min(num, (int)topics.size());
			for(int j = 0; j < topics.size(); j++)
				queue_push(topics[j], num);
			
			vector<topic> ll;
			while(!pq.empty())
			{
				ll.push_back(pq.top());
				pq.pop();
			}
			sort(ll.begin(), ll.end(), cmp_topic);
			for(int j = 0; j < ll.size(); j++)
				printf("%d%s", ll[j].topic_id, (j == (int)ll.size() - 1 ? "" : " "));
			printf("\n");
		}
		else
		{
			cnt2 = 0;
			while(!pq2.empty()) pq2.pop();
			
			vector<topic> vt = topics;
			sort(topics.begin(), topics.end(), cmp_topic);
			vector<question> ll;
			num = min(num, (int)questions.size());
			
			vector<bool> done;
			done.resize(questions.size());
			for(int j = 0; j < questions.size(); j++)
				done[j] = 0;
			
			int pushed = 0;
			for(int j = 0; j < vt.size(); j++)
			{
				for(int k = 0; k < vt[j].questions.size(); k++)
					if(!done[vt[j].questions[k]])
					{
						pushed++;
						question qq = questions[vt[j].questions[k]];
						qq.dt = vt[j].dis;
						done[vt[j].questions[k]] = 1;
						//cout << qq.topic_id << endl;
						queue_push2(qq, num);
					}
				
				if(pushed >= num) break;
			}
			
			while(!pq2.empty())
			{
				ll.push_back(pq2.top());
				pq2.pop();
			}
			sort(ll.begin(), ll.end(), cmp_question);
			
			/*
			vector<question> vq = questions;
			num = min(num, (int)vq.size());
			
			
			for(int k = 0; k < vq.size(); k++)
				for(int l = 0; l < vq[k].topics.size(); l++)
					vq[k].dt = ( l == 0 ) ? topics[vq[k].topics[l]].dis : min(vq[k].dt, topics[vq[k].topics[l]].dis);
			
			for(int k = 0; k < vq.size(); k++)
				queue_push2(vq[k], num);
			
			vector<question> ll;
			while(!pq2.empty())
			{
				ll.push_back(pq2.top());
				pq2.pop();
			}
			sort(ll.begin(), ll.end(), cmp_question);
			
			//sort(vq.begin(), vq.end(), cmp2);
			*/
			for(int k = 0; k < min(num, (int)ll.size()); k++)
				printf("%d%s", ll[k].question_id, (k == num - 1 ? "" : " "));
			printf("\n");
		}
		/*
		for(int j = 0; j < t; j++)
		{
				dis[j]  = (targ_x - topics[j].x) * (targ_x - topics[j].y);
				dis[j] += (targ_y - topics[j].y) * (targ_y - topics[j].y); 
				//cout << j << " " << dis[j] << endl;
		}
		//cout << endl;
		
		
		if(qtype == 't')
		{
			vector<topic> vt = topics;
			sort(vt.begin(), vt.end(), cmp);
			num = min(num, (int)vt.size());
			for(int j = 0; j < num; j++)
				printf("%d%s", vt[j].topic_id, (j == num - 1 ? "" : " "));
		}
		 
		printf("\n"); */
	} 

}
