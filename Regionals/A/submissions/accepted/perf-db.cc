#include <bits/stdc++.h>
using namespace std;

bool do_it(){
  int n, L; cin >> n >> L;

  int len = 0;
  for(int i=0;i<n;i++){
    string s; cin >> s;
    len += s.length();
  }

  int blanks = L - len;
  if(blanks < n-1) return false;
  if(n == 1) return blanks == 0;
  return (blanks % (n-1) == 0);
}

int main(){
  cout << (do_it() ? "Yes" : "No") << endl;
}
