import java.util.*;
import java.math.*;


public class KrazyMax {

	static int N;
	static ArrayList<HashSet<Integer>> adj;

	static void dfs(int at, boolean[] vis, boolean any) {
		vis[at] = true;
		for (int i = 0; i < N; ++i) if (!vis[i]) {
			if (adj.get(at).contains(i) || (any && adj.get(i).contains(at))) {
				dfs(i, vis, any);
			}
		}
	}

	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);

		N = sc.nextInt();

		adj = new ArrayList<HashSet<Integer>>();

		for (int i = 0; i < N; ++i) adj.add(new HashSet<Integer>());

		int X = sc.nextInt(), Y = sc.nextInt();

		for (int x = 0; x < X; ++x) {
			int u = sc.nextInt(), v = sc.nextInt();
			--u; --v;
			adj.get(u).add(v);
			adj.get(v).add(u);
		}

		for (int y = 0; y < Y; ++y) {
			int u = sc.nextInt(), v = sc.nextInt();
			--u; --v;
			adj.get(u).add(v);
		}

		boolean[] vis1 = new boolean[N], vis2 = new boolean[N];
		dfs(0, vis1, false);
		dfs(0, vis2, true);

		for (int i = 0; i < N; ++i) {
			if (!vis2[i]) {
				System.out.println("Impossible");
			} else if (!vis1[i]) {
				System.out.println("Ticket");
			} else {
				System.out.println("No Ticket");
			}
		}


	}
}
