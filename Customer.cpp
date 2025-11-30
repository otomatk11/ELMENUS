#include "Customer.h"

Customer::Customer()
{
    deliveryAddress= " ";
    loyaltyPoints= 0;
}
Customer::Customer(string deliveryA, int loyaltyP)
{
    setDeliveryAddress(deliveryA);
    setLoyaltyPoints(loyaltyP);
}
void Customer::displayinfo()
{
    User::displayinfo();
   cout<< deliveryAddress<< endl;
   cout << loyaltyPoints<< endl;
}
double Customer::calculateEarnings()
{
    return loyaltyPoints* 0.5;
}
void Customer::setDeliveryAddress(string a)
{
    deliveryAddress= a;
}
void Customer::setLoyaltyPoints(int p)
{
    loyaltyPoints= p;
}
void Customer::operator+=(int o)
{
    loyaltyPoints += o;
}
