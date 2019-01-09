import java.util.*;
import java.io.*;

public class CollectDarcy {
  static StreamTokenizer st = new StreamTokenizer(new BufferedReader(new InputStreamReader(System.in)));
  static int readi() throws IOException {
    st.nextToken();
    return new Integer(st.sval).intValue();
  }

  public static void main(String[] args) throws Exception {
    new CollectDarcy().run();
  }

  void run()  throws Exception {
	st.ordinaryChars('0', '9');
    		st.wordChars('0', '9');
    //Scanner in = new Scanner(System.in);

    int n = readi();
    int k = readi();
    long MAX_T = 1000000001;

    long[] stars = new long[n];
    for(int i=0;i<n;i++){
      long t = (long)readi();
      long d = (long)readi();
      stars[i] = t + MAX_T * d;
    }

    Arrays.sort(stars);

    PriorityQueue<Long> pq = new PriorityQueue<>();

    long ans = 0;
    int idx = 0;
    for(int i=0;i<k;i++){
      while(idx < n && stars[idx] / MAX_T <= i){
        pq.add(stars[idx] % MAX_T);
        idx++;
      }
      if(pq.isEmpty()){
        System.out.println("IMPOSSIBLE");
        return;
      }
      ans += pq.remove();
    }

    System.out.println(ans);
  }
}
