
#include <iostream>
#include "Status.h"
#include "Customer.h"

using namespace std;

Customer::Customer() : User()
{
}

Customer::Customer(
		std::string id,
		std::string n,
		std::string p,
		std::string deliveryA,
		int loyaltyP
) : User(id, n, p)
{
    setDeliveryAddress(deliveryA);
    setLoyaltyPoints(loyaltyP);

    userType_ = UserType::CUSTOMER;
}

void Customer::displayInfo()
{
    cout << "UserID: " << userid_ << endl;
	cout << "Name: " << name_ << endl;
	cout << "Phone Number: " << phonenumber_ << endl;
	
    cout << "Delivery Address: " << deliveryAddress_ << endl;
    cout << "Loyalty Points: " << loyaltyPoints_ << endl;
}

double Customer::calculateEarnings()
{
    const double TAX = 0.5;
    return loyaltyPoints_ * TAX;
}

void Customer::setDeliveryAddress(string a)
{
    deliveryAddress_ = a;
}

void Customer::setLoyaltyPoints(int p)
{
    loyaltyPoints_ = p;
}

void Customer::operator+=(int o)
{
    loyaltyPoints_ += o;
}
