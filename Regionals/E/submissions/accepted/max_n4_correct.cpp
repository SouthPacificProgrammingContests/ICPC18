#include <bits/stdc++.h>

using namespace std;

typedef long double coord_t;
const long double EPS = 1e-8;

template <typename T> int sgn(T val) { return (T(0) < val) - (val < T(0)); }
template <typename T> T tabs(T val) { return val < T(0) ? -val : val; }
template <typename T> bool eq(T lhs, T rhs, T eps) { return tabs(lhs - rhs) <= EPS * max(tabs(lhs), tabs(rhs)); }

struct Point {
	coord_t x, y;
	Point() : x(0), y(0) {}
	Point(coord_t x, coord_t y) : x(x), y(y) {}
	Point operator+(const Point& rhs) const {
		return Point(x + rhs.x, y + rhs.y);
	}
	Point operator-(const Point& rhs) const {
		return Point(x - rhs.x, y - rhs.y);
	}
	Point operator*(const coord_t rhs) const {
		return Point(x * rhs, y * rhs);
	}
	Point operator/(const coord_t rhs) const {
		return Point(x / rhs, y / rhs);
	}
	coord_t operator*(const Point& rhs) const {
		return (x * rhs.x) + (y * rhs.y);
	}
	coord_t cross(const Point& rhs) const {
		return (x * rhs.y) - (y * rhs.x);
	}
	Point norm() {
		return Point(-y, x);
	}
	coord_t sqmag() {
		return x*x + y*y;
	}
	coord_t mag() {
		return sqrt(sqmag());
	}
	Point unit() {
		coord_t m = mag();
		return Point(x/m, y/m);
	}
	bool operator<(const Point& rhs) const {
		if (x == rhs.x) return y < rhs.y;
		else return x < rhs.x;
	}
	bool operator>(const Point& rhs) const {
		if (x == rhs.x) return y > rhs.y;
		else return x > rhs.x;
	}
	bool operator==(const Point& rhs) const {
		return x == rhs.x && y == rhs.y;
	}
	bool operator!=(const Point& rhs) const {
		return x != rhs.x || y != rhs.y;
	}
	friend ostream& operator<<(ostream& os, const Point& rhs) {
		os << "(" << rhs.x << ", " << rhs.y << ")";
		return os;
	}
};

struct Line {
	Point s, e;
	Line() : s(), e() {}
	Line(Point s, Point e) : s(s), e(e) {}
	Point vel() {
		return e - s;
	}
	friend ostream& operator<<(ostream& os, const Line& rhs) {
		os << rhs.s << " - " << rhs.e;
		return os;
	}
	bool contains(Point pt) {
		if (s == e) return pt == s;
		Point proj = Point((pt - s) * vel(), (pt - s) * vel().norm()) / vel().sqmag();
		if (0 <= proj.x && proj.x <= 1) proj.x = 0;
		return proj.mag() <= EPS;
	}
	pair<bool, Line> intersection(Line rhs) {
		Line lhs = *this;
		Point lv = lhs.vel(), rv = rhs.vel();
		coord_t den = lv.cross(rv);
		Point num = (lv * rhs.s.cross(rhs.e) - rv * lhs.s.cross(lhs.e)) * sgn(den);
		den *= sgn(den);
		if (den == 0) {	// Parallel or Point
			if (lv.cross(rhs.s-lhs.s) == 0 && rv.cross(lhs.s-rhs.s) == 0) {	// Collinear or Point
				if (lhs.s > lhs.e) swap(lhs.s, lhs.e);
				if (rhs.s > rhs.e) swap(rhs.s, rhs.e);
				Line result(max(lhs.s, rhs.s), min(lhs.e, rhs.e));
				if (result.s > result.e) {
					return pair<bool, Line>(false, Line());
				} else {
					return pair<bool, Line>(true, result);
				}
			} else {
				return pair<bool, Line>(false, Line());
			}
		} else {
			Point inter = num / den;
			return pair<bool, Line>(lhs.contains(inter) && rhs.contains(inter), Line(inter, inter));
		}
	}
};

const int MAXN = 200, MAXENDS = 2*MAXN+5;
int DPF[4][MAXENDS][MAXN][MAXN], DPG[4][MAXN][MAXN][MAXN], V[MAXENDS], L[MAXENDS], R[MAXENDS], N, W[MAXN], endpts[4];
bool adjmat[MAXN][MAXN];

