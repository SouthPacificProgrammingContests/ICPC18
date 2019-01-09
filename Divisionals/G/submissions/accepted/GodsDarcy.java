import java.util.*;

public class GodsDarcy {
  public static void main(String[] args) {
    new GodsDarcy().run();
  }

  void run(){
    Scanner in = new Scanner(System.in);

    String s = in.next();
    for(int i=s.length()-1;i>=0;i--)
      for(int j=0;j<3;j++)
        System.out.print(s.charAt(i));
    System.out.println();
  }
}
