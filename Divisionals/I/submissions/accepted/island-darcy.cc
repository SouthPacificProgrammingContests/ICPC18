#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;

struct UnionFind {
  vi A;
  UnionFind (int n) : A ( n ) { iota(begin(A), end(A), 0); }
  int find (int x) { return (A[x] == x ? x : A[x] = find(A[x])); }
  void merge(int x,int y){
    x = find(x); y = find(y);
    A[x] = y;
  }
  bool connected (int x, int y) { x = find(x); return x == find(y); }
};

int main(){
  int n, F, Q; cin >> n >> F >> Q;
  
  vector<pair<int,int> > friends(F);
  for(auto& x : friends){
    cin >> x.first >> x.second;
    x.first--;
    x.second--;
  }
  
  vector<pair<int,int> > endings(Q);
  vector<char> type(Q);
  for(int i=0;i<Q;i++){
    cin >> type[i] >> endings[i].first >> endings[i].second;
    endings[i].first--;
    endings[i].second--;
  }
  
  set<pair<int,int> > friendships(begin(friends), end(friends));
  for(int i=0;i<Q;i++)
    if(type[i] == 'E')
      friendships.erase(endings[i]);

  UnionFind UF(n);
  for(auto f : friendships)
    UF.merge(f.first, f.second);
  
  vector<int> ans;
  for(int i=Q-1;i>=0;i--){
    if(type[i] == 'E') UF.merge(endings[i].first, endings[i].second);
    else ans.push_back(UF.connected(endings[i].first, endings[i].second));
  }
  reverse(begin(ans), end(ans));
  for(auto x : ans)
    cout << (x ? "YES" : "NO") << endl;
}
