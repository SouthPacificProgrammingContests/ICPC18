import java.util.*;


public class cryptic_mw {

	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		String clue = sc.nextLine();
		String[] words = clue.split(" ");
		int S = sc.nextInt();
		for (int s = 0; s < S; ++s) {
			String sol = sc.next();
			char[] sortedsol = sol.toCharArray();
			Arrays.sort(sortedsol);

			boolean g = false;
			for (int i = 0; i < words.length; ++i) {
				String subwords = "";
				for (int j = i; j < words.length; ++j) {
					subwords += words[j];
					char[] sorted = subwords.toCharArray();
					Arrays.sort(sorted);
					// System.out.println(subwords);
					if (subwords.equals(sol)) continue;
					if (sorted.length != sortedsol.length) continue;
					boolean eq = true;
					for (int k = 0; k < sorted.length; ++k) {
						if (sorted[k] != sortedsol[k]) {
							eq = false;
						}
					}
					if (eq) {
						g = true;
					}
				}
			}
			if (g) {
				System.out.println(sol);
				return;
			}

		}

	}
}
