#include <bits/stdc++.h>
using namespace std;

vector<vector<pair<int,int> > > adj;
vector<bool> vis;
vector<string> ans;

void dfs(int v,int step, const string& my_answer){
  if(vis[v]) return;
  vis[v] = true;
  
  ans[v] = my_answer;

  for(auto u : adj[v])
    if(u.second <= step) // Am I allowed to use this edge?
      dfs(u.first,step,my_answer);
}

int main(){
  int n, x, y;
  cin >> n >> x >> y;

  adj.resize(n);
  for(int i=0;i<x;i++){
    int u, v;
    cin >> u >> v;
    u--;
    v--;
    adj[u].emplace_back(v,0);
    adj[v].emplace_back(u,0);
  }
  for(int i=0;i<y;i++){
    int u, v;
    cin >> u >> v;
    u--;
    v--;
    adj[u].emplace_back(v,0);
    adj[v].emplace_back(u,1);
  }

  ans.assign(n,"Impossible");
  
  vis.assign(n,false);
  dfs(0,1,"Ticket");
  
  vis.assign(n,false);
  dfs(0,0,"No Ticket");

  for(int v=0;v<n;v++)
    cout << ans[v] << endl;
}
