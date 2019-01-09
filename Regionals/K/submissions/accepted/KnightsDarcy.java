import java.util.*;
import java.io.*;

public class KnightsDarcy {
  static StreamTokenizer st = new StreamTokenizer(new BufferedReader(new InputStreamReader(System.in)));
  static int readi() throws IOException {
    st.nextToken();
    return new Integer(st.sval).intValue();
  } 
  public static void main(String[] args) throws Exception {
    new KnightsDarcy().run();
  }

  void run() throws Exception {
    // Scanner in = new Scanner(System.in);

    int n = readi();

    Point[] P = new Point[n];
    for(int i=0;i<n;i++)
      P[i] = new Point(readi(), readi(), i);

    boolean[] ans = convex_hull(P);
    StringBuilder S = new StringBuilder();
    for(int i=0;i<n;i++){
      if(!ans[i]) S.append('Y');
      else S.append('N');
    }
    System.out.println(S.toString());
  }

  Point start_p, max_p;

  boolean[] convex_hull(Point P[]){
    int n = P.length;

    Arrays.sort(P, new XYCompare());
    boolean col = true;
    for(int i=2;i<n;i++)
      if(dir(P[0], P[1], P[i]) != 0)
        col = false;

    boolean[] ans = new boolean[n];
    if(col){
      ans[P[0].idx] = true;
      ans[P[n-1].idx] = true;
      return ans;
    }

    start_p = P[0];

    int best_i = 1;
    for(int i=2;i<n;i++)
      if(dir(P[0],P[best_i], P[i]) == 1)
        best_i = i;
    max_p = P[best_i];

    Point[] Q = new Point[n-1];
    for(int i=0;i<n-1;i++) Q[i] = P[i+1];
    Arrays.sort(Q, new AngleComparator());

    Point[] hull = new Point[n];
    int ctr = 2;
    hull[0] = P[0];
    hull[1] = Q[0];
    for(int i=1;i<n-1;i++){
      while(ctr > 1 && dir(hull[ctr-2], hull[ctr-1], Q[i]) != 1)
        ctr--;
      hull[ctr++] = Q[i];
    }

    for(int i=0;i<ctr;i++)
      if(dir(hull[(i+ctr-1)%ctr], hull[i], hull[(i+1)%ctr]) != 0)
        ans[hull[i].idx] = true;
    return ans;
  }

  class Point {
    long x, y;
    int idx;

    Point(long X, long Y, int IDX){
      x = X;
      y = Y;
      idx = IDX;
    }
  }

  class XYCompare implements Comparator<Point> {
    @Override
    public int compare(Point a, Point b) {
      if(a.y != b.y) return (int)(b.y - a.y);
      return (int)(b.x - a.x);
    }
  }

  class AngleComparator implements Comparator<Point> {
    @Override
    public int compare(Point a, Point b) {
      if(a.x == b.x && a.y == b.y) return 0;
      if((dir(start_p, a, max_p) == 0 && dir(start_p, b, max_p) == 0)){
        long dx1 = Math.abs(start_p.x - a.x);
        long dx2 = Math.abs(start_p.x - b.x);
        long dy1 = Math.abs(start_p.y - a.y);
        long dy2 = Math.abs(start_p.y - b.y);
        if(dx1 != dx2) return (dx1 > dx2 ? -1 : 1);
        return (dy1 > dy2 ? -1 : 1);
      }
      if(dir(start_p, a, b) == 0) {
        long dx1 = Math.abs(start_p.x - a.x);
        long dx2 = Math.abs(start_p.x - b.x);
        long dy1 = Math.abs(start_p.y - a.y);
        long dy2 = Math.abs(start_p.y - b.y);
        if(dx1 != dx2) return (dx1 > dx2 ? 1 : -1);
        return (dy1 > dy2 ? 1 : -1);
      }
      return -dir(start_p, a, b);
    }
  }
  
  long dot   (Point p, Point q) { return p.x*q.x + p.y*q.y; }
  long cross (Point p, Point q) { return p.x*q.y - p.y*q.x; }
  long len2  (Point p)          { return dot(p,p); }
  Point sub(Point p, Point q)   { return new Point(p.x-q.x,p.y-q.y,-1); }
  boolean  eq(Point p, Point q) { return p.x == q.x && p.y == q.y; }

  int dir(Point p, Point q, Point r) {
    long c = cross(sub(q,p), sub(r,q));
    if(c == 0) return 0;
    return (c < 0 ? -1 : 1);
  }
  
  boolean on_seg(Point a, Point b, Point p){
    return (Math.min(a.x,b.x) <= p.x && p.x <= Math.max(a.x,b.x)) &&
      (Math.min(a.y,b.y) <= p.y && p.y <= Math.max(a.y,b.y));
  }
  
  boolean intersect(Point a1, Point a2, Point b1, Point b2){
    int d1 = dir(a1,a2,b1), d2 = dir(a1,a2,b2);
    int d3 = dir(b1,b2,a1), d4 = dir(b1,b2,a2);
    if(d1 != d2 && d1 == -d2 && d3 != d4 && d3 == -d4) return true;
    
    return (d1 == 0 && on_seg(a1,a2,b1)) ||
      (d2 == 0 && on_seg(a1,a2,b2)) ||
      (d3 == 0 && on_seg(b1,b2,a1)) ||
      (d4 == 0 && on_seg(b1,b2,a2));  
  }
}
