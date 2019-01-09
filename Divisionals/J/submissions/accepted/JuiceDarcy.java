import java.util.*;

public class JuiceDarcy {
  public static void main(String[] args) {
    new JuiceDarcy().run();
  }
    
  void run() {
    Scanner in = new Scanner(System.in);

    int n = in.nextInt();
    int C = in.nextInt();

    int LCM = 8 * 9 * 5 * 7;
    
    n *= LCM;

    int[] DP = new int[n+1];
    Arrays.fill(DP,-1);
    DP[0] = 0;

    for(int i=0;i<C;i++){
      int x = in.nextInt();
      int y = in.nextInt();
      x *= LCM / y;

      for(int j=0;j+x<=n;j++){
	if(DP[j] == -1) continue;
	if(DP[j+x] == -1 || DP[j+x] > DP[j] + 1)
	  DP[j+x] = DP[j] + 1;
      }	
    }

    System.out.println(DP[n]);
  }
}
