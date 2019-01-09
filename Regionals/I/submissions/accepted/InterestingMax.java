import java.util.*;


class InterestingMax {

	int n, m;
	int[] C, Amf, Cmf;
	long[] fact;

	long f(int ii, int rem) {
		long ans = 0;
		if (ii == n) {
			if (rem != 0) return 0;
			ans = 1;
			Amf = new int[n+1];
			Cmf = new int[n+1];
			for (int i = 0; i < n; ++i) {
				Cmf[C[i]%m]++;
				Amf[i%m] += C[i];
			}
			if (!Arrays.equals(Cmf, Amf)) return 0;
			for (int i = 0; i <= n; ++i) ans *= fact[Cmf[i]];
			for (int i = 0; i < n; ++i) ans /= fact[C[i]];
			return ans;
		}
		for (int v = 0; v <= rem; ++v) {
			C[ii] = v;
			ans += f(ii+1, rem-v);
		}
		return ans;
	}

	public void run() {
		Scanner sc = new Scanner(System.in);
		n = sc.nextInt();
		m = sc.nextInt();
		fact = new long[n+1];
		fact[0] = 1;
		for (int i = 1; i <= n; ++i) fact[i] = fact[i-1]*i;
		C = new int[n];
		System.out.println(f(0,n));

	}

	public static void main(String[] args) {
		InterestingMax sol = new InterestingMax();
		sol.run();
		
	}
}
