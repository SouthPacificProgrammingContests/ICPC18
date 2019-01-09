import java.util.*;


class Pt {
	long x, y;
	public Pt(long xx, long yy) {
		x = xx;
		y = yy;
	}
	public Pt subtract(Pt o) {
		return new Pt(x-o.x, y-o.y);
	}
}


class Seg {
	Pt s, e;
	Seg(Pt ss, Pt ee) {
		s = ss;
		e = ee;
	}
	int dir(Pt a, Pt b, Pt c) {
		Pt e = b.subtract(a), f = c.subtract(a);
		long d = e.x*f.y-f.x*e.y;
		if (d > 0) return 1;
		if (d < 0 || e.x*f.x < 0 || e.y*f.y < 0) return -1;
		if (e.x*e.x+e.y*e.y < f.x*f.x+f.y*f.y) return 1;
		return 0;
	}
	boolean inter(Seg o) {
		return dir(s,e,o.s)*dir(s,e,o.e) <= 0 && dir(o.s,o.e,s)*dir(o.s,o.e,e) <= 0; 
	}
}

class Pair implements Comparable<Pair> {
	int first, second;
	Pair(int f, int s) {
		first = f;
		second = s;
	}
	public int compareTo(Pair o) {
		if (first == o.first) return second-o.second;
		return first-o.first;
	}
}

class ExplosiveMax {
	int N;
	Pt[][] lines;
	int[] W, Ln, L, R;
	boolean[][] cross;
	int[][] adj;
	int[][][] dp;

	int f(int l1, int l2, int i) {
		if (dp[l1][l2][i] != -1) return dp[l1][l2][i];
		// System.out.println(l1+" "+l2+" "+i+" "+dp[l1][l2].length+" "+R[l2]);
		int ans = 0;
		if (i != L[l1] && i != R[l1] && i != L[l2] && i != R[l2]) {
			ans = Math.max(ans, f(l1, l2, i+1));
			int ln1 = Ln[i];
			if (R[ln1] != i && !cross[ln1][l1] && !cross[ln1][l2]) {
				for (int ln2 : adj[ln1]) if (L[ln2] > i) {
					int j = L[ln2];
					if (cross[ln2][l1] || cross[ln2][l2]) continue;
					int tot = W[ln1]+W[ln2]+f(ln1, ln2, i+1);
					if (R[ln2] > R[ln1])
						tot += f(ln1, ln2, j+1)+f(ln1, ln2, R[ln1]+1)+f(l1, l2, R[ln2]+1);
					else
						tot += f(ln1, ln2, j+1)+f(ln1, ln2, R[ln2]+1)+f(l1, l2, R[ln1]+1);
					ans = Math.max(ans, tot);
				}	
			}
		}
		return dp[l1][l2][i] = ans;
	}


	public void run() {
		Scanner sc = new Scanner(System.in);
		N = sc.nextInt();
		lines = new Pt[N][];
		W = new int[N];
		Pair[] xs = new Pair[2*N];
		int kek = 0;

		for (int i = 0; i < N; ++i) {
			W[i] = sc.nextInt();
			int cnt = sc.nextInt();
			lines[i] = new Pt[cnt];
			for (int j = 0; j < cnt; ++j) {
				lines[i][j] = new Pt(0,0);
				lines[i][j].x = sc.nextLong();
				lines[i][j].y = sc.nextLong();
			}
			xs[kek] = new Pair(0,0);
			xs[kek].first = (int)lines[i][0].x;
			xs[kek++].second = i;
			xs[kek] = new Pair(0,0);
			xs[kek].first = (int)lines[i][cnt-1].x;
			xs[kek++].second = i;
		}
		Arrays.sort(xs);
		Ln = new int[2*N];
		L = new int[N+1];
		R = new int[N+1];
		boolean[] done = new boolean[N+1];
		for (int i = 0; i < 2*N; ++i) {
			if (!done[xs[i].second]) {
				L[xs[i].second] = i;
				done[xs[i].second] = true;
			} else
				R[xs[i].second] = i;
			Ln[i] = xs[i].second;
		}
		L[N] = -1;
		R[N] = 2*N;
		// System.out.println(2*N);
		// for (int i = 0; i < N; ++i) System.out.println(R[i]);
		cross = new boolean[N+1][N+1];
		for (int i = 0; i < N; ++i) {
			for (int j = 0; j < N; ++j) {
				for (int k = 0; k < lines[i].length-1; ++k)
					for (int l = 0; l < lines[j].length-1; ++l) {
						Seg  s = new Seg(lines[i][k],lines[i][k+1]), s2 = new Seg(lines[j][l],lines[j][l+1]);
						if (s.inter(s2)) {
							cross[i][j] = true;
						}
					}
			}
		}

		adj = new int[N+1][];
		for (int i = 0; i < N; ++i) {
			int deg = 0;
			for (int j = 0; j < N; ++j) if (i!=j && cross[i][j]) ++deg;
			adj[i] = new int[deg];
			int k = 0;
			for (int j = 0; j < N; ++j) if (i != j && cross[i][j]) {
				adj[i][k++] = j;
			}
		}
		dp = new int[N+5][N+5][2*N+5];
		for (int i = 0; i < N+5; ++i) {
			for (int j = 0; j < N+5; ++j) {
				for (int k = 0; k < 2*N+5; ++k) {
					dp[i][j][k] = -1;
				}
			}
		}
		System.out.println(f(N,N,0));
		
	}
	public static void main(String[] args) {
		ExplosiveMax sol = new ExplosiveMax();
		sol.run();
		
	}
}
