#include <bits/stdc++.h>

using namespace std;

const double PI = 3.141592653589793238L;
const double EPS = 1e-9;

typedef int64_t i64;

double solve(i64 a, i64 b, i64 c) {
	double cosA = (double)(b*b + c*c - a*a)/(double)(2*b*c);
	double sinA = sqrt(1-cosA*cosA);
	double Bx = b * cosA, By = b * sinA;
	double Cx = c, Cy = 0;
	double lwr = 0, upr = PI/2 - acos(cosA);
	double x, y;
	while (upr - lwr >= EPS) {
		double mid = (upr + lwr)/2;
		x = 0, y = 0;
		x = max(x, cos(mid) * Bx - sin(mid) * By);
		y = max(y, sin(mid) * Bx + cos(mid) * By);
		x = max(x, cos(mid) * Cx - sin(mid) * Cy);
		y = max(y, sin(mid) * Cx + cos(mid) * Cy);
		if (x > y) {
			lwr = mid;
		} else {
			upr = mid;
		}
	}
	return max(x, y);
}

int main() {
	i64 a, b, c;
	cin >> a >> b >> c;
	cout << fixed << setprecision(20);
	double best = c;
	best = min(best, solve(a, b, c));
	best = min(best, solve(b, c, a));
	best = min(best, solve(c, a, b));
	cout << best << endl;
}
