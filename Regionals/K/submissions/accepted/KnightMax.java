
import java.util.*;
import java.io.*;


class KnightMax {

	static StreamTokenizer st = new StreamTokenizer(new BufferedReader(new InputStreamReader(System.in)));
  static int readi() throws IOException {
    st.nextToken();
    return new Integer(st.sval).intValue();
  }

  
	class Point implements Comparable<Point> {
		long x, y;
		int i;
		Point() { x = y = 0; }
		Point(long _x, long _y) { x = _x; y = _y; }
		public int compareTo( Point pt)  {
			if (x != pt.x)
				return (int)x - (int)pt.x;
			return (int)y - (int)pt.y;
		}
	}


	/* cross_product(o, a, b)
	 * Returns the cross product of (a-o)X(b-o)
	 */
	long cross_product( Point o,  Point a,  Point b) {
		return (a.x - o.x) * (b.y - o.y) - (a.y - o.y) * (b.x - o.x);
	}

	ArrayList<Point> convex_hull(Point[] points) {
		if (points.length <= 2) return new ArrayList<Point>(Arrays.asList(points)); // Minimal case
		Arrays.sort(points); // Sort lexographically (by x, then y)
		ArrayList<Point> upper = new ArrayList<Point>(), lower = new ArrayList<Point>(); // Upper and lower parts of the convex hull

		for(int i = 0; i < points.length; i++) { // Iterate through points, L to R
			// Remove any "left" turns by removing internal points
			while (upper.size() >= 2 && cross_product(upper.get(upper.size()-2),
						upper.get(upper.size()-1), points[i]) >= 0) {
				upper.remove(upper.size()-1);
			}
			upper.add(points[i]); // Add the current point to the upper hull
			// Remove any "right" turns by removing internal points
			while (lower.size() >= 2 && cross_product(lower.get(lower.size()-2),
						lower.get(lower.size()-1), points[i]) <= 0) {
				lower.remove(lower.size()-1); 
			}
			lower.add(points[i]); // Add the current point to the lower hull
		}
		
		// Reverse the upper hull to make it counter-clockwise
		Collections.reverse(upper);
		upper.remove(upper.size()-1);
		lower.remove(lower.size()-1);

		for (Point pt : upper) lower.add(pt);

		return lower; // Return full convex hull
	}


	public void run() throws Exception {
		// Scanner sc = new Scanner(System.in);
		int N = readi();
		Point[] pts = new Point[N];
		for (int i = 0; i < N; ++i) {
			pts[i] = new Point(readi(), readi());
			pts[i].i = i;
		}
		ArrayList<Point> hull = convex_hull(pts);
		boolean[] y = new boolean[N];
		for (Point pt : hull) {
			//System.out.println(pt.i);
			y[pt.i] = true;
		}
		for (int i = 0; i < N; ++i) {
			System.out.print(y[i] ? 'N' : 'Y');
		}
		System.out.println();

	}

	public static void main(String[] args) throws Exception {
		KnightMax sol = new KnightMax();
		sol.run();
		
	}
}
