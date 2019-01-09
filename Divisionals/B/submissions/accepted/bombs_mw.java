
import java.util.*;


class FenwickTree2D {
  int N, M;
  int[][] A;
  FenwickTree2D(int n, int m) {
  	N = n;
  	M = m;
  	A = new int[N+1][M+1];

  }
  int query(int i, int j) {
  	++i; ++j;
    int sum = 0;
    int x = i;
    while (x > 0) {
      int y = j;
      while (y > 0) {
        sum += A[x][y];
        y -= (y & -y);
      }
      x -= (x & -x);
    }
    return sum;
  }
  
  void update(int i, int j, int v){
  	++i; ++j;
    int x = i;
    while (x <= N) {
      int y = j;
      while (y <= M) {
        A[x][y] += v;
        y += (y & -y);
      }
      x += (x & -x);
    }
  }
  void update(int i, int j, int i2, int j2) {
    update(i, j, 1);
    update(i2 + 1, j, -1);
    update(i, j2 + 1, -1);
    update(i2 + 1, j2 + 1, 1);
  }
}

public class bombs_mw {

	static class Coord {
		int r, c;
		Coord(int rr, int cc)
		{
			r = rr;
			c = cc;
		}
	}

	public static void main(String[] args)
	{

		Scanner sc = new Scanner(System.in);

		int R = sc.nextInt(), C = sc.nextInt(), K = sc.nextInt();

		FenwickTree2D ft = new FenwickTree2D(R, C);

		int str = 0, stc = 0;
		sc.nextLine();
		for (int r = 0; r < R; ++r) {
			String row = sc.nextLine();
			for (int c = 0; c < C; ++c) {
				if (row.charAt(c) == 'X')
					ft.update(r, c, r, c);
				if (row.charAt(c) == 'S') {
					str = r;
					stc = c;
				}
			}
		}

		Queue<Coord> Q = new ArrayDeque<Coord>();
		Queue<Coord> nextQ;
		Q.offer(new Coord(str, stc));
		boolean[][] D = new boolean[R][C];
		D[str][stc] = true;
		int[][] dirs = { { 0, 1 }, { 0, -1 }, { 1, 0 }, { -1, 0 }, { 1, 1 }, { 1, -1 }, { -1, 1 }, { -1, -1 } };
		for (int k = 0; k < K; ++k) {
			int r1 = sc.nextInt(), c1 = sc.nextInt(), r2 = sc.nextInt(), c2 = sc.nextInt();
			--r1;
			--r2;
			--c1;
			--c2;
			nextQ = new ArrayDeque<Coord>();
			while (!Q.isEmpty()) {
				Coord co = Q.poll();
				if (ft.query(co.r, co.c) > 0)
					continue;
				for (int i = 0; i < dirs.length; ++i) {
					int rr = co.r + dirs[i][0], cc = co.c + dirs[i][1];
					if (rr < 0 || rr >= R || cc < 0 || cc >= C)
						continue;
					if (D[rr][cc] || ft.query(rr, cc) > 0)
						continue;
					D[rr][cc] = true;
					nextQ.offer(new Coord(rr, cc));
				}
			}
			ft.update(r1, c1, r2, c2);
			Q = nextQ;
		}

		for (int r = 0; r < R; ++r) {
			for (int c = 0; c < C; ++c) {
				if (D[r][c] && ft.query(r, c) == 0) {
					System.out.println(Integer.toString(r + 1) + " " + Integer.toString(c + 1));
					return;
				}
			}
		}
		System.out.println(-1);
	}
}
