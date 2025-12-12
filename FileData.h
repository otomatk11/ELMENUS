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
#include "Order.h"

struct OrderRecord {
    int id; 	    // "ID: "
    int status;     // ", Status: "
    int capacity;   // ", Capacity: "
};

class FileData {
private:

    std::fstream orders_file;
	std::fstream drivers_file;
	std::fstream orders_bin_file;

public:

    FileData();
    ~FileData();

    void saveOrder(Order& order);
    void saveDriver(DliveryDriver& driver);
    void saveOrderBIN(Order& driver);

    int getBINSize();

    // load an order from the binary file
    OrderRecord* loadOrder(int pos);
};


#endif // _FILE_DATA_H_