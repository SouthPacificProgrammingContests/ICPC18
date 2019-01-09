
import java.util.*;


class JudgingMax {


	public void run() {
		Scanner sc = new Scanner(System.in);
		int n;
		n = sc.nextInt();
		String[][] S = new String[n][3];
		for (int i = 0; i < n; ++i) {
			S[i][0] = sc.next();
			S[i][1] = sc.next();
			S[i][2] = sc.next();
		}
		boolean[] sel = new boolean[n];
		TreeMap<String, Integer> divcnt = new TreeMap<String, Integer>();
		TreeMap<String, Integer> unicnt = new TreeMap<String, Integer>();
		for (int i = 0; i < n; ++i) {
			divcnt.put(S[i][1], 0);
			unicnt.put(S[i][2], 0);
		}
		int c = 0;
		for (int i = 0; i < n && c < 6; ++i) {
			if (divcnt.get(S[i][1]) < 2 && unicnt.get(S[i][2]) == 0) {
				sel[i] = true;
				int v = 0;
				if (divcnt.containsKey(S[i][1])) v = divcnt.get(S[i][1]);
				divcnt.put(S[i][1], v+1);
				v = 0;
				if (unicnt.containsKey(S[i][2])) v = unicnt.get(S[i][2]);
				unicnt.put(S[i][2], v+1);
				++c;
			}
		}
		for (int i = 0; i < n && c < 12; ++i) {
			if (sel[i]) continue;
			if (unicnt.get(S[i][2]) == 2) continue;
			sel[i] = true;
			int v = 0;
			if (unicnt.containsKey(S[i][2])) v = unicnt.get(S[i][2]);
			unicnt.put(S[i][2], v+1);
			++c;
		}
		for (int i = 0; i < n; ++i) {
			if (sel[i]) {
				System.out.println(S[i][0]);
			}
		}

	}

	public static void main(String[] args) {
		JudgingMax sol = new JudgingMax();
		sol.run();
		
	}
}
