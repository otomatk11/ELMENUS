

#ifndef _DLIVERY_DRIVER_H_
#define _DLIVERY_DRIVER_H_


#include <string>
#include "User.h"

class DliveryDriver : public User
{
private:

    std::string vehicalType_;
    int completeDliveries_;
    double totalEarnings_;
public:

    // ctors
    DliveryDriver();
    DliveryDriver(const DliveryDriver& dd);
    DliveryDriver(
		std::string id,
		std::string n,
		std::string p,
		std::string vehicalType,
		int completeDliveries,
		double totalEarnings
	);

    void displayInfo() override;
    double calculateEarnings() override;

    void completeDlivery(double orderValue);

    // postfix
    DliveryDriver operator++();

    // prefix
    DliveryDriver& operator++(int);

    // getters
    std::string getVehicalType();
    int getCompleteDliveries();
    double getTotalEarnings();
};


#endif // _DLIVERY_DRIVER_H_