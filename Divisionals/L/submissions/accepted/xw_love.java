import static java.lang.Math.abs;
import static java.lang.Math.cos;
import static java.lang.Math.sin;
import static java.lang.Math.PI;

import java.io.PrintWriter;
import java.util.Scanner;

public class Main {

  private static double cosineRule(double a, double b, double c) {
    return Math.acos((b*b + c*c - a*a) / (2. * b * c));
  }

  private static double Min(double ... args) {
    double result = Double.MAX_VALUE;
    for (double d : args) {
      result = Math.min(result, d);
    }
    return result;
  }

  private static double solve(double a, double b, double c) {
    double C = cosineRule(c, a, b);
    if (C > PI / 2.0) {
      double x = a + b * cos(PI - C);
      double y = b * cos(PI / 2.0 - C);
      return Math.max(x ,y);
    }
    double lo = 0.0, hi = (PI / 2.0 - C);
    for (int iter = 0; iter < 200 && abs(hi - lo) > 1e-10; iter++) {
      double t = (lo + hi) / 2.0;
      double x = Math.max(b * cos(C + t), a * cos(t));
      double y = Math.max(b * sin(C + t), a * sin(t));
      if (x > y) {
        lo = t;
      } else {
        hi = t;
      }
    }
    double t = (lo + hi) / 2.0;
    return Math.max(
        Math.max(b * cos(C + t), a * cos(t)),
        Math.max(b * sin(C + t), a * sin(t)));
  }

  public static void main(String[] args) {
    Scanner in = new Scanner(System.in);
    PrintWriter out = new PrintWriter(System.out);
    double a = in.nextInt();
    double b = in.nextInt();
    double c = in.nextInt();

    double ans = Min(
        solve(a, b, c),
        solve(a, c, b),
        solve(b, a, c),
        solve(b, c, a),
        solve(c, a, b),
        solve(c, b, a)
    );
    out.println(ans);
    out.close();
  }
}
