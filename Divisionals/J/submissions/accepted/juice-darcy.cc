#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 55;
const int MAX_C = 12;
const int LCM = 8 * 9 * 5 * 7;
int DP[MAX_N * LCM];

int main(){
  int n, C; cin >> n >> C;

  n *= LCM;
  
  for(int i=0;i<=n;i++) DP[i] = -1;
  DP[0] = 0;
  
  for(int i=0;i<C;i++){
    int x,y; cin >> x >> y;
    x *= LCM / y;

    for(int j=0;j+x<=n;j++){
      if(DP[j] == -1) continue;
      if(DP[j+x] == -1 || DP[j+x] > DP[j] + 1)
	DP[j+x] = DP[j] + 1;
    }	
  }

  cout << DP[n] << endl;
}
