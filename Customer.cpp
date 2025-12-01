//
//
// Author: Mahmoud Shalaby

#include <iostream>
#include "Status.h"
#include "Customer.h"

using namespace std;

Customer::Customer() : User()
{
    deliveryAddress = "";
    loyaltyPoints = 0;

    userType = UserType::CUSTOMER;
}

Customer::Customer(string deliveryA, int loyaltyP) : User()
{
    setDeliveryAddress(deliveryA);
    setLoyaltyPoints(loyaltyP);

    userType = UserType::CUSTOMER;
}

void Customer::displayinfo()
{
    User::displayInfo();

    cout<< deliveryAddress<< endl;
    cout << loyaltyPoints<< endl;
}

double Customer::calculateEarnings()
{
    const double TAX = 0.5;

    return loyaltyPoints * TAX;
}

void Customer::setDeliveryAddress(string a)
{
    deliveryAddress = a;
}

void Customer::setLoyaltyPoints(int p)
{
    loyaltyPoints = p;
}

void Customer::operator+=(int o)
{
    loyaltyPoints += o;
}
