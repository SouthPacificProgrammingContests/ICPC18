import java.util.*;

public class FurthestDarcy {
  public static void main(String[] args) {
    new FurthestDarcy().run();
  }

  int budget;

  void run() {
    Scanner in = new Scanner(System.in);

    int n = in.nextInt();
    budget = in.nextInt();

    int power = 0;
    while((1 << power) <= budget) power++;
    power++;

    int[][][] pow2 = new int[power][n][n];

    for(int i=0;i<n;i++)
      for(int j=0;j<n;j++)
        pow2[0][i][j] = in.nextInt();

    for(int i=1;i<power;i++)
      pow2[i] = multiply(pow2[i-1], pow2[i-1]);

    int[][] ans = new int[n][n];
    for(int i=0;i<n;i++)
      for(int j=0;j<n;j++)
        ans[i][j] = (i == 0 && j == 0 ? 0 : budget+1);

    int[][] tmp = new int[n][n];
    int the_answer = 0;
    for(int i=power-1;i>=0;i--){
      tmp = multiply(ans, pow2[i]);
      int mini = budget+1;
      for(int j=0;j<n;j++) mini = Math.min(mini, tmp[0][j]);
      if(mini <= budget){
        for(int j=0;j<n;j++)
          for(int k=0;k<n;k++)
            ans[j][k] = tmp[j][k];
        the_answer |= (1 << i);
      }
    }
    
    System.out.println(the_answer);
  }

  int[][] multiply(int[][] A, int[][] B){
    int n = A.length;
    int[][] C = new int[n][n];

    for(int i=0;i<n;i++)
      for(int j=0;j<n;j++){
        C[i][j] = budget+1;
        for(int k=0;k<n;k++)
        if(C[i][j] > A[i][k] + B[k][j])
          C[i][j] = A[i][k] + B[k][j];
      }
    return C;
  }
}
