// The slowest solution I can think of...

import java.util.*;

public class CrypticDarcyACSlow {
  public static void main(String[] args) {
    new CrypticDarcyACSlow().run();
  }

  void run() {
    Scanner in = new Scanner(System.in);
    String orig_clue = in.nextLine();

    String clue = "";
    boolean[] start_of_word = new boolean[2*orig_clue.length()+1];
    start_of_word[0] = true;

    for(int i=0,j=0;i<orig_clue.length();i++)
      if(orig_clue.charAt(i) == ' '){
	start_of_word[j] = true;
      } else {
	clue += orig_clue.charAt(i);
	j++;
      }
    start_of_word[clue.length()] = true;

    int W = in.nextInt();

    for(int i=0;i<W;i++){
      String soln = in.next();
      boolean should_print = false;
      for(int j1=0;j1<clue.length();j1++)
	for(int j2=j1+1;j2<=clue.length();j2++){
	  String this_clue = clue.substring(j1,j2);
	  String this_soln = soln;
	  boolean good = true;

	  if(this_clue.equals(this_soln)) good = false;
	  if(!start_of_word[j1]) good = false;
	  if(!start_of_word[j2]) good = false;
	  if(this_clue.length() != this_soln.length()) good = false;
	  
	  this_clue = SortString(this_clue);
	  this_soln = SortString(this_soln);

	  if(!this_clue.equals(this_soln)) good = false;

	  if(good) should_print = true;
	}
      if(should_print)
	System.out.println(soln);
    }
  }

  public static String SortString(String inputString) 
  { 
    // convert input string to char array 
    char tempArray[] = inputString.toCharArray(); 
    
    // sort tempArray 
    Arrays.sort(tempArray); 
    
    // return new sorted string 
    return new String(tempArray); 
  } 
}
