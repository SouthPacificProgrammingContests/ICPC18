import java.util.*;

public class HolidayDarcy {
  public static void main(String[] args) {
    new HolidayDarcy().run();
  }
  
  void run() {
    Scanner in = new Scanner(System.in);
    
    int n = in.nextInt();

    int A[] = new int[n];
    TreeMap<Integer, Integer> M = new TreeMap<Integer,Integer>();
    int ctr = 0;
    for(int i=0;i<n;i++){
      int x = in.nextInt();
      if(!M.containsKey(x)) { M.put(x,ctr); ctr++; }
      A[i] = M.get(x);
    }

    int[] used = new int[ctr];

    int r = 0;
    
    for(int num_used=0;num_used<ctr;r++){
      used[A[r]]++;
      if(used[A[r]] == 1)
	num_used++;
    }
    
    int ans = r;
    for(int l=0;l<n && r < n;l++){
      used[A[l]]--;
      if(used[A[l]] == 0){
	while(r < n && used[A[l]] == 0){
	  used[A[r]]++;
	  r++;
	}
	int size = r-l-1;
	if(used[A[l]] == 0) size++;
	ans = Math.max(ans, size);
      }
    }
    
    System.out.println(ans);
  }
}
