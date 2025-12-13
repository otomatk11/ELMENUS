//
//
//
// Haytham Ashraf  - 20246070 - G8
// Mahmoud Shalaby - 20246102 - G8

#ifndef Customer_h
#define Customer_h

#include <string>
#include "User.h"

class Customer : public User
{
private:

    std::string deliveryAddress_;
    int loyaltyPoints_;
public:

    Customer();
    Customer(
		std::string id,
		std::string n,
		std::string p,
		std::string deliveryA,
		int loyaltyP
	);

    void displayInfo();
    double calculateEarnings();
    void setDeliveryAddress(std::string a);
    void setLoyaltyPoints(int p);

    std::string getDeliveryAddress();
    int getLoyaltyPoints();

    void operator+=(int o);
};

#endif