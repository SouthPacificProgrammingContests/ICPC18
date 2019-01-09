import java.util.*;

public class BombsDarcy {
  public static void main(String[] args) {
    new BombsDarcy().run();
  }

  int[][] t;

  void run(){
    Scanner in = new Scanner(System.in);

    int m = in.nextInt();
    int n = in.nextInt();
    int K = in.nextInt();

    String[] A = new String[m];

    for(int i=0;i<m;i++)
      A[i] = in.next();

    t = new int[m+1][n+1];

    int[] q = new int[n*m];
    int st = 0, en = 0;

    int[][] D = new int[m][n];
    for(int i=0;i<m;i++)
      for(int j=0;j<n;j++)
        D[i][j] = -1;


    for(int i=0;i<m;i++)
      for(int j=0;j<n;j++){
        if(A[i].charAt(j) == 'S'){
          q[en] = i*n + j;
          en++;
          D[i][j] = 0;
        }
        if(A[i].charAt(j) == 'X')
          rec(i, j, i, j, 1);
      }

    int[] di = {-1,-1,-1, 0, 0, 1, 1, 1};
    int[] dj = {-1, 0, 1,-1, 1,-1, 0, 1};
    
    for(int KK=0;KK<K;KK++){
      int r1 = in.nextInt()-1;
      int c1 = in.nextInt()-1;
      int r2 = in.nextInt()-1;
      int c2 = in.nextInt()-1;
      rec(r1, c1, r2, c2, 1);

      int last = en;
      while(st != last){
        int curr = q[st];
        st++;
        int I = curr / n, J = curr % n;
        for(int k=0;k<8;k++){
          int nI = I + di[k], nJ = J + dj[k];
          if(!(0 <= nI && nI < m && 0 <= nJ && nJ < n)) continue;
          if(D[nI][nJ] != -1) continue;
          if(sum(nI,nJ) > 0) continue;
          D[nI][nJ] = D[I][J] + 1;
          q[en] = nI*n + nJ;
          en++;
        }
      }
    }

    for(int i=0;i<m;i++)
      for(int j=0;j<n;j++)
        if(D[i][j] != -1 && sum(i,j) == 0){
          System.out.println((i+1) + " " + (j+1));
          return;
        }
    System.out.println(-1);
  }

  void add(int r, int c, int value) {
    for (int i = r; i < t.length; i |= i + 1)
      for (int j = c; j < t[0].length; j |= j + 1)
        t[i][j] += value;
  }

  void rec(int r1, int c1, int r2, int c2, int value) {
    add(r1, c1, 1);
    add(r1, c2+1, -1);
    add(r2+1, c1, -1);
    add(r2+1, c2+1, 1);
  }

  // sum[(0, 0), (r, c)]
  int sum(int r, int c) {
    int res = 0;
    for (int i = r; i >= 0; i = (i & (i + 1)) - 1)
      for (int j = c; j >= 0; j = (j & (j + 1)) - 1)
        res += t[i][j];
    return res;
  }

  // sum[(r1, c1), (r2, c2)]
  int sum(int r1, int c1, int r2, int c2) {
      int ans = sum(r2, c2);
      if(r1 > 0) ans -= sum(r1-1,c2);
      if(c1 > 0) ans -= sum(r2,c1-1);
      if(r1 > 0 && c1 > 0) ans += sum(r1-1,c1-1);
      return ans;
  }

  int get(int r, int c) {
    return sum(r, c, r, c);
  }
}
