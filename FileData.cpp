


#include <iostream>
#include "FileData.h"

using namespace std;

// name of file to save orders
const string ORDERS_FILE = "orders.txt";

// driver statistics file 
const string DRIVERS_FILE = "drivers.txt";

// driver statistics binary file 
const string ORDERS_BIN_FILE = "orders.bin";


FileData::FileData()
{
    orders_file.open(ORDERS_FILE, fstream::out | fstream::in | fstream::app);
    drivers_file.open(DRIVERS_FILE, fstream::out | fstream::app);
    orders_bin_file.open(ORDERS_BIN_FILE, fstream::out | fstream::app | fstream::binary);
}

FileData::~FileData()
{
    orders_file.close();
    drivers_file.close();
    orders_bin_file.close();
}

void FileData::saveOrder(const Order& order)
{
    orders_file << order;
}

void FileData::saveDriver(const DliveryDriver& driver)
{
    drivers_file << driver;
}

void FileData::saveOrderBIN(const Order& order)
{
    orders_bin_file << order;
}

int FileData::getBINSize() 
{
    return orders_bin_file.tellp();
}

OrderDetails FileData::loadOrder(int pos) {

    OrderDetails details;

    // check file size
    orders_bin_file.seekg(0, ios_base::end);
    const int SIZE = orders_bin_file.tellp();
    orders_bin_file.seekg(pos * sizeof(OrderDetails), ios_base::beg);

    if(SIZE) {
        cout << " . Bad file\n";
        return details;
    }

    const int pos1 = orders_bin_file.tellp();
    orders_bin_file.read((char*)&details, sizeof(OrderDetails));
    const int pos2 = orders_bin_file.tellp();

    // check 
    if( pos1 - pos2 <= 0 ) {
        cout << "error, position too big, or no orders are in file\n";
    }

    return details;
}