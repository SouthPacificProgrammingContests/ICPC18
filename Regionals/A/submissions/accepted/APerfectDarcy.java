import java.util.*;

public class APerfectDarcy {
  public static void main(String[] args) {
    new APerfectDarcy().run();
  }

  void run() {
    System.out.println(f() ? "Yes" : "No");
  }
  
  boolean f(){
    Scanner in = new Scanner(System.in);
    
    int n = in.nextInt();
    int L = in.nextInt();
    
    int len = 0;
    for(int i=0;i<n;i++)
      len += in.next().length();

    int blanks = L - len;
    if(blanks < n-1) return false;
    if(n == 1) return blanks == 0;
    return blanks % (n-1) == 0;
  }
}
