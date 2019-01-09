import java.util.*;

public class LoveDarcy {
  public static void main(String[] args) {
    new LoveDarcy().run();
  }

  void run(){
    Scanner in = new Scanner(System.in);
    
    int a = in.nextInt(), b = in.nextInt(), c = in.nextInt();
    double ans = f(a,b,c);
    ans = Math.min(ans,f(b,c,a));
    ans = Math.min(ans,f(c,a,b));
    System.out.printf("%.12f",ans);
  }

  double f(double a, double b, double c){
        double PI = Math.PI;
        double EPS = 1e-12;
        if(a < b) {
            double t = a; a = b; b = t;
        }
	// Use cosine law to find the angle in the corner
	double theta = Math.acos( (a*a + b*b - c*c) / (2*a*b) );


	// Boundary conditions!
	// (a) Will this triangle fit into this quadrant?
	if(theta > PI/2)
		return Math.max(a,Math.max(b,c));
	
	// (b) Can we use the main diagonal?
	if(theta <= PI/4){
		double width  = a * Math.cos(PI/4);
		double height = b * Math.cos(PI/4 - theta);
		if(height < width)
			return width;
	}

	// We now want to find phi so that
	// a * cos(phi) = b * cos(PI/2 - theta - phi)
	// Answer is then a * cos(phi)

	double lo = 0, hi = Math.min(PI/4,PI/2 - theta);
	while(hi - lo > EPS){
		double mid = (lo + hi)/2;
		double left = a * Math.cos(mid);
		double right = b * Math.cos(PI/2 - theta - mid);
                if(left > right) lo = mid;
                else hi = mid;
	}

	return a * Math.cos((lo+hi)/2);
  }
}
