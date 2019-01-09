// solution of problem "A long, long way"

import java.io.*;

public class far {

  static StreamTokenizer st = new StreamTokenizer(new BufferedReader(new InputStreamReader(System.in)));
  static int readi() throws IOException {
    st.nextToken();
    return new Integer(st.sval).intValue();
  }

  static final long infty = 1<<30;

  // minimal-cost matrix product m1 * m2
  static long[][] mult(long[][] m1, long[][] m2) {
    int n = m1.length;
    long res[][] = new long[n][n];
    for (int i=0 ; i<n ; i++)
      for (int j=0 ; j<n ; j++)
        res[i][j] = infty;
    for (int i=0 ; i<n ; i++)
      for (int j=0 ; j<n ; j++)
        for (int k=0 ; k<n ; k++)
          res[i][j] = Math.min(res[i][j], m1[i][k] + m2[k][j]);
    return res;
  }

  static boolean anyBelow(long[] a, long m) {
    for (long x : a)
      if (x <= m)
        return true;
    return false;
  }

  public static void main(String[] args) throws Exception {
    st.ordinaryChars('0', '9');
    st.wordChars('0', '9');
    int n = readi(), m = readi();
    long c[][][] = new long[32][n][n];
    for (int i=0 ; i<n ; i++)
      for (int j=0 ; j<n ; j++)
        c[0][i][j] = readi();
    // matrix powers c[x] = c[0]^2^x, minimal costs for paths of length 2^x
    int k = 0;
    for ( ; anyBelow(c[k][0], m) ; k++)
      c[k+1] = mult(c[k], c[k]);
    // iteration stops if minimal cost from location 0 exceeds m
    if (k == 0) {
      // get nowhere as every leg from location 0 exceeds m
      System.out.println(0);
      return;
    }
    // maximise len such that minimal cost from location 0 in c[0]^len is <= m
    // binary search works as minimal cost increases with len
    // construct len bit-by-bit, the k-th bit is 1
    k--;
    long cc[][] = c[k];
    int len = 1<<k;
    for (k-- ; k>=0 ; k--) {
      long[][] c1 = mult(cc, c[k]);
      // try 1 for the k-th bit of len
      if (anyBelow(c1[0], m)) {
        cc = c1;
        len += 1<<k;
      }
    }
    System.out.println(len);
  }

}

