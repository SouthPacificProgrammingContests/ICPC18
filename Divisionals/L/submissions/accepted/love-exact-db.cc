// Computes the exact answer without binary searching...

/*

   ----------------------------------------------
  |               **                             |
  |              * A  *                          |
  |             *        *                       |
  |            *            *                    |
  |           *                *      c          |
  |          *                    *              |
  |     b   *                        *           |
  |        *                            *        |
  |       *                                *     |
  |      *                                B   *  |
  |     *                                       *|
  |    *                                *        |
  |   *                       *                  |
  |  * C             *      a                    |
  | *       *                                    |
  |*                                             |
   ----------------------------------------------
*/


#include <bits/stdc++.h>
using namespace std;

long long sqr(long long a){ return a*a; }

long double f(long long a, long long b, long long c){
  if(a < b) return max({a,b,c}); // We will check this later (symmetry)
  long long a2 = sqr(a), b2 = sqr(b), c2 = sqr(c);
  long long a4 = sqr(a2);
  
  pair<long long, long long> cosA(b2 + c2 - a2, 2*b*c);
  pair<long long, long long> cosB(a2 + c2 - b2, 2*a*c);
  pair<long long, long long> cosC(a2 + b2 - c2, 2*a*b);
  
  // First, I don't fit in the quadrant, return!
  // - If we can, then acos( cosC ) > PI/2
  // - This happens when:
  if(cosC.first <= 0) return max(a,c);
  
  // Can we just use 'a' on the main diagonal?
  //  - We can if B and C are both <= PI/4
  //
  //  NOTE: acos(x) <= PI/4  ---> 1/sqrt(2) <= x <= 1
  //    ---> 1/sqrt(2) <= cosC
  //    --->         1 <= sqrt(2) * cosC
  //    --->         1 <= 2 * cosC^2
  if(sqr(cosC.second) <= 2 * sqr(cosC.first) &&
     sqr(cosB.second) <= 2 * sqr(cosB.first))
    return a / sqrt(2);

  long double X = sqrt(-a4 + 2*(b2 + c2) * a2 - sqr(b-c) * sqr(b+c));
  long double Y_n = (-X + a2 + b2);
  
  long long ans_n = (a2 + b2 - c2);
  long double ans_d = 2 * sqrt(Y_n);

  long double ans = ans_n / ans_d;
  
  // It is possible that we have found degenerate cases. Let's check
  // for those now!
  if(ans < max({a,b,c}) / sqrt(2)-(1e-5)) return max({a,b,c});

  long double phi = acosl(ans / a);
  const long double PI = acosl(-1.0);
  long double theta = acos(cosC.first / 1.l / cosC.second);

  if(PI/2 - theta - phi < 0){
    phi = PI/2 - theta;
    return max(a * cos(phi), b * cos(PI/2 - theta - phi));
  }
  
  return ans;
}

int main(){
  long long a[3];
  for(int i=0;i<3;i++)
    cin >> a[i];

  cout << fixed << setprecision(15);

  long double best = a[2]; // It won't be this bad...

  do {
    best = min(best, f(a[0], a[1], a[2]));
  } while(next_permutation(a,a+3));

  cout << best << endl;
}
