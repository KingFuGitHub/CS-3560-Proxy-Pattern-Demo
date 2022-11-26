package CreditCardProxy;

//CreditCard "implements" the Payment interface
public class CreditCard implements Payment
{
 private final Payment paymentMethod = new Cash();
 
 /*
 * This method validates the customer's credit card access.
 * This is an extra functionality for the payment process. 
 * This precedes the process of paying.
 * Example of protection proxy
 */
	private boolean validateAccess() {
	    System.out.println("Validating Credit Card Access...");
	    return true;
	}
	
	/*
 * This method updates the payment history of the credit card. 
 * This safeguards the case that the customer's receipt has been lost
 * This is an extra functionality for the payment process. 
 * This follows the process of paying.
 * Example of logging proxy
 */
	private void updatePaymentHistory() {
	    System.out.println("Adding purchase to credit card payment history.");
	}

 /*
 * This method makes the payment with the credit card as well. The usage of
 * the credit card as a proxy allows for the additional methods to execute
 * before and after the payment request.
 * @param amount - payment amount
 */
	@Override
	public void makePayment(String amount) {
	    if(validateAccess()) {
	        paymentMethod.makePayment(amount); //Makes the real payment.
	        updatePaymentHistory();
	    }
	    else {
	        System.out.println("Purchase Failed!");
	    }
	    return;
	}
}