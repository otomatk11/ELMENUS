

#include <iostream>
#include "Status.h"
#include "DliveryDriver.h"

using namespace std;


DliveryDriver::DliveryDriver() 
{
    vehicalType_ = "";
    completeDliveries_ = 0;
    totalEarnings_ = 0.0;

    userType_ = UserType::Driver;
}

DliveryDriver::DliveryDriver(
	std::string id,
	std::string n,
	std::string p,
	std::string vehicalType,
	int completeDliveries,
	double totalEarnings
) {
    vehicalType_ = vehicalType;
    completeDliveries_ = completeDliveries;
    totalEarnings_ = totalEarnings;

    userType_ = UserType::Driver;
}

DliveryDriver::DliveryDriver(const DliveryDriver& dd) : User(dd)
{
    vehicalType_ = dd.vehicalType_;
    completeDliveries_ = dd.completeDliveries_;
    totalEarnings_ = dd.totalEarnings_;

    userType_ = UserType::Driver;
}

void DliveryDriver::displayInfo() 
{
    // User::displayInfo();

	cout << "UserID: " << userid_ << endl;
	cout << "Name: " << name_ << endl;
	cout << "Phone Number: " << phonenumber_ << endl;

    cout << "Vehcial Type: " << vehicalType_ << endl;
    cout << "CompleteDliveries: " << completeDliveries_ << endl;
    cout << "Total Earnings: " << totalEarnings_ << endl;
}

double DliveryDriver::calculateEarnings() 
{
    return totalEarnings_;
}

void DliveryDriver::completeDlivery(double orderValue) 
{
    const double TAX = 0.75; // 75% tax

    totalEarnings_ += orderValue * TAX;
}

// postfix
DliveryDriver DliveryDriver::operator++() 
{
    DliveryDriver before = *this;
    completeDliveries_++;
    return before;
}

// prefix
DliveryDriver& DliveryDriver::operator++(int)
{
    ++completeDliveries_;
    return *this;
}

string DliveryDriver::getVehicalType()
{
    return vehicalType_;
}

int DliveryDriver::getCompleteDliveries()
{
    return completeDliveries_;
}

double DliveryDriver::getTotalEarnings()
{
    return totalEarnings_;
}

ostream& operator<<(ostream& os, const DliveryDriver& dd) {
	
	os << "Complete Deliveries: " << dd.completeDliveries_;
	os << ", Total Earning: " << dd.totalEarnings_;
	os << endl;
	
	return os;
}