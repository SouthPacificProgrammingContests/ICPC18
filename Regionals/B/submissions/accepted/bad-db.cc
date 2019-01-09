#include <bits/stdc++.h>
using namespace std;

void prepare_pattern(const string &pat, vector<int> &T)
{
  int n = pat.length();
  T.resize(n+1);
  fill(T.begin(), T.end(), -1);
  for (int i = 1; i <= n; i++) {
    int pos = T[i-1];
    while (pos != -1 && pat[pos] != pat[i-1]) {
      pos = T[pos];
    }
    T[i] = pos + 1;
  }
}

int find_pattern(const string &s, const string &pat, const vector<int> &T)
{
  int sp = 0, kp = 0;
  int slen = s.length(), plen = pat.length();
  int maxi = 0;
  while (sp < slen) {
    while (kp != -1 && (kp == plen || pat[kp] != s[sp])) {
      kp = T[kp];
    }
    kp++;   sp++;
    if(kp > maxi) maxi = kp;
    if (kp == plen) {
      // a match is found
      return maxi;

      // if you want more than one match (i.e. all matches), do not return
      // in the above but rather record the location of the match.  Continue
      // the loop with:
      //
      // kp = T[kp];
    }
  }
  return maxi;
}

void ans(int x){
  cout << x << endl;
  exit(0);
}

int main(){
  string s; cin >> s;
  
  int n = s.length();
  s += string(n,'*');
  
  if(n <= 3) ans(n);
  
  int the_ans = 2;
  for(int st=0;st<2;st++){
    string t((n+1-st)/2,'x');
    for(int j=st;j<n;j+=2)
      t[j/2] = s[j];
    
    vector<int> T;
    prepare_pattern(t, T);
    int best = find_pattern(s, t, T);

    the_ans = max(the_ans, 2*best + st);
  }
  cout << min(n,the_ans) << endl;
}
