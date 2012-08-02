/*
 * What is the first fibonacci number to contain 1000 digits?
 */
import java.math.BigInteger;

public class fib { 
	public static void main (String[] args) {
		BigInteger a = new BigInteger("1");
		BigInteger b = new BigInteger("1");
		BigInteger temp;
		BigInteger goal = (new BigInteger("10")).pow(1000-1);
		int i = 2;

		while (a.compareTo(goal) < 0) {
			i++;
			temp = a;
			a = a.add(b);
			b = temp;
		} 
		System.out.println(i);
	}
}
