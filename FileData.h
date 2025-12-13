//
//
//
// Haytham Ashraf  - 20246070 - G8
// Mahmoud Shalaby - 20246102 - G8

// Simple File for storing system data within files


#ifndef _FILE_DATA_H_
#define _FILE_DATA_H_


#include <fstream>
#include <string>

#include "User.h"
// #include "Customer.h"
// #include "DliveryDriver.h"
#include "Order.h"


class FileData {
private:

    std::fstream orders_file;
	std::fstream drivers_file;
	std::fstream orders_bin_file;

public:

    FileData();
    ~FileData();

    void saveOrder(const Order& order);
    void saveDriver(const DliveryDriver& driver);
    void saveOrderBIN(Order& driver);

    int getBINSize();

    // load an order from the binary file
    OrderDetails* loadOrder(int pos);
};


#endif // _FILE_DATA_H_