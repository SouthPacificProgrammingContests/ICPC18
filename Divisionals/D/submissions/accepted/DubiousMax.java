import java.util.*;
import java.math.*;


public class DubiousMax {

	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);

		long N = sc.nextLong();
		long[] A = new long[(int)N];
		for (int i = 0; i < N; ++i) {
			A[i] = sc.nextLong();
		}
		long sum = 0;
		for (int i = 0; i < N; ++i) {
			sum += A[i]*(i+1)*(N-i);
		}
		long g = (new BigInteger(""+sum)).gcd(new BigInteger(""+(N*(N+1)/2))).longValue();
		System.out.print(sum/g);
		System.out.print("/");
		System.out.println((N*(N+1)/2)/g);
	}
}
