import java.util.*;

public class FlowDarcy {
  public static void main(String[] args) {
    new FlowDarcy().run();
  }
  
  void run() {
    Scanner in = new Scanner(System.in);

    int m = in.nextInt();
    int n = in.nextInt();

    int sum = 0;
    for(int i=0;i<m;i++)
      sum += in.nextInt();

    System.out.println((sum + n - 1) / n);
  }
}
