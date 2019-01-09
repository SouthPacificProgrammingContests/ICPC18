// Explosive Wiring
// Author: Darcy Best
// Complexity: O(n^3 * m + n^3)
//
// EXPECTED_RESULT: ??

#include <bits/stdc++.h>
using namespace std;

vector<int> value;               // The value of the i'th wire
vector<vector<bool> > intersect; // Do the wires intersect?
vector<int> right_end;           // Who is my right endpoint?

vector<vector<vector<int> > > DP;

int f(int idx, int c1, int c2){
  int& x = DP[idx][c1][c2];
  if(x >= 0) return x;

  x = 0;
  
  for( ; !(c1 == idx || c2 == idx || right_end[c1] == idx || right_end[c2] == idx) ; idx++)
    if(right_end[idx] != idx && !intersect[idx][c1] && !intersect[idx][c2]){ // Use this wire
      for(int you=idx+1;you != c1 && you != c2 && you != right_end[c1] && you != right_end[c2];you++){
        if(!intersect[idx][you] || intersect[you][c1] || intersect[you][c2] || right_end[you] == you) continue;
        x = max(x,
              value[idx] + value[you] + f(idx+1, idx, you) + f(you+1, idx, you) +
              f(min(right_end[idx], right_end[you])+1, idx, you) +
              f(max(right_end[idx], right_end[you])+1, c1, c2));
      }
    }  

  return x;
}

struct Point {
  int x, y;
};
Point operator-(Point p, Point q){ return {p.x-q.x, p.y-q.y}; }
int cross(Point p, Point q){ return p.x*q.y - p.y*q.x; }

bool in_bounding_box(Point p, Point q, Point r){ // Is r in box?
  return min(p.x,q.x) <= r.x && r.x <= max(p.x,q.x) &&
    min(p.y,q.y) <= r.y && r.y <= max(p.y,q.y);
}

int dir(Point p, Point q, Point r){
  int val = cross(q-p, r-q);
  if(val == 0) return (in_bounding_box(p,q,r) ? 2 : 0); // 0 is bad... 2 is on line
  return (val < 0 ? -1 : 1);
}

bool lines_intersect(pair<Point, Point> L1, pair<Point, Point> L2){
  int d1 = dir(L1.first, L1.second, L2.first), d2 = dir(L1.first, L1.second, L2.second);
  int d3 = dir(L2.first, L2.second, L1.first), d4 = dir(L2.first, L2.second, L1.second);

  return max({d1,d2,d3,d4}) == 2 || (d1*d2 == -1 && d3*d4 == -1);
}

bool polylines_intersect(const vector<Point>& p, const vector<Point>& q){
  for(int i=0;i+1<(int)p.size();i++)
    for(int j=0;j+1<(int)q.size();j++)
      if(lines_intersect(make_pair(p[i], p[i+1]), make_pair(q[j], q[j+1])))
        return true;
  return false;
}

int main(){
  int n; cin >> n;

  vector<vector<Point> > lines(n);

  vector<int> orig_values(n);
  vector<pair<int,int> > who;
  for(int i=0;i<n;i++){
    int p; cin >> orig_values[i] >> p;
    lines[i].resize(p);
    for(auto& pt : lines[i])
      cin >> pt.x >> pt.y;
    who.emplace_back(lines[i].front().x, i);
    who.emplace_back(lines[i].back().x , i);
  }
  sort(begin(who), end(who));

  for(int i=0;i<2*n;i++)
    value.push_back(orig_values[ who[i].second ]);

  vector<int> the_right(n, -1);
  right_end.resize(2*n+1, 2*n); // The 2*n is so that right_end[2*n] == 2*n
  for(int i=2*n-1;i>=0;i--){
    if(the_right[ who[i].second ] == -1) the_right[ who[i].second ] = i;
    right_end[i] = the_right[ who[i].second ];
  }

  intersect.assign(2*n+1, vector<bool>(2*n+1, false));

  for(int i=0;i<2*n;i++)
    for(int j=i+1;j<2*n;j++)
      intersect[i][j] = intersect[j][i] = polylines_intersect(lines[who[i].second], lines[who[j].second]);

  DP.assign(2*n+1, vector<vector<int> >(2*n+1, vector<int>(2*n+1,-1)));

  cout << f(0, 2*n, 2*n) << endl;
}
