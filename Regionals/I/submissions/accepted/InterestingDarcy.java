import java.util.*;

public class InterestingDarcy {
  public static void main(String[] args) {
    new InterestingDarcy().run();
  }

  long[] factorial;
  int[] cnt;

  void run() {
    Scanner in = new Scanner(System.in);

    int n = in.nextInt(), m = in.nextInt();

    factorial = new long[n+2];
    factorial[0] = 1;
    for(int i=1;i<n+2;i++)
      factorial[i] = factorial[i-1] * i;

    cnt = new int[n];
    System.out.println(f(0,n,n,m));
  }

  long f(int idx,int available,int n,int m){
    if(idx == n){
      if(available != 0)
        return 0;

      int[] arr = new int[n];
      int my_idx = 0;
      for(int i=0;i<n;i++)
        for(int j=0;j<cnt[i];j++)
          arr[my_idx++] = i;

      // Do they have the same modular distribution?
      int sz = Math.min(n+1, m);
      int[] mods_cnt = new int[sz];
      int[] mods_arr = new int[sz];
      for(int i=0;i<n;i++){
        mods_cnt[ cnt[i] % m ]++;
        mods_arr[ arr[i] % m ]++;
      }

      for(int i=0;i<sz;i++)
        if(mods_arr[i] != mods_cnt[i])
          return 0;
    
      long ans = 1;
      for(int i=0;i<sz;i++)
        ans *= factorial[mods_cnt[i]];

      for(int i=0;i<n;i++)
        ans /= factorial[cnt[i]];

      return ans;
    }

    long ans = 0;
    for(int i=0;i<=available;i++){
      cnt[idx] = i;
      ans += f(idx+1,available-i,n,m);
    }
    return ans;
  }
}
