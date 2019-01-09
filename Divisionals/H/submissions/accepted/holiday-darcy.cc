#include <bits/stdc++.h>
using namespace std;

vector<int> A;
int how_many;

bool f(int t){
  map<int,int> S;
  for(int i=0;i<t;i++) S[A[i]]++;
  if((int)S.size() != how_many) return false;
  
  for(int i=0;i+t<(int)A.size();i++){
    S[A[i+t]]++;
    S[A[i]]--;
    if(S[A[i]] == 0) return false;
  }
  return true;
}

int main(){
  int n; cin >> n;
  A.resize(n);
  for(auto& x : A) cin >> x;
  how_many = set<int>(begin(A), end(A)).size();

  int lo = 0, hi = n;
  
  while(hi - lo > 1){
    int mid = (lo + hi) / 2;
    (f(mid) ? hi : lo) = mid;
  }
  cout << hi << endl;
}
