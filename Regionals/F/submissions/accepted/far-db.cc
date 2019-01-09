// Binary lifting type solution.

#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 130;
const int LOG_MAX_ANS = 35;
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

int pow2[LOG_MAX_ANS][MAX_N][MAX_N];
int ans[MAX_N][MAX_N];
int tmp[MAX_N][MAX_N];

int main(){
  cin >> n >> budget;
  for(int i=0;i<n;i++)
    for(int j=0;j<n;j++)
      cin >> A[i][j];

  copy(A, pow2[0]);
  int maxi = 1;
  while(true){
    mult(pow2[maxi-1], pow2[maxi-1], pow2[maxi]);
    if(*min_element(pow2[maxi][0], pow2[maxi][0]+n) > budget) break;
    maxi++;
  }

  for(int i=0;i<n;i++)
    for(int j=0;j<n;j++)
      ans[i][j] = (i == 0 && j == 0 ? 0 : budget+1);

  int the_answer = 0;
  for(int i=maxi-1;i>=0;i--){
    mult(ans, pow2[i], tmp);
    if(*min_element(tmp[0], tmp[0]+n) <= budget){
      copy(tmp, ans);
      the_answer |= (1 << i);
    }
  }

  cout << the_answer << endl;
}
