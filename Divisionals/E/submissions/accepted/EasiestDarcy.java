import java.util.*;

public class EasiestDarcy {
  public static void main(String[] args) {
    new EasiestDarcy().run();
  }

  void run(){
    Scanner in = new Scanner(System.in);

    int n = in.nextInt();
    String ans = "";
    int rank_a = 3*101, rank_b = 101;

    for(int i=0;i<n;i++){
      String prob = in.next();
      int a = in.nextInt();
      int b = a+in.nextInt()+in.nextInt();
      if(b < rank_a || (b == rank_a && a < rank_b)){
         rank_a = b; rank_b = a; ans = prob;
      }
    }
    
    System.out.println(ans);
  }
}
