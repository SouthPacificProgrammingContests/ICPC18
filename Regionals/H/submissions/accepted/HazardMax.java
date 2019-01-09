import java.util.*;
import java.io.*;


class HazardMax {

	static StreamTokenizer st = new StreamTokenizer(new BufferedReader(new InputStreamReader(System.in)));
  static int readi() throws IOException {
    st.nextToken();
    return new Integer(st.sval).intValue();
  }

	class Edge {
		int h, l, n;
		public Edge(int ww, int uu, int vv) {
			h = ww;
			l = uu;
			n = vv;
		}
	}

	class Pair implements Comparable<Pair> {
		long first, second;
		Pair(long f, long s) {
			first = f;
			second = s;
		}
		public int compareTo(Pair o) {
			if (first == o.first) return (int)second-(int)o.second;
			return (int)first-(int)o.first;
		}
	}

	int N, M, S, T;
	ArrayList<ArrayList<Edge>> adj;

	int dijk1(int s, int en) {
		int[] D = new int[N];
		for (int i = 0; i < N; ++i) D[i] = 1000000005;
		D[s] = 0;
		PriorityQueue<Pair> Q = new PriorityQueue<Pair>();

		Q.offer(new Pair(0, s));
		while (Q.size() > 0) {
			Pair p = Q.poll();
			int hh = (int)p.first, at = (int) p.second;
			if (at == en)
				return D[(int)at];
			if (D[(int)at] < hh) continue;
			for (Edge e : adj.get(at)) {
				int h = e.h, l = e.l, n = e.n;
				if (D[n] <= Math.max(h,D[at])) continue;
				D[n] = Math.max(h,D[at]);
				Q.offer(new Pair(Math.max(h,D[at]), n));
			}
		}
		return -1;
	}

	long dijk2(int s, int en, int t) {
		long[] D = new long[N];
		for (int i = 0; i < N; ++i) D[i] = 1000000000L*1000000000L+5L;
		D[s] = 0;
		PriorityQueue<Pair> Q = new PriorityQueue<Pair>();

		Q.offer(new Pair(0, s));
		while (Q.size() > 0) {
			Pair p = Q.poll();
			long ll = p.first, at = p.second;
			if (at == en)
				return D[(int)at];
			if (D[(int)at] < ll) continue;
			for (Edge e : adj.get((int)at)) {
				int h = e.h, l = e.l, n = e.n;
				if (h>t || D[(int)n] <= D[(int)at]+l) continue;
				D[(int)n] = D[(int)at]+l;
				Q.offer(new Pair(D[(int)at]+l, n));
			}
		}
		return -1;
	}

	public void run() throws Exception {
		// Scanner sc = new Scanner(System.in);
		N = readi();
		M = readi();
		S = readi();
		T = readi();
		--S;--T;
		adj = new ArrayList<ArrayList<Edge>>(N);
		for (int i = 0; i < N; ++i) {
			adj.add(i, new ArrayList<Edge>());
		}
		for (int i = 0; i < M; ++i) {
			int a=readi(),b=readi(),h=readi(),l=readi();
			--a;--b;
			adj.get(a).add(new Edge(h,l,b));
			adj.get(b).add(new Edge(h,l,a));
		}
		int t = dijk1(S,T);
		System.out.println(t);
		System.out.println(dijk2(S,T,t));
	}

	public static void main(String[] args) throws Exception {
		HazardMax sol = new HazardMax();
		sol.run();
		
	}
}
