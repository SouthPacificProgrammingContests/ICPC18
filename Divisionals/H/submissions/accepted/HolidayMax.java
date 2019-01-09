import java.util.*;
import java.math.*;


public class HolidayMax {

	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);

		int N = sc.nextInt();
		int[] A = new int[N];

		TreeSet<Integer> set = new TreeSet<Integer>();
		for (int i = 0; i < N; ++i) {
			A[i] = sc.nextInt();
			set.add(A[i]);
		}

		int distinct = set.size();

		int r = 0, ans = 0;
		TreeMap<Integer, Integer> cnts = new TreeMap<Integer,Integer>();
		for (int l = 0; l < N; ++l) {
			while (cnts.size() < distinct && r < N) {
				if (!cnts.containsKey(A[r])) cnts.put(A[r], 0);
				cnts.put(A[r], cnts.get(A[r])+1);
				++r;
			}
			if (cnts.size() < distinct) {
				ans = Math.max(ans, N-l+1);
				break;
			}
			ans = Math.max(ans, r-l);
			if (!cnts.containsKey(A[l])) cnts.put(A[l], 0);
			cnts.put(A[l], cnts.get(A[l])-1);
			if (cnts.get(A[l]) == 0) cnts.remove(A[l]);
		}
		System.out.println(ans);
	}
}
