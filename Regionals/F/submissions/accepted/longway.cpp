// solution of problem "A long, long way"

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;
typedef vector<ll> vl;
typedef vector<vl> ml;

const ll infty = 1<<30;

// minimal-cost matrix product m1 * m2
ml mult(ml &m1, ml &m2) {
  int n = m1.size();
  ml res(n, vl(n, infty));
  for (int i=0 ; i<n ; i++)
    for (int j=0 ; j<n ; j++)
      for (int k=0 ; k<n ; k++)
        res[i][j] = min(res[i][j], m1[i][k] + m2[k][j]);
  return res;
}

int main() {
  int n, m;
  cin >> n >> m;
  ml c[32];
  c[0] = ml(n, vl(n));
  for (int i=0 ; i<n ; i++)
    for (int j=0 ; j<n ; j++)
      cin >> c[0][i][j];
  // matrix powers c[x] = c[0]^2^x, minimal costs for paths of length 2^x
  int k = 0;
  for ( ; *min_element(c[k][0].begin(), c[k][0].end()) <= m ; k++)
    c[k+1] = mult(c[k], c[k]);
  // iteration stops if minimal cost from location 0 exceeds m
  if (k == 0) {
    // get nowhere as every leg from location 0 exceeds m
    cout << 0 << endl;
    return 0;
  }
  // maximise len such that minimal cost from location 0 in c[0]^len is <= m
  // binary search works as minimal cost increases with len
  // construct len bit-by-bit, the k-th bit is 1
  k--;
  ml cc = c[k];
  int len = 1<<k;
  for (k-- ; k>=0 ; k--) {
    ml c1 = mult(cc, c[k]);
    // try 1 for the k-th bit of len
    if (*min_element(c1[0].begin(), c1[0].end()) <= m) {
      cc = c1;
      len += 1<<k;
    }
  }
  cout << len << endl;
  return 0;
}

