import java.util.*;


public class ausvsamer_mw {
	static int N;
	static int[][] dates;
	static int[] days = {0,31,28,31,30,31,30,31,31,30,31,30,31};

	static boolean valid_month(int m) {
		return m >= 1 && m <= 12;
	}

	static boolean valid_day(int d, int m, int y) {
		if (y%4 == 0 && m == 2) {
			return d >= 1 && d <= 29;
		}
		return d >= 1 && d <= days[m];
	}

	static int[] ans_perm;


	static int check(int[] perm) {
		for (int i = 0; i < N; ++i) {
			int d = dates[i][perm[0]], m = dates[i][perm[1]], y = dates[i][perm[2]];
			if (!valid_month(m)) {
				return 0;
			}
			if (!valid_day(d,m,y)) {
				return 0;
			}
		}
		ans_perm = perm;
		return 1;
	}

	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		N = sc.nextInt();
		dates = new int[N][3];
		for (int i = 0; i < N; ++i) {
			String[] parts = sc.next().split("/");
			dates[i][0] = Integer.parseInt(parts[0]);
			dates[i][1] = Integer.parseInt(parts[1]);
			dates[i][2] = Integer.parseInt(parts[2]);
		}

		int num_ans = check(new int[] {0,1,2}) + check(new int[] {0,2,1}) 
					+ check(new int[] {1,0,2}) + check(new int[] {1,2,0})
					+ check(new int[] {2,1,0}) + check(new int[] {2,0,1});

		if (num_ans == 0) {
			System.out.println("IMPOSSIBLE");
		} else if (num_ans > 1) {
			System.out.println("UNSURE");
		} else {
			String[] parts = {"DD","MM","YY"};
			int[] iperm = new int[3];
			for (int i = 0; i < 3; ++i) iperm[ans_perm[i]] = i;
			System.out.println(parts[iperm[0]] + "/" + parts[iperm[1]] + "/" + parts[iperm[2]]);
		}

	}
}
