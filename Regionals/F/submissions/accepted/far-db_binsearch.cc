// Binary-search with a small optimization...

#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 130;
int A[MAX_N][MAX_N];

int n, budget;

void mult(const int A[MAX_N][MAX_N],
	  const int B[MAX_N][MAX_N],
	  int C[MAX_N][MAX_N]){
  for(int i=0;i<n;i++)
    for(int j=0;j<n;j++){
      C[i][j] = budget+1;
      for(int k=0;k<n;k++)
	if(C[i][j] > A[i][k] + B[k][j])
	  C[i][j] = A[i][k] + B[k][j];
    }
}

void copy(const int A[MAX_N][MAX_N], int B[MAX_N][MAX_N]){
  for(int i=0;i<n;i++)
    for(int j=0;j<n;j++)
      B[i][j] = A[i][j];
}

int B[MAX_N][MAX_N];
int res[MAX_N][MAX_N];
int tmp[MAX_N][MAX_N];

bool can_do(int steps){
  copy(A, B);
  for(int i=0;i<n;i++)
    for(int j=0;j<n;j++)
      res[i][j] = (i == 0 && j == 0 ? 0 : budget+1);

  while(steps){
    if(steps % 2){
      mult(res, B, tmp);
      copy(tmp, res);

      if(*min_element(res[0], res[0]+n) > budget)
	return false;
    }
    mult(B, B, tmp);
    copy(tmp, B);

    steps /= 2;
  }
  
  return true;  
}

int main(){
  cin >> n >> budget;
  for(int i=0;i<n;i++)
    for(int j=0;j<n;j++)
      cin >> A[i][j];

  int lo = 0, hi = 1;
  while(can_do(hi)) hi *= 2;
  while(hi - lo > 4){
    int mid = (lo + hi) / 2;
    (can_do(mid) ? lo : hi) = mid;
  }
  while(can_do(lo)) lo++;
  cout << lo-1 << endl;
}
