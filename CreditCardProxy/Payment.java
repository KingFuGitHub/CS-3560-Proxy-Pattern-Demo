package CreditCardProxy;

/**
* Interface for all the different payment methods.
*/
public interface Payment 
{
    /*
    * This method makes the payment with a specified payment method.
    * @param amount - payment amount
    */
    public void makePayment(String amount);
}
