import java.util.*;

public class ExplosionDarcy {
  public static void main(String[] args) {
    new ExplosionDarcy().run();
  }

  int[] value;
  boolean[][] intersect;
  int[] right_end;
  int[][] adj;
  int[] adj_sz;
  int[][] DP;
  int[] edgesA;
  int[] edgesB;

  void run() {
    Scanner in = new Scanner(System.in);

    int n = in.nextInt();

    Point[][] lines = new Point[n][11];
    int[] sz = new int[n];
    int[] orig_values = new int[n];

    int[] who = new int[2*n];
    for(int i=0;i<n;i++){
      orig_values[i] = in.nextInt();
      sz[i] = in.nextInt();
      for(int j=0;j<sz[i];j++){
        int x = in.nextInt(), y = in.nextInt();
        lines[i][j] = new Point(x,y);
      }
      who[2*i] = i + n*lines[i][0].x;
      who[2*i+1] = i + n*lines[i][sz[i]-1].x;
    }

    Arrays.sort(who);
    for(int i=0;i<2*n;i++) who[i] %= n;

    value = new int[2*n];

    for(int i=0;i<2*n;i++)
      value[i] = orig_values[ who[i] ];

    int[] the_right = new int[n];
    Arrays.fill(the_right, -1);
    right_end = new int[2*n+1];
    right_end[2*n] = 2*n;
    for(int i=2*n-1;i>=0;i--){
      if(the_right[ who[i] ] == -1) the_right[ who[i] ] = i;
      right_end[i] = the_right[ who[i] ];
    }

    intersect = new boolean[2*n+1][2*n+1];
    adj = new int[2*n+1][2*n+1];
    adj_sz = new int[2*n+1];

    int num_edges = 0;
    for(int i=0;i<2*n;i++)
      for(int j=i+1;j<2*n;j++)
        if(polylines_intersect(lines[who[i]], sz[who[i]], lines[who[j]], sz[who[j]]))
          num_edges++;

    num_edges++;
    edgesA = new int[num_edges];
    edgesB = new int[num_edges];
    num_edges = 0;
    for(int i=0;i<2*n;i++)
      for(int j=i+1;j<2*n;j++)
        if(polylines_intersect(lines[who[i]], sz[who[i]], lines[who[j]], sz[who[j]])){
          intersect[i][j] = intersect[j][i] = true;
          if(right_end[i] != i && right_end[j] != j){
            adj[i][adj_sz[i]] = num_edges;
            adj_sz[i]++;
            edgesA[num_edges] = i;
            edgesB[num_edges] = j;
            num_edges++;
          }
        }
    edgesA[num_edges] = 2*n;
    edgesB[num_edges] = 2*n;
    num_edges++;

    DP = new int[2*n+1][num_edges];
    for(int i=0;i<2*n+1;i++)
      Arrays.fill(DP[i], -1);
    System.out.println(f(0, num_edges-1));
  }

  int f(int idx, int ceiling){
    if(DP[idx][ceiling] >= 0) return DP[idx][ceiling];

    int c1 = edgesA[ceiling], c2 = edgesB[ceiling];
    if(c1 == idx || c2 == idx || right_end[c1] == idx || right_end[c2] == idx) return 0; // Empty range

    int x = f(idx+1, ceiling); // Don't use this wire
  
    if(right_end[idx] != idx && !intersect[idx][c1] && !intersect[idx][c2]){ // Use this wire
      for(int i=0;i<adj_sz[idx];i++){
        int e_idx = adj[idx][i];
        int you = edgesB[e_idx];
        if(intersect[you][c1] || intersect[you][c2]) continue;
        x = Math.max(x,
          value[idx] + value[you] + f(idx+1, e_idx) + f(you+1, e_idx) +
          f(Math.min(right_end[idx], right_end[you])+1, e_idx) +
          f(Math.max(right_end[idx], right_end[you])+1, ceiling));
      }
    }  

    DP[idx][ceiling] = x;
    return x;
  }

  class Point {
    int x, y;

    Point(int X, int Y){
      x = X;
      y = Y;
    }
  }
  
  int dot   (Point p, Point q) { return p.x*q.x + p.y*q.y; }
  int cross (Point p, Point q) { return p.x*q.y - p.y*q.x; }
  int len2  (Point p)          { return dot(p,p); }
  Point sub(Point p, Point q)   { return new Point(p.x-q.x,p.y-q.y); }
  boolean  eq(Point p, Point q) { return p.x == q.x && p.y == q.y; }
  
  int dir(Point p, Point q, Point r) {
    int c = cross(sub(q,p), sub(r,q));
    if(c == 0) return 0;
    return (c < 0 ? -1 : 1);
  }
  
  boolean on_seg(Point a, Point b, Point p){
    return (Math.min(a.x,b.x) <= p.x && p.x <= Math.max(a.x,b.x)) &&
      (Math.min(a.y,b.y) <= p.y && p.y <= Math.max(a.y,b.y));
  }
  
  boolean lines_intersect(Point a1, Point a2, Point b1, Point b2){
    int d1 = dir(a1,a2,b1), d2 = dir(a1,a2,b2);
    int d3 = dir(b1,b2,a1), d4 = dir(b1,b2,a2);
    if(d1 != d2 && d1 == -d2 && d3 != d4 && d3 == -d4) return true;
    
    return (d1 == 0 && on_seg(a1,a2,b1)) ||
      (d2 == 0 && on_seg(a1,a2,b2)) ||
      (d3 == 0 && on_seg(b1,b2,a1)) ||
      (d4 == 0 && on_seg(b1,b2,a2));  
  }

  boolean polylines_intersect(Point p[], int p_sz, Point q[], int q_sz){
    for(int i=0;i+1<p_sz;i++)
      for(int j=0;j+1<q_sz;j++)
        if(lines_intersect(p[i], p[i+1], q[j], q[j+1]))
          return true;
    return false;
  }
}
