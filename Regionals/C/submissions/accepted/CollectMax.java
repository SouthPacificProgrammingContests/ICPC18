import java.util.*;
import java.io.*;

class CollectMax {
  static StreamTokenizer st = new StreamTokenizer(new BufferedReader(new InputStreamReader(System.in)));
  static int readi() throws IOException {
    st.nextToken();
    return new Integer(st.sval).intValue();
  }
	public static void main(String[] args) throws Exception {
		st.ordinaryChars('0', '9');
    		st.wordChars('0', '9');
		//Scanner sc = new Scanner(System.in);
		int N = readi(), K = readi();
		PriorityQueue pq = new PriorityQueue();
		ArrayList<ArrayList<Integer>> stars = new ArrayList<ArrayList<Integer>>(N+1);
		for (int i = 0; i < N+1; i++) stars.add(i, new ArrayList<Integer>());

		for (int i = 0; i < N; ++i) {
			int t, s;
			t = readi();
			s = readi();
			if (s <= N) stars.get(s).add(t);
		}

		long t = 0, cnt = 0;
		for (long tt : stars.get(0)) pq.add(tt);
		while (pq.size() > 0 && cnt < K) {
			t += (Long)pq.poll();
			++cnt;
			for (long tt : stars.get((int)cnt)) pq.add(tt);
		}
		if (cnt != K) System.out.println("IMPOSSIBLE");
		else System.out.println(t);
	}
}
