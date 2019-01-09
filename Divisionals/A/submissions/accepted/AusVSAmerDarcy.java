import java.util.*;

public class AusVSAmerDarcy {
  public static void main(String[] args) {
    new AusVSAmerDarcy().run();
  }

  String output;
  String[] input;
  int n;

  void run(){
    Scanner in = new Scanner(System.in);

    n = in.nextInt();

    input = new String[n];
    for(int i=0;i<n;i++)
      input[i] = in.next();

    output = "IMPOSSIBLE";
    check("YY/MM/DD");
    check("YY/DD/MM");
    check("MM/YY/DD");
    check("MM/DD/YY");
    check("DD/YY/MM");
    check("DD/MM/YY");
    
    System.out.println(output);
  }
  
  void check(String s){
      int[] dom = {31,29,31,30,31,30,31,31,30,31,30,31};
      for(int i=0;i<n;i++){
          int y=-1, m=-1, d=-1;
          String v[] = input[i].split("/");
          for(int j=0;j<3;j++){
              if(s.charAt(3*j) == 'D') d = Integer.parseInt(v[j]);
              if(s.charAt(3*j) == 'M') m = Integer.parseInt(v[j]);
              if(s.charAt(3*j) == 'Y') y = Integer.parseInt(v[j]);
          }
          if(!(1 <= m && m <= 12)) return;
          if(!(1 <= d && d <= dom[m-1])) return;
          if(m == 2 && d == 29 && y % 4 != 0) return;
      }
      if(output.equals("IMPOSSIBLE")) output = s;
      else output = "UNSURE";
  }
}
