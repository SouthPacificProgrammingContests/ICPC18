import java.util.*;


class InterestingMax {


	public void run() {
		Scanner sc = new Scanner(System.in);
		int n = sc.nextInt(), m = sc.nextInt();
		int last = 0, ans = 0;
		for (int i = 0; i < m; ++i) {
			int tmp = sc.nextInt();
			if (tmp < last) ++ans;
			last = tmp;
		}
		System.out.println(ans);

	}

	public static void main(String[] args) {
		InterestingMax sol = new InterestingMax();
		sol.run();
		
	}
}
