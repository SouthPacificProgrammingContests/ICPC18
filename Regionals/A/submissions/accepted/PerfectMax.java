import java.util.*;

class PerfectMax {
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		long n = sc.nextInt(), L = sc.nextInt(), sum = 0;
		String str;
		for (int i = 0; i < n; ++i) {
			str = sc.next();
			sum += str.length();
		}

		for (int i = 1; i <= L; ++i) {
			if (sum + (n-1)*i == L) {
				System.out.println("Yes");
				return;
			}
		}

		System.out.println("No");
	}
}
