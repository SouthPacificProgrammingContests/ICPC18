#include <bits/stdc++.h>

using namespace std;

typedef long long coord_t; // Type for point coordinates

struct Point {
	coord_t x, y;
	int i;
	Point() { x = y = 0; }
	Point(coord_t _x, coord_t _y) { x = _x; y = _y; }
	Point(coord_t _x, coord_t _y, int _i) { x = _x; y = _y; i = _i; }
	inline bool operator<(const Point& pt) const {
		if (x != pt.x)
			return x < pt.x;
		return y < pt.y;
	}
};

typedef vector<Point> Polygon;

/* cross_product(o, a, b)
 * Returns the cross product of (a-o)X(b-o)
 */
inline coord_t cross_product(const Point& o, const Point& a, const Point& b) {
	return (a.x - o.x) * (b.y - o.y) - (a.y - o.y) * (b.x - o.x);
}

/* convex_hull(points)
 * Takes a vector of pairs of integers representing points in 2D space.
 * Returns the convex hull of this set of points, represented as a
 * counter-clockwise ordered vector of pairs of integers representing the
 * vertices of the convex hull.
 * O(N log N)
 */
Polygon convex_hull(Polygon& points) {
	if (points.size() <= 2) return points; // Minimal case
	sort(points.begin(), points.end()); // Sort lexographically (by x, then y)
	Polygon upper, lower; // Upper and lower parts of the convex hull

	for(int i = 0; i < points.size(); i++) { // Iterate through points, L to R
		// Remove any "left" turns by removing internal points
		while (upper.size() >= 2 && cross_product(upper[upper.size()-2],
					upper[upper.size()-1], points[i]) >= 0) {
			upper.pop_back();
		}
		upper.push_back(points[i]); // Add the current point to the upper hull
		// Remove any "right" turns by removing internal points
		while (lower.size() >= 2 && cross_product(lower[lower.size()-2],
					lower[lower.size()-1], points[i]) <= 0) {
			lower.pop_back(); 
		}
		lower.push_back(points[i]); // Add the current point to the lower hull
	}
	
	// Reverse the upper hull to make it counter-clockwise
	reverse(upper.begin(), upper.end()); 
	upper.pop_back(); // Remove duplicate rightmost point
	lower.pop_back(); // Remove duplicate leftmost point
	// Concatenate upper hull onto lower to form full convex hull
	lower.insert(lower.end(), upper.begin(), upper.end()); 

	return lower; // Return full convex hull
}

int main() {
	int N;
	cin >> N;
	vector<Point> pts(N);
	for (int i = 0; i < N; ++i) {
		cin >> pts[i].x >> pts[i].y;
		pts[i].i = i;
	}
	auto hull = convex_hull(pts);
	vector<int> y(N, 1);
	for (auto &pt : hull) y[pt.i] = 0;
	for (int i = 0; i < N; ++i) {
		cout << (y[i] ? 'Y' : 'N');
	}
	cout << endl;
}
