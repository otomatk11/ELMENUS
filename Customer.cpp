//
//
//
// Haytham Ashraf  - 20246070 - G8
// Mahmoud Shalaby - 20246102 - G8


#include <iostream>
#include "Status.h"
#include "Customer.h"

using namespace std;

Customer::Customer() : User()
{
}

Customer::Customer(
    string id,
    string n,
    string p,
    string deliveryA,
    int loyaltyP
) : User(id, n, p)
{
    deliveryAddress_ = deliveryA;
    loyaltyPoints_ = loyaltyP;

    userType_ = UserType::Customer;
}

void Customer::displayInfo()
{
    cout << "UserID: " << userid_ << endl;
    cout << "Type: " << userTypeName(userType_) << endl;
	cout << "Name: " << name_ << endl;
	cout << "Phone Number: " << phonenumber_ << endl;
	
    cout << "Delivery Address: " << deliveryAddress_ << endl;
    cout << "Loyalty Points: " << calculateEarnings() << endl;
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
