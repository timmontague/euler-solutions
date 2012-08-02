/*
 * What is the sum of the digits of the number 2^1000
 */
import java.math.BigInteger;

public class DigitSum { 
	public static void main (String[] args) {
		BigInteger n = (new BigInteger("2")).pow(1000);
		BigInteger sum = new BigInteger("0");
		BigInteger div[];

		while (n.compareTo(BigInteger.ZERO) > 0) {
			div = n.divideAndRemainder(BigInteger.TEN);
			n = div[0]; // quotient
			sum = sum.add(div[1]); // remainder
		} 
		System.out.println(sum.toString());
	}
}
