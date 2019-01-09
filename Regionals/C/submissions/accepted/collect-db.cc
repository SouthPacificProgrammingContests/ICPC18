#include <bits/stdc++.h>
using namespace std;

int main(){
  int n, k; cin >> n >> k;

  vector<pair<int,int> > v(n);
  for(auto& x : v) cin >> x.second >> x.first;

  sort(v.rbegin(), v.rend());

  priority_queue<int, vector<int>, greater<int> > pq;
  long long ans = 0;
  int collected = 0;
  for(int collected = 0 ; collected < k ; collected++){
    while(v.size() && v.back().first <= collected){
      pq.push(v.back().second);
      v.pop_back();
    }
    if(pq.empty()) { cout << "IMPOSSIBLE" << endl; return 0; }
    ans += pq.top();
    pq.pop();
  }
  cout << ans << endl;
}
