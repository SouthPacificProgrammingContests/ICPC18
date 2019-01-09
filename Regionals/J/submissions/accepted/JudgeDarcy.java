import java.util.*;

public class JudgeDarcy {
  public static void main(String[] args) {
    new JudgeDarcy().run();
  }

  void run() {
    Scanner in = new Scanner(System.in);

    int n = in.nextInt();

    String[][] A = new String[n][3];
    for(int i=0;i<n;i++)
      for(int j=0;j<3;j++)
        A[i][j] = in.next();

    boolean[] selected = new boolean[n];

    String[] div = {"Central", "Western", "Eastern"};

    // Selection Step 1
    for(String d : div){
      String uni = "";
      for(int i=0;i<n;i++)
        if(A[i][1].equals(d) && !A[i][2].equals(uni)){
          selected[i] = true;
          if(!uni.equals("")) break;
          uni = A[i][2];
        }
    }

    // Selection Step 2
    for(int k=0;k<6;k++)
      for(int i=0;i<n;i++){
        if(selected[i]) continue;
        int ctr = 0;
        for(int j=0;j<n;j++)
          if(selected[j] && A[i][2].equals(A[j][2]))
            ctr++;
        if(ctr == 2) continue;
        selected[i] = true;
        break;
      }

    for(int i=0;i<n;i++)
      if(selected[i])
        System.out.println(A[i][0]);
  }
}
