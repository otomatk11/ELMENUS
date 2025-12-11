


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
    orders_file.open(ORDERS_FILE, fstream::out | fstream::app);
    drivers_file.open(DRIVERS_FILE, fstream::out | fstream::app);
    orders_bin_file.open(ORDERS_BIN_FILE, fstream::out | fstream::app | fstream::in | fstream::binary);
}

FileData::~FileData()
{
    if(orders_file.is_open()) orders_file.close();
    if(drivers_file.is_open()) drivers_file.close();
    if(orders_bin_file.is_open()) orders_bin_file.close();
}

void FileData::saveOrder(const Order& order)
{
	if(orders_file.is_open()) {
		orders_file << order;
		// orders_file.flush();
	} else
		cout << ORDERS_FILE << " is not opened!\n";
}

void FileData::saveDriver(const DliveryDriver& driver)
{
    if(drivers_file.is_open()) {
		drivers_file << driver;
		// drivers_file.flush();
	} else
		cout << DRIVERS_FILE << " is not opened\n";
}

void FileData::saveOrderBIN(const Order& order)
{
    if(orders_bin_file.is_open()) {
		orders_bin_file << order;
		// orders_bin_file.flush();
	} else
		cout << ORDERS_BIN_FILE << " file is not opened\n";
}

int FileData::getBINSize() 
{
    return orders_bin_file.tellp();
}

OrderDetails* FileData::loadOrder(int pos) {

    OrderDetails* details = NULL;

    /* 
    // check file size
	orders_bin_file.seekg(0, ios_base::end);
	const int SIZE = orders_bin_file.tellp();
	orders_bin_file.seekg(pos * sizeof(OrderDetails), ios_base::beg);

	if(SIZE) {
		cout << " . Bad file\n";
		return details;
	}
	*/

	orders_bin_file.seekg(pos * sizeof(OrderDetails), ios_base::beg);
	int cursorPos = orders_bin_file.tellp();
	
	if(cursorPos != pos * sizeof(OrderDetails)) {
		cout << "error, position is out of reach\n";
		return NULL;
	}
	
	details = new OrderDetails;

    const int pos1 = orders_bin_file.tellp();
    orders_bin_file.read((char*)details, sizeof(OrderDetails));
    const int pos2 = orders_bin_file.tellp();

    // check 
    if( pos1 - pos2 <= 0 ) {
        cout << "error, position too big, or no orders are in file\n";
		delete details;
		return NULL;
    }

    return details;
}