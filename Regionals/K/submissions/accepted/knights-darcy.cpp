#include <bits/stdc++.h>
using namespace std;

struct Point {
  long long x, y;
  int idx;
  bool operator==(const Point &p) const { return x == p.x && y == p.y; }
  bool operator< (const Point &p) const { return y < p.y || (y == p.y && x < p.x); }
};
Point operator-(const Point& p,const Point& q) {
	return {p.x - q.x, p.y - q.y};
}
long long cross(const Point& p,const Point& q){ return p.x*q.y - q.x*p.y; }

vector<Point> convex_hull(vector<Point> P){
  int n = P.size();
  sort(begin(P),end(P));

  // Are all of the points collinear?
  bool collinear = true;
  for(int i=2;i<n;i++)
  	if(cross(P[i]-P[i-1],P[i-2]-P[i]) != 0)
  		collinear = false;

  if(collinear){
  	if(n == 1) return P;
  	return {P.front(),P.back()};
  }

  // NOT collinear!

  vector<Point> L,U;
  for(int i=0;i<n;i++){
    while(L.size()>1 && cross(P[i]-L.back(),L[L.size()-2]-P[i]) <= 0) L.pop_back();
    while(U.size()>1 && cross(P[i]-U.back(),U[U.size()-2]-P[i]) >= 0) U.pop_back();
    L.push_back(P[i]); U.push_back(P[i]);
  }
  vector<Point> hull(L.size() + U.size() - 2);
  copy(begin(L),end(L),begin(hull));
  copy(U.rbegin()+1,U.rend()-1,hull.begin()+L.size());
  return hull;
}

int main(){
	int n;
	cin >> n;

	vector<Point> P(n);
	for(int i=0;i<n;i++){
		cin >> P[i].x >> P[i].y;
		P[i].idx = i;
	}

	vector<Point> hull = convex_hull(P);

	string ans(n,'Y');
	for(int i=0;i<(int)hull.size();i++)
		ans[hull[i].idx] = 'N';

	cout << ans << endl;
}
