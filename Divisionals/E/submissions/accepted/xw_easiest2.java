import java.io.PrintWriter;
import java.util.Scanner;

public class Main {
  public static void main(String[] args) {
    Scanner in = new Scanner(System.in);
    PrintWriter out = new PrintWriter(System.out);

    int P = in.nextInt();
    int Ma = Integer.MAX_VALUE;
    int cap = -1;
    String ans = null;

    for (int i = 0; i < P; i++) {
      String prob = in.next();
      int a = in.nextInt();
      int b = in.nextInt();
      int c = in.nextInt();
      int sum = a + b + c;
      if (sum < Ma || (sum == Ma && a < cap)) {
        Ma = sum;
        cap = a;
        ans = prob;
      }
    }
    out.println(ans);
    out.close();
  }
}
