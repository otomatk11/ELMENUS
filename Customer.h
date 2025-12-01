//
//
// Author: Mahmoud Shalaby

#ifndef Customer_h
#define Customer_h

#include <string>
#include "User.h"

class Customer : public User
{
private:

    std::string deliveryAddress;
    int loyaltyPoints;
public:

    Customer();
    Customer(std::string deliveryA, int loyaltyP);

    void displayinfo();
    double calculateEarnings();
    void setDeliveryAddress(std::string a);
    void setLoyaltyPoints(int p);

    std::string getDeliveryAddress();
    int getLoyaltyPoints();

    void operator+=(int o);
};

#endif