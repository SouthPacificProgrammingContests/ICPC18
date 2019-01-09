import java.util.*;
import java.math.*;

class OnionFind {
	int[] par, rank;
	public OnionFind(int n)
	{
		par = new int[n];
		rank = new int[n];
		for (int i = 0; i < n; ++i) {
			par[i] = i;
			rank[i] = 1;
		}
	}
	public int find(int a)
	{
		if (par[a] == a)
			return a;
		par[a] = find(par[a]);
		return par[a];
	}
	public void onion(int a, int b)
	{
		int ra = find(a), rb = find(b);
		if (ra == rb)
			return;
		if (rank[ra] > rank[rb]) {
			int tmp = ra;
			ra = rb;
			rb = tmp;
		}
		par[ra] = rb;
		if (rank[ra] == rank[rb])
			++rank[rb];
	}
}

public class IslandMax {

	public static class pair implements Comparable<pair> {
		public int first;
		public int second;
		public pair(int first, int second)
		{
			this.first = first;
			this.second = second;
		}
		public int compareTo(pair o) {
			if (first == o.first) {
				return second - o.second;
			}
			return first - o.first;
		}
	}

	public static void main(String[] args)
	{
		Scanner sc = new Scanner(System.in);

		int N = sc.nextInt(), F = sc.nextInt(), Q = sc.nextInt();
		TreeSet<pair> E = new TreeSet<pair>();
		for (int i = 0; i < F; ++i) {
			int u,v;
			u = sc.nextInt()-1;
			v = sc.nextInt()-1;
			E.add(new pair(u, v));
		}
		int[][] queries = new int[Q][3];
		for (int i = 0; i < Q; ++i) {
			String t = sc.next();
			int a = sc.nextInt(), b = sc.nextInt();
			--a; --b;
			if (t.equals("E")) {
				E.remove(new pair(a, b));
				queries[i][0] = 1;
			} else {
				queries[i][0] = 2;
			}
			queries[i][1] = a;
			queries[i][2] = b;
		}
		OnionFind of = new OnionFind(N);
		for (pair p : E) of.onion(p.first, p.second);
		boolean[] ans = new boolean[Q];
		boolean[] isans = new boolean[Q];
		for (int i = Q-1; i >= 0; --i) {
			if (queries[i][0] == 1) of.onion(queries[i][1], queries[i][2]);
			else {
				isans[i] = true;
				ans[i] = of.find(queries[i][1]) == of.find(queries[i][2]);
			}
		}
		for (int i = 0; i < Q; ++i) {
			if (isans[i]) {
				System.out.println(ans[i]?"YES":"NO");
			}
		}
	}
}
