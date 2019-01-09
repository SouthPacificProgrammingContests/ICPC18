import java.util.*;

class BadMax {
	public static int[] zalgorithm(String s) {
		int n = s.length();
		char[] S = s.toCharArray();
		int[] z = new int[n];
		int L = 0, R = 0;
		for (int i = 0; i < n; ++i) {
			if (i > R) {
				L = R = i;
				while (R < n && S[R-L] == S[R]) R++;
				z[i] = R-L; R--;
			} else {
				int k = i-L;
				if (z[k] < R-i+1) z[i] = z[k];
				else {
					L = i;
					while (R < n && S[R-L] == S[R]) R++;
					z[i] = R-L; R--;
				}
			}
		}
		z[0] = n;
		return z;
	}

	public static int ans(String a, String b) {
		int[] z = zalgorithm(a+"$"+b);
		int mx = 0;
		for (int i = a.length()+1; i < a.length()+b.length()+1; ++i) {
			mx = Math.max(mx, z[i]);
		}
		return mx;
	}

	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		String S = sc.next();

		int N = S.length();

		StringBuilder odd = new StringBuilder(), eve = new StringBuilder();

		for (int i = 0; i < N; ++i) {
			if (i%2 == 1) odd.append(S.charAt(i));
			else eve.append(S.charAt(i));
		}

		System.out.println(Math.min(N, Math.max(ans(odd.toString(), S)*2+1, ans(eve.toString(),S)*2)));
	}
}
