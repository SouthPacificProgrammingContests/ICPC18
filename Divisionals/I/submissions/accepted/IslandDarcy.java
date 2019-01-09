import java.util.*;

public class IslandDarcy {
  public static void main(String[] args) {
    new IslandDarcy().run();
  }

  int[] uf;

  int find(int x){
    if(uf[x] == x) return x;
    uf[x] = find(uf[x]);
    return uf[x];
  }

  void merge(int x, int y){
    x = find(x); y = find(y);
    uf[x] = y;
  }

  boolean connected(int x, int y){
    x = find(x); y = find(y);
    return x == y;
  }
  
  void run() {
    Scanner in = new Scanner(System.in);
    
    int n = in.nextInt();
    int F = in.nextInt();
    int Q = in.nextInt();

    int[][] Fs = new int[F+Q][4];
    for(int i=0;i<F;i++){
      Fs[i][0] = in.nextInt() - 1;
      Fs[i][1] = in.nextInt() - 1;
      Fs[i][2] = 0; // Add friendship
      Fs[i][3] = i;
    }
    for(int i=0;i<Q;i++){
      Fs[i+F][2] = "AES".indexOf(in.next());
      Fs[i+F][0] = in.nextInt() - 1;
      Fs[i+F][1] = in.nextInt() - 1;
      Fs[i+F][3] = i+F;
    }

    Arrays.sort(Fs, new Comparator<int[]>() {
	public int compare(int[] a, int[] b){
	  if(a[2] == b[2] && a[2] == 2) return 0;
	  if(a[2] == 2) return 1;
	  if(b[2] == 2) return -1;
	  
	  for(int i=0;i<4;i++)
	    if(a[i] != b[i])
	      return a[i] - b[i];
	  return 0;
	}
      });

    uf = new int[n];
    for(int i=0;i<n;i++)
      uf[i] = i;
    
    for(int i=0;i<F+Q;i++){
      // Should I add this guy?
      if(Fs[i][2] != 0) continue;
      if(i+1 < F+Q &&
	 (Fs[i+1][0] == Fs[i][0] && Fs[i+1][1] == Fs[i][1] && Fs[i+1][2] == 1))
	continue;
      merge(Fs[i][0], Fs[i][1]);
    }

    Arrays.sort(Fs, new Comparator<int[]>() {
	public int compare(int[] a, int[] b){
	  return b[3] - a[3];
	}
      });

    boolean[] ans = new boolean[Q];
    int idx = 0;
    for(int i=0;i<Q;i++){
      if(Fs[i][2] == 1) merge(Fs[i][0], Fs[i][1]);
      else {
	ans[idx] = connected(Fs[i][0], Fs[i][1]);
	idx++;
      }
    }

    for(int i=idx-1;i>=0;i--)
      System.out.println(ans[i] ? "YES" : "NO");
  }
}
