import java.util.*;

public class BadDarcy {
  public static void main(String[] args) {
    new BadDarcy().run();
  }

  void run() {
    Scanner in = new Scanner(System.in);

    String s = in.next();

    int n = s.length();

    if(n <= 3){
      System.out.println(n);
      return;
    }

    int the_ans = 2;
    for(int st=0;st<2;st++){

      StringBuilder t = new StringBuilder();
      for(int j=st;j<n;j+=2)
        t.append(s.charAt(j));
      the_ans = Math.max(the_ans, 2*kmpMatcher(s,t.toString()) + st);
    }
    
    System.out.println(Math.min(the_ans, n));
  }

  public static int[] prefixFunction(String s) {
    int[] p = new int[s.length()];
    int k = 0;
    for (int i = 1; i < s.length(); i++) {
      while (k > 0 && s.charAt(k) != s.charAt(i))
        k = p[k - 1];
      if (s.charAt(k) == s.charAt(i))
        ++k;
      p[i] = k;
    }
    return p;
  }

  public static int kmpMatcher(String s, String pattern) {
    int m = pattern.length();
    if (m == 0)
      return 0;
    int maxi = 0;
    int[] p = prefixFunction(pattern);
    for (int i = 0, k = 0; i < s.length(); i++)
      for (; ; k = p[k - 1]) {
        if (pattern.charAt(k) == s.charAt(i)) {
          if (++k == m)
            return m;
          maxi = Math.max(k, maxi);
          break;
        }
        if (k == 0)
          break;
      }
    return maxi;
  }
}
