

#ifndef _FILE_CONNECTION_H_
#define _FILE_CONNECTION_H_

#include <string>
#include <fstream>
#include "Status.h"
#include "Customer.h"
#include "DliveryDriver.h"
#include "Order.h"

class FileConnection 
{
private:

	fstream* file_;
public:
	
	FileConnection(const string& fileName, int mode);
	~FileConnection();
	
	// writing
	fstream& operator<< (const Order& order);
	fstream& operator<< (const Customer& customer);
	fstream& operator<< (const DliverDriver& driver);
	
	// reading
	// fstream& operator>> (void);
};

#endif // _FILE_CONNECTION_H_