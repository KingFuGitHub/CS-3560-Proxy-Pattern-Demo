package CreditCardProxy;

//Cash "implements" the Payment interface
public class Cash implements Payment
{
 /*
 * This method makes the payment with cash.
 * @param amount - payment amount
 */
 @Override
	public void makePayment(String amount) {
	    System.out.println("Making Payment: " + amount);
	    return;
	}
}
