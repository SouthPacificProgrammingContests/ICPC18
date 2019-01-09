import java.io.PrintWriter;
import java.util.Scanner;

public class Main {
  public static void main(String[] args) {
    Scanner in = new Scanner(System.in);
    PrintWriter out = new PrintWriter(System.out);

    int m = in.nextInt();
    int n = in.nextInt();

    int sum = 0;
    for (int i = 0; i < m; i++) {
      sum += in.nextInt();
    }

    int ans = (sum + n - 1) / n;
    out.println(ans);
    out.close();
  }
}
