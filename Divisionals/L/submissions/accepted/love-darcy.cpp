#include <bits/stdc++.h>
using namespace std;

const double PI = acosl(-1.0);
const double EPS = 1e-12;

// Vertex between side a and b in the corner.
double f(double a, double b, double c){
	if(a < b) swap(a,b);
	// Use cosine law to find the angle in the corner
	double theta = acos( (a*a + b*b - c*c) / (2*a*b) );


	// Boundary conditions!
	// (a) Will this triangle fit into this quadrant?
	if(theta > PI/2)
		return max({a,b,c}); // This is the worst case scenario
	
	// (b) Can we use the main diagonal?
	if(theta <= PI/4){
		double width  = a * cos(PI/4);
		double height = b * cos(PI/4 - theta);
		if(height < width)
			return width;
	}

	// We now want to find phi so that
	// a * cos(phi) = b * cos(PI/2 - theta - phi)
	// Answer is then a * cos(phi)

	double lo = 0, hi = min(PI/4,PI/2 - theta);
	while(hi - lo > EPS){
		double mid = (lo + hi)/2;
		double left = a * cos(mid);
		double right = b * cos(PI/2 - theta - mid);

		(left > right ? lo : hi) = mid;
	}

	return a * cos((lo+hi)/2);
}

int main(){
	int a, b, c;
	cin >> a >> b >> c;

	cout << fixed << setprecision(13);
	cout << min({f(a,b,c),f(b,c,a), f(c,a,b)}) << endl;
}
