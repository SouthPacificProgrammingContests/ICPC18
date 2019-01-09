import java.util.*;

public class DroppingDarcy {
  public static void main(String[] args) {
    new DroppingDarcy().run();
  }

  void run() {
    Scanner in = new Scanner(System.in);

    int n = in.nextInt();

    int[] A = new int[n+1];
    for(int i=0;i<n;i++)
      A[i] = in.nextInt();

    String ans = "YES";
    int forced_right = 0;
    for(int i=0;i<n;i++){
      if(A[i] < forced_right) ans = "NO";
      forced_right += Math.max(0, A[i+1] - A[i]);
    }
    
    System.out.println(ans);
  }
}
