import java.util.*;


class FarMax {

	public long[][] matmul(long[][] A, long[][] B) {
		if (A[0].length != B.length) return null;
		long[][] result = new long[A.length][B[0].length];
		for (int i = 0; i < A.length; ++i) {
			for (int j = 0; j < B[0].length; ++j) {
				result[i][j] = 1000000001;
			}
		}
		for (int r = 0; r < result.length; ++r) {
			for (int c = 0; c < result[0].length; ++c) {
				for (int i = 0; i < A[0].length; ++i) {
					result[r][c] = Math.min(result[r][c], A[r][i] + B[i][c]);
				}
			}
		}
		return result;
	}

	public void run() {
		Scanner sc = new Scanner(System.in);
		long n = sc.nextLong(), m = sc.nextLong();
		long[][] mat = new long[(int)n][(int)n];

		for (int i = 0; i < (int)n; ++i) {
			for (int j = 0; j < n; ++j) {
				mat[i][j] = sc.nextLong();
			}
		}

		long mn = 1000000100;
		for (int i = 0; i < n; ++i) mn = Math.min(mn, mat[0][i]);
		if (mn > m) {
			System.out.println(0);
			return;
		}

		ArrayList<long[][]> p2mats = new ArrayList<long[][]>();
		p2mats.add(null);
		p2mats.add(mat);
		long[][] curr = matmul(mat,mat);
		for (long p = 2; p <= m; p *= 2) {
			p2mats.add(curr);
			curr = matmul(curr, curr);
		}

		curr = mat;
		long ans = 1;
		for (long p = p2mats.size()-1; p > 0; --p) {
			long[][] ma = matmul(curr, p2mats.get((int)p));
			mn = 1000000100;
			for (int i = 0; i < n; ++i) mn = Math.min(mn, ma[0][i]);
			if (mn <= m) {
				curr = ma;
				ans += ((long)1)<<(p-1);
			}
		}
		System.out.println(ans);
	}
	public static void main(String[] args) {
		FarMax sol = new FarMax();
		sol.run();
		
	}
}
