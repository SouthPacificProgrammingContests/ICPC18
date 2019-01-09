import java.util.*;

class DroppingMax {
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		int N = sc.nextInt();
		int[] A = new int[N];
		for (int i = 0; i < N; ++i) {
			A[i] = sc.nextInt();
		}
		int l = A[0], r = 0, last = A[0];
		boolean g = true;
		for (int i = 1; i < N; ++i) {
			if (A[i] < last) {
				l -= (last-A[i]);
				if (l < 0) {
					g = false;
					break;
				}
			} else if (A[i] > last) {
				r += A[i]-last;
			}
			last = A[i];
		}
		if (g) {
			System.out.println("YES");
		} else {
			System.out.println("NO");
		}
	}
}
