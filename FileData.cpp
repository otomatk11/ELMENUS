//
//
//
// Haytham Ashraf  - 20246070 - G8
// Mahmoud Shalaby - 20246102 - G8


#include <iostream>
#include "FileData.h"

using namespace std;

// name of file to save orders
const string ORDERS_FILE = "orders.txt";

// driver statistics file 
const string DRIVERS_FILE = "drivers.txt";

// driver statistics binary file 
const string ORDERS_BIN_FILE = "orders.dat";

/*
void printOrderDetails(OrderDetails* details) {
    cout << "OrderID: " << details->id << endl;
    cout << "Status: " << orderStatusName((OrderStatus) details->status ) << endl;
    cout << "Capacity: " << details->capacity << endl;
    cout << endl;
}
*/

FileData::FileData()
{
    orders_file.open(ORDERS_FILE, fstream::out);
    drivers_file.open(DRIVERS_FILE, fstream::out);

	// this line fails, the file can't be opened,
	// using fstream::trunc, solves the problem.
    orders_bin_file.open(ORDERS_BIN_FILE, fstream::out | fstream::in | fstream::trunc);
}

FileData::~FileData()
{
    if(orders_file.is_open()) orders_file.close();
    if(drivers_file.is_open()) drivers_file.close();
    if(orders_bin_file.is_open()) orders_bin_file.close();
}

void FileData::saveOrder(const Order& order)
{
	if(orders_file.is_open())
		orders_file << order;
	else
		cout << ORDERS_FILE << " is not opened!\n";
}

void FileData::saveDriver(const DliveryDriver& driver)
{
    if(drivers_file.is_open())
		drivers_file << driver;
	else
		cout << DRIVERS_FILE << " is not opened\n";
}

void FileData::saveOrderBIN(Order& order)
{
    if(!orders_bin_file.is_open()) {
		cout << ORDERS_BIN_FILE << " file is not opened\n";
		return;
	}
	
	OrderRecord record;
	
	record.id = stoi(order.getOrderId());
	record.status = (int)order.getStatus();
	record.capacity = order.getItemCount();
	
	orders_bin_file.write((char*)&record, sizeof(OrderRecord));
}

int FileData::getBINSize() 
{
	if(!orders_bin_file.is_open())
		return 0;
    return orders_bin_file.tellp();
}

OrderRecord* FileData::loadOrder(int pos) {

	// calculate file size
	orders_bin_file.seekg(0, fstream::end);
	const int SIZE = orders_bin_file.tellp();
    
	// move to position
	orders_bin_file.seekg(
		pos * (sizeof(OrderRecord) /* + 35 */),
		fstream::beg
	);
	
	// compare current reading position index with the file size.
	const int CPOS = orders_bin_file.tellp();
	if(SIZE == CPOS) {
		return NULL;
	}
	
	// hopefully we can read now...
	OrderRecord* record = new OrderRecord;
	orders_bin_file.read((char*)record, sizeof(OrderRecord));
	
	/*
	// 'ID: '
	orders_bin_file.seekg(4, fstream::cur);
	orders_bin_file.read((char*)&details->id, sizeof(int));
	
	// '\nStatus: '
	orders_bin_file.seekg(10, fstream::cur);
	orders_bin_file.read((char*)&details->status, sizeof(int));
	
	// '\nCapacity: '
	orders_bin_file.seekg(12, fstream::cur);
	orders_bin_file.read((char*)&details->capacity, sizeof(int));
	
	// '\n'
	// orders_bin_file.seekg(1, fstream::cur);
	*/
	
	return record;
}