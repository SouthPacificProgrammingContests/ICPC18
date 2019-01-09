import java.util.*;
import java.io.*;

public class HazardDarcy {
  static StreamTokenizer st = new StreamTokenizer(new BufferedReader(new InputStreamReader(System.in)));
  static int readi() throws IOException {
    st.nextToken();
    return new Integer(st.sval).intValue();
  }
  public static void main(String[] args) throws Exception {
    new HazardDarcy().run();
  }

  boolean[] vis;
  ArrayList<Integer> adjV[];
  ArrayList<Integer> adjH[];
  ArrayList<Integer> adjL[];
  int n;
  long N;

  void run() throws Exception {
    // Scanner in = new Scanner(System.in);

    n = readi();
    int m = readi();
    N = (long)n;
    int s = readi() - 1, t = readi() - 1;

    vis = new boolean[n];
    adjV = new ArrayList[n];
    adjH = new ArrayList[n];
    adjL = new ArrayList[n];
    for(int i=0;i<n;i++){
    	adjV[i] = new ArrayList<>();
    	adjH[i] = new ArrayList<>();
    	adjL[i] = new ArrayList<>();	
    } 

    for(int i=0;i<m;i++){
      int u = readi() - 1, v = readi() - 1;
      int H = readi(), L = readi();
      adjV[u].add(v); adjH[u].add(H); adjL[u].add(L);
      adjV[v].add(u); adjH[v].add(H); adjL[v].add(L);
    }

    int lo = 1, hi = 1;
    while(!can(s, t, hi)) hi *= 2;
    while(hi - lo > 4){
      int mid = (lo + hi) / 2;
      if(can(s, t, mid)) hi = mid;
      else lo = mid;
    }
    while(!can(s, t, lo)) lo++;

    System.out.println(lo);
    System.out.println(dist(s,t,lo));
  }

  long dist(int src, int dest, int haz_lvl) throws Exception {
  	PriorityQueue<Long> pq = new PriorityQueue<>();
  	pq.offer((long)src);
  	long[] D = new long[n];
  	Arrays.fill(D, -1);
  	D[src] = 0;
  	while(!pq.isEmpty()){
  		long t = pq.poll();
  		long d = t / N;
  		int v = (int)(t % N);
  		if(D[v] != d) continue;
  		for(int i=0;i<adjV[v].size();i++)
  			if(adjH[v].get(i) <= haz_lvl)
  			    if(D[adjV[v].get(i)] == -1 || D[adjV[v].get(i)] > (d+adjL[v].get(i))){
  			        D[adjV[v].get(i)] = (d+adjL[v].get(i));
      				pq.offer((d+adjL[v].get(i)) * N + adjV[v].get(i));
  			    }
  	}
  	return D[dest];
  }

  boolean can(int src, int dest, int haz_lvl){
    Arrays.fill(vis, false);
    return reachable(src, dest, haz_lvl);
  }

  boolean reachable(int src, int dest, int haz_lvl){
  	if(vis[src]) return false;
    if(src == dest) return true;
    vis[src] = true;

    for(int i=0;i<adjV[src].size();i++){
    	int u = adjV[src].get(i), H = adjH[src].get(i);
    	if(H <= haz_lvl && reachable(u, dest, haz_lvl))
    		return true;
    }
    return false;
   }
}
