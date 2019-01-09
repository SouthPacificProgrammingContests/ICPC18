import java.util.*;


class GoodMax {

	int N, Q;
	int[] par, depth;
	char[] type;

	public int dep(int at) {
		if (at == 0) return 0;
		if (depth[at] != 0) return depth[at];
		return depth[at] = dep(par[at])+1;
	}

	public void run() {
		Scanner sc = new Scanner(System.in);
		N = sc.nextInt();
		Q = sc.nextInt();
		par = new int[N+2];
		type = new char[N+2];
		for (int i = 2; i <= N+1; ++i) {
			type[i] = sc.next().charAt(0);
			par[i] = sc.nextInt();
		}

		int p2 = 1, mp = 0;
		for (; p2 < N+2; p2 *= 2, ++mp);

		int[][] jpar = new int[mp+1][N+2];
		jpar[0] = par;
		for (int p = 1; p <= mp; ++p)
			for (int i = 1; i <= N+1; ++i) 
				jpar[p][i] = jpar[p-1][jpar[p-1][i]];
		
		depth = new int[N+2];
		for (int i = 1; i < N+2; ++i) dep(i);

		int cnt = 0;
		for (int q = 0; q < Q; ++q) {
			int a = sc.nextInt(), b = sc.nextInt();
			if (depth[a] > depth[b]) {
				int tmp = a;
				a = b;
				b = tmp;
			}
			int oa = a, ob = b;
			int d = depth[b]-depth[a];
			for (int p = mp; d != 0 && p >= 0; --p) if (1<<p <= d) {
				d -= 1<<p;
				b = jpar[p][b];
			}
			for (int p = mp; p >= 0; --p) if (jpar[p][a] != jpar[p][b]) {
				a = jpar[p][a];
				b = jpar[p][b];
			}
			if (a != b) {
				if (type[a] == 'L' && type[b] == 'L') ++cnt;
				else if (type[a] == 'P' && type[b] == 'L' && a > b) ++cnt;
				else if (type[a] == 'L' && type[b] == 'P' && a < b) ++cnt;
			} else {
				a = oa; b = ob;
				d = depth[b]-depth[a];
				for (int p = mp; d != 0 && p >= 0; --p) if (1<<p < d) {
					d -= 1<<p;
					b = jpar[p][b];
				}
				// System.out.println(b);
				if (type[b] == 'L') ++cnt;
			}
			// System.out.println(a+" "+b+" "+cnt);

		}
		System.out.println(cnt);
	}
	public static void main(String[] args) {
		GoodMax sol = new GoodMax();
		sol.run();
		
	}
}



// #include <bits/stdc++.h>

// using namespace std;

// int N, Q;
// vector<int> par, depth;
// vector<vector<int>> adj;
// vector<char> type;

// int dfs(int at, int d, int p) {
// 	depth[at] = d;
// 	for (int c : adj[at]) if (c != p) dfs(c, d+1, at);
// }

// int main() {
// 	cin >> N >> Q;
// 	par.resize(N+2);
// 	type.resize(N+2);
// 	adj.resize(N+2);
// 	adj[0].push_back(1);
// 	adj[1].push_back(0);
// 	for (int i = 2; i <= N+1; ++i) {
// 		cin >> type[i] >> par[i];
// 		adj[i].push_back(par[i]);
// 		adj[par[i]].push_back(i);
// 	}

// 	int p2 = 1, mp = 0;
// 	for (; p2 < N+2; p2 *= 2, ++mp);

// 	vector<vector<int>> jpar(mp+1, vector<int>(N+2));
// 	jpar[0] = par;
// 	for (int p = 1; p <= mp; ++p)
// 		for (int i = 1; i <= N+1; ++i) 
// 			jpar[p][i] = jpar[p-1][jpar[p-1][i]];
// 	depth.resize(N+2);
// 	dfs(0, 0, 0);

// 	int cnt = 0;
// 	for (int q = 0; q < Q; ++q) {
// 		int a, b;
// 		cin >> a >> b;
// 		if (depth[a] > depth[b]) swap(a,b);
// 		int oa = a, ob = b;
// 		int d = depth[b]-depth[a];
// 		for (int p = mp; d && p >= 0; --p) if (1<<p <= d) {
// 			d -= 1<<p;
// 			b = jpar[p][b];
// 		}
// 		for (int p = mp; p >= 0; --p) if (jpar[p][a] != jpar[p][b]) {
// 			a = jpar[p][a];
// 			b = jpar[p][b];
// 		}
// 		if (a != b) {
// 			if (type[a] == 'L' && type[b] == 'L') ++cnt;
// 			else if (type[a] == 'P' && type[b] == 'L' && a > b) ++cnt;
// 			else if (type[a] == 'L' && type[b] == 'P' && a < b) ++cnt;
// 		} else {
// 			a = oa; b = ob;
// 			d = depth[b]-depth[a];
// 			for (int p = mp; d && p >= 0; --p) if (1<<p < d) {
// 				d -= 1<<p;
// 				b = jpar[p][b];
// 			}
// 			if (type[b] == 'L') ++cnt;
// 		}

// 	}
// 	cout << cnt << endl;
// }