int dpg(int ropt, int xp, int x, int y);

int dpf(int ropt, int l, int x, int y) {
	if (DPF[ropt][l][x][y] != -1) return DPF[ropt][l][x][y];
	int r;
	if (ropt == 0) r = L[x];
	else if (ropt == 1) r = R[x];
	else if (ropt == 2) r = L[y];
	else r = R[y];
	int mx = 0;
	for (int k = l+1; k < r; ++k) if (L[V[k]] == k && R[V[k]] < r) {
		if (adjmat[V[k]][x] || adjmat[V[k]][y]) continue;
		mx = max(mx, dpg(ropt, V[k], x, y));
	}
	return DPF[ropt][l][x][y] = mx;
}

int dpg(int ropt, int xp, int x, int y) {
	if (DPG[ropt][xp][x][y] != -1) return DPG[ropt][xp][x][y];
	int r;
	if (ropt == 0) r = L[x];
	else if (ropt == 1) r = R[x];
	else if (ropt == 2) r = L[y];
	else r = R[y];
	int mx = 0;
	for (int k = L[xp]+1; k < R[xp]; ++k) if (L[V[k]] == k && R[V[k]] < r) {
		if (!adjmat[V[k]][xp]) continue;
		if (adjmat[V[k]][x] || adjmat[V[k]][y]) continue;
		int sc = W[V[k]]+W[xp]+dpf(ropt,max(R[xp],R[V[k]]),x,y);
		sc += dpf(2, L[xp], xp, V[k]);
		if (R[V[k]] < R[xp]) {
			sc += dpf(3, L[V[k]], xp, V[k]);
			sc += dpf(1, R[V[k]], xp, V[k]);
		} else {
			sc += dpf(1, L[V[k]], xp, V[k]);
			sc += dpf(3, R[xp], xp, V[k]);
		}
		mx = max(mx, sc);
	}

	return DPG[ropt][xp][x][y] = mx;
}

int n4solve(vector<vector<Line>> wires, vector<int> weights) {
	wires.push_back({Line(Point(-1e9, 0), Point(-1e9, 1e9)), Line(Point(-1e9, 1e9), Point(1e9, 1e9)), Line(Point(1e9, 1e9), Point(1e9, 0))});
	weights.push_back(0);
	N = wires.size();
	for (int u = 0; u < N; ++u) W[u] = weights[u];
	for (int u = 0; u < N; ++u) for (int v = u+1; v < N; ++v) {
		bool inter = 0;
		for (auto &ul : wires[u]) for (auto &vl : wires[v]) {
			if (ul.intersection(vl).first) {
				inter = 1;
				break;
			}
		}
		adjmat[u][v] = adjmat[v][u] = inter;
	}
	vector<pair<int, int>> ends;
	for (int u = 0; u < N; ++u) {
		ends.emplace_back(wires[u][0].s.x, u);
		ends.emplace_back(wires[u].back().e.x, u);
	}
	sort(ends.begin(), ends.end());
	set<int> seen;
	for (int i = 0; i < ends.size(); ++i) {
		V[i] = ends[i].second;
		if (seen.count(V[i])) R[V[i]] = i;
		else {
			seen.insert(V[i]);
			L[V[i]] = i;
		}
	}
	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < MAXN; ++j)
			for (int k = 0; k < MAXN; ++k) {
				for (int l = 0; l < MAXN; ++l) DPG[i][j][k][l] = -1;
				for (int l = 0; l < MAXENDS; ++l) DPF[i][l][k][j] = -1;
			}
	return dpf(1, 0, N-1, N-1);
}


int main() {
	cin >> N;
	vector<vector<Line>> wires(N);
	vector<int> weights(N);
	for (int i = 0; i < N; ++i) {
	    cin >> weights[i];
		int w;
		cin >> w;
		Point lastpt(0, -1);
		for (int j = 0; j < w; ++j) {
			int x, y;
			cin >> x >> y;
			if (lastpt.y >= 0) wires[i].emplace_back(lastpt, Point(x, y));
			lastpt = Point(x, y);
		}
	}
	
	cout << n4solve(wires, weights) << endl;
}