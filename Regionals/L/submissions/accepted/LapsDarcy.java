import java.util.*;

public class DroppingDarcy {
  public static void main(String[] args) {
    new DroppingDarcy().run();
  }

  void run() {
    Scanner in = new Scanner(System.in);

    int n = in.nextInt();
    int m = in.nextInt();

    int[] A = new int[m];
    for(int i=0;i<m;i++)
      A[i] = in.nextInt();

    int ans = 0;
    for(int i=1;i<m;i++)
      if(A[i] < A[i-1])
        ans++;

    System.out.println(ans);
  }
}
