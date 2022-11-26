package CreditCardProxy;

public class ClientDriver {
	public static void main(String[] args) {
		//Initializes Payment Options
		Payment paymentMethod1 = new Cash();
		Payment paymentMethod2 = new CreditCard();
		
		//Making Cash Payments
		System.out.println("\nCash Payments");
		paymentMethod1.makePayment("$5.99");
		paymentMethod1.makePayment("$20.84");
		paymentMethod1.makePayment("$8.67");
		
		//Making Credit Card Payments (Proxy)
		System.out.println("\nCredit Card Payments");
		paymentMethod2.makePayment("$50.15");
		paymentMethod2.makePayment("$2.33");
		paymentMethod2.makePayment("$12.62");
	}
}
