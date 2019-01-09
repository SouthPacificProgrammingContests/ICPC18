#include<bits/stdc++.h>
using namespace std;

int main(){
  int n; cin >> n;
  vector<long long> A(n);
  for(auto& x : A) cin >> x;

  long long tot = 0;
  for(int i=0;i<n;i++)
    tot += (i+1) * A[i] * (n-i);

  long long den = (long long)n * (n+1) / 2;
  long long g = __gcd(tot, den);

  cout << tot/g << "/" << den/g << endl;
}
