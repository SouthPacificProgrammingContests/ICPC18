import java.util.*;

public class DubiousDarcy {
  public static void main(String[] args) {
    new DubiousDarcy().run();
  }
  
  void run() {
    Scanner in = new Scanner(System.in);
    
    long n = in.nextLong();

    long A[] = new long[(int)n];
    for(int i=0;i<n;i++)
      A[i] = in.nextLong();

    long tot = 0;
    for(int i=0;i<n;i++)
    tot += (i+1) * A[i] * (n-i);

    long den = n * (n+1) / 2;
    long g = gcd(tot, den);
    
    System.out.println(tot/g + "/" + den/g);
  }
  
  long gcd(long a, long b){
    return (b == 0 ? a : gcd(b,a%b));
  }
}
