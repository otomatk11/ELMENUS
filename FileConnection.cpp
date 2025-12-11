


#include "FileConnection.h"


FileConnection::ileConnection(const string& fileName, int mode) {
	
	file_.open(fileName, mode);
	if(!file_.is_open()) {
		
		cout << "Failed to open file " << fileName << endl;
		exit(0);
	}
	
	// file_.lock();
	
	// cout << "Opened connection to " << fileName << endl;
}

FileConnection::~FileConnection() {
	
	if(file.is_open())
		file_.close();
	
}
	
// writing
fstream& FileConnection::operator<< (const Order& order) {
	
	
}

fstream& FileConnection::operator<< (const Customer& customer);
fstream& FileConnection::operator<< (const DliverDriver& driver);