import java.util.*;

public class GoodDarcy {
  public static void main(String[] args) {
    new GoodDarcy().run();
  }


  void run() {
    Scanner in = new Scanner(System.in);

    int n = in.nextInt() + 1, Q = in.nextInt();

    int logg = 1; while((1 << logg) <= 2*n) logg++;

    String[] upgrades = new String[n];
    int[] depth = new int[n];
    int[][] par = new int[logg][n];

    upgrades[0] = "L";

    for(int i=1;i<n;i++){
      upgrades[i] = in.next();
      par[0][i] = in.nextInt() - 1;
      depth[i] = depth[par[0][i]] + 1;
    }

    for(int i=1;i<logg;i++)
      for(int v=0;v<n;v++)
        par[i][v] = par[i-1][ par[i-1][v] ];

    int ans = 0;
    while(Q-- > 0){
      int u = in.nextInt() - 1, v = in.nextInt() - 1;
      if(depth[u] > depth[v]) { int t = u; u = v; v = t; }
      for(int i=logg-1;i>=0;i--)
			if(depth[v] - (1 << i) > depth[u])
				v = par[i][v];

		int care_about = v;

		if(par[0][v] != u){
			if(depth[v] != depth[u]) v = par[0][v];
			for(int i=logg-1;i>=0;i--)
				if(par[i][u] != par[i][v]){
					u = par[i][u]; v = par[i][v];
				}
			care_about = Math.min(u, v);
		}
      if(upgrades[care_about].equals("L"))
        ans++;
    }
    System.out.println(ans);
  }
}
