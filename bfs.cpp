#include <iostream>
#include <vector>
#include <queue>
using namespace std;
const int MAX = 20;
#define MP make_pair
#define LL long long
vector<vector<int>> g;
vector<vector<pair<int,int>> gp;
vector<bool> visited;
vector<int> path(MAX, -1), dis;
struct opt{
	operator()(const pair<int,int> &a,const pair<int,int> &b) const{
		return a.second > b.second;
	}
};
int n,m;
void bfs(int s){
	queue<int> q;
	q.push(s);
	visited[s] = true;
	while(!q.empty()){
		int u = q.front();
		q.pop();
		for(int i = 0 ; i < g[u].size() ; ++i){
			int v = g[u][i];
			if(!visited[v]){
				visited[v] = true;
				q.push(v);
				path[v] = u;
			}
		}
	}
}
void dfs(int s){
	visited[s] = true;
	for(int i = 0 ; i < g[s].size() ; ++i){
		int t = g[s][i];
		if(!visited[t]){
			path[t] = s;
			dfs(t);
		}
	}
}
void dijkstra(int s){
	priority_queue<pair<int,int>, vector<pair<int,int>>, opt> pq;
   	dis[s] = 0;
	pq.push(MP(s,0));
	while(!pq.empty()){
		int u = pq.top().first, wt = pq.top().second;
		pq.pop();
		for(int i = 0 ; i < g[u].size() ; ++i){
			int v = g[u][i].first, w = g[u][i].second;
			if(dis[v] > wt + w){
				dis[v] = wt + w;
				pq.push(MP(v,dis[v]));
			}	
		}
	}
}

bool bf(int s){
	for(int i = 0 ; i < n ; ++i){
		for(int j = 0 ; j < m ; ++j){
			int u = g[j].s, v = g[j].t, w = g[j].wt;
			if(dis[u] != VV && dis[v] > dis[u] + w){
				dis[v] = dis[u] + w;
			}
		}
	}
	for(int j = 0 ; j < m ; ++j){
		int u = g[j].s, v = g[j].t, w = g[j].wt;
			if(dis[u] != VV && dis[v] > dis[u] + w){
				return false;
			}
	}
	return true;
}
bool fw(){
	for(int k = 0 ; k < n ; ++k)
		for(int i = 0 ; i < n ; ++i)
			for(int j = 0 ; j < n ; ++j)
				dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
	for(int i = 0 ; i < n ; ++i){
		if(dis[i][i] < 0) return false;
	}
	return true;
}
void printPath(int s,int t){
	if(s == t){
		cout << s << '\n';
		return;
	}
	else if(path[t] == -1){
		cout << "No path\n";
		return;
	}
	int b[MAX], m = 0;
	while(t != -1){
		b[m++] = t;
		t = path[t];
	}
	for(int i = m - 1; i >=0;--i){
		cout << b[i];
		if(i > 0) cout << " -> ";
	}
	cout << '\n';
}
int main()
{
	cin >> n >> m;
	g = vector<vector<int>>(MAX, vector<int>());
	visited = vector<bool>(MAX, false);
	for(int i = 0 ; i < m ; ++i){
		int u,v;
		cin >> u >> v;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	int s,t;
	cin >> s >> t;
	bfs(s);
	printPath(s,t);
	return 0;
}
