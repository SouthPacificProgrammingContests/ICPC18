#include <bits/stdc++.h>
using namespace std;

int main(){
  int m, n; cin >> m >> n;

  vector<int> A(m);
  for(auto& x : A) cin >> x;
  
  int tot = accumulate(begin(A), end(A), 0);

  cout << (tot + n - 1) / n << endl;
}
