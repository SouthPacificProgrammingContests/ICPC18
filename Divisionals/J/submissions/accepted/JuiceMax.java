import java.util.*;
import java.math.*;


public class JuiceMax {

	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);

		int amt = sc.nextInt(), NC = sc.nextInt();

		int[] C = new int[NC];

		int lcm = 2520;

		for (int i = 0; i < NC; ++i) {
			int n = sc.nextInt(), d = sc.nextInt();
			C[i] = n*(lcm/d);

		}
		int[] DP = new int[lcm*amt+1];
		DP[0] = 0;
		for (int num = 1; num <= lcm*amt; ++num) {
			DP[num] = (int)1e9;
			for (int i = 0; i < NC; ++i) if (num-C[i] >= 0) {
				DP[num] = Math.min(DP[num], DP[num-C[i]]+1);
			}
		}
		System.out.println(DP[lcm*amt]==(int)1e9?-1:DP[lcm*amt]);
	}
}
