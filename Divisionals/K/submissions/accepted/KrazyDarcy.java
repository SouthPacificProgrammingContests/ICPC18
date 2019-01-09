import java.util.*;

public class KrazyDarcy {
  public static void main(String[] args) {
    new KrazyDarcy().run();
  }

  int n;
  int[] D;
  int[][] A;

  void run(){
    Scanner in = new Scanner(System.in);
    
    n = in.nextInt();
    int x = in.nextInt(), y = in.nextInt();

    A = new int[n][n];

    for(int i=0;i<x;i++){
      int u = in.nextInt()-1, v = in.nextInt()-1;
      A[u][v] = A[v][u] = 2;
    }
    for(int i=0;i<y;i++){
      int u = in.nextInt()-1, v = in.nextInt()-1;
      A[u][v] = 2;
      if(A[v][u] == 0) A[v][u] = 1;
    }

    D = new int[n];

    dfs(0,1);
    dfs(0,2);

    String[] output = {"Impossible", "Ticket", "No Ticket"};

    for(int i=0;i<n;i++) System.out.println(output[D[i]]);
  }

  void dfs(int v, int val){
    D[v] = val;
    for(int i=0;i<n;i++)
      if(A[v][i] >= val && D[i] != val)
        dfs(i, val);
  }
}
