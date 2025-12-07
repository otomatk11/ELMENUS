


#include <iostream>
#include <iomanip>
#include "User.h"
#include "Order.h"
// #include "Prompt.h"

using namespace std;

// constants
const int MENU_WIDTH = 40;

// title of the application
const string TITLE = "ELMENUS MANAGEMENT SYSTEM v1.0";

User* users[50];
Order* orders[50];
int user_i = 0; // users index
int order_i = 0; // orders index

enum MenuItem {
	// User Management
	REG_CUS,        // register a new customer
	REG_DRI,        // register a new driver

	// Order Management
	NEW_ORDER,      // create a new order
	ADD,            // adds items to order
	ASSIGN,         // assign driver to order
	UPDATE,         // update order status
	DIS_ORD,        // display order status

	// Information Management
	DIS_CUS,        // display custorm information
	DIS_DRI,        // display dirver information
	CMP,            // compare two orders by total
	DIS_SYS,        // display system statistics

	// File Operations
	SAVE_ORDERS,    // save completed orders to a file
	SAVE_DRIVERS,   // save driver statistics to a file

	// Extra(Bonus) Features
	SAVE_ORDERS_BIN, // save orders to a binary file
	LOAD,            // load order by position
	BIN_STAT,        // binary file statistics

	// System
	MENU,            // print this menu
	EXIT,            // exit the system
};

enum class DataType {
	INT,
    STR,
    DOUBLE
};


void   breakLine(const string& title);
void   printHeader(int rows, const string& title, bool bottom_line);
void   printMenu();
string dataTypeName(DataType dt);
void   prompt(const string& str, DataType dt, void* out);



int main() {

	bool shouldExit = false;

    // print program's splash and menu
    printHeader(3, TITLE, false);
    printMenu();

    while(!shouldExit) {

        int option;

        prompt("\n>> ", DataType::INT, &option);

        switch(option) {
			case MenuItem::REG_CUS: // register a new customer
			{
				string id;
				string n;
				string p;
				string deliveryA;
				int loyaltyP;

				prompt("UserID: ", DataType::STR, &id);
				prompt("Name: ", DataType::STR, &n);
				prompt("Phone Number: ", DataType::STR, &p);
				prompt("Delivery Address: ", DataType::STR, &deliveryA);
				prompt("Loyalty Points: ", DataType::INT, &loyaltyP);
				
				users[user_i] = new Customer(id, n, p, deliveryA, loyaltyP);
				user_i++;
			} break;
			
			case MenuItem::REG_DRI: // register a new driver
			{
				string id;
				string n;
				string p;
				string vehicalType;
				int completeDeliveries;
				double totalEarning;

				prompt("UserID: ", DataType::STR, &id);
				prompt("Name: ", DataType::STR, &n);
				prompt("Phone Number: ", DataType::STR, &p);
				prompt("Vehical Type: ", DataType::STR, &vehicalType);
				prompt("Complete Deliveries: ", DataType::INT, &completeDeliveries);
				prompt("Total Earning: ", DataType::DOUBLE, &totalEarning);
				
				users[user_i] = new DliveryDriver(
                    id,
                    n,
                    p,
					vehicalType,
                    completeDeliveries,
                    totalEarning
				);
				
				user_i++;
			} break;
			
			case MenuItem::NEW_ORDER: // create a new order
			{
				int orderId;
				Customer* customer;
				
				prompt("Order ID: ", DataType::INT, &orderId);
				
				cout << "Choose Customer:\n";
				for(int i = 0; i < user_i; i++)
					cout << setw(3) << i << ". " << users[i]->getName() << endl;
				
				int cus_index;
				prompt("Choose Customer: ", DataType::INT, &cus_index);
				
			} break;
			
			case MenuItem::ADD:       // adds items to order
			{} break;
			
			case MenuItem::ASSIGN:    // assign driver to order
			{} break;
			
			case MenuItem::UPDATE:    // update order status
			{} break;
			
			case MenuItem::DIS_ORD:   // display order status
			{} break;
			
			case MenuItem::DIS_CUS: // display custorm information
			{} break;
			
			case MenuItem::DIS_DRI: // display dirver information
			{} break;
			
			case MenuItem::CMP:     // compare two orders by total
			{} break;
			
			case MenuItem::DIS_SYS: // display system statistics
			{} break;
			
			case MenuItem::SAVE_ORDERS:  // save completed orders to a file
			{} break;
			
			case MenuItem::SAVE_DRIVERS: // save driver statistics to a file
			{} break;
			
			case MenuItem::SAVE_ORDERS_BIN: // save orders to a binary file
			{} break;
			
			case MenuItem::LOAD:            // load order by position
			{} break;
			
			case MenuItem::BIN_STAT:        // binary file statistics
			{} break;
			
            case MenuItem::MENU: // print menu
                printMenu();
				break;

            case MenuItem::EXIT: // exit program
                shouldExit = true;
				break;

            default:
                cout << "Unknow option\n";
        }
    }

	for(int i = 0; i < user_i; i++)
		delete users[i];
	
	for(int i = 0; i < order_i; i++)
		delete orders[i];

    return 0;
}

void breakLine(const string& title) {

    cout << "+";

    // check if title is odd numbered, just spit out an empty space
    // this is done to fix some issues with headers
    if(title.length() % 2 == 1)
        cout << " ";

    const int HALF_WAY = (MENU_WIDTH-title.length()) / 2;
    for(int c = 0; c < HALF_WAY - 1; c++)
        cout << "-";
    cout << title;
    for(int c = 0; c < HALF_WAY - 1; c++)
        cout << "-";

    cout << "+\n";
}

void printHeader(int rows, const string& title, bool bottom_line) {

    // print top line
    breakLine("");

    for(int i = 0; i < rows; i++) {

        cout << "|";
        if(i == (rows-1) / 2) {

            // check if title is odd numbered, just spit out an empty space
            // this is done to fix some issues with headers
            if(title.length() % 2 == 1)
                cout << " ";

            // print title
            const int HALF_WAY = (MENU_WIDTH-title.length()) / 2;
            for(int c = 0; c < HALF_WAY - 1; c++)
                cout << " ";
			
            cout << title;
            for(int c = 0; c < HALF_WAY - 1; c++)
                cout << " ";
			
        } else {

            // print empty
            for(int c = 0; c < MENU_WIDTH-2; c++)
                cout << " ";
        }
        cout << "|\n";
    }

    // bottom line
    if(bottom_line)
        breakLine("");
}

void printMenu() {

    printHeader(1, "User Management", true);
    cout << setw(3) << (int)MenuItem::REG_CUS << ". " << "Register a new customer" << endl;
    cout << setw(3) << (int)MenuItem::REG_DRI << ". " << "Register a new driver" << endl;

    printHeader(1, "Order Management", true);
    cout << setw(3) << (int)MenuItem::NEW_ORDER << ". " << "Create a new order" << endl;
    cout << setw(3) << (int)MenuItem::ADD << ". " << "Add items to order" << endl;
    cout << setw(3) << (int)MenuItem::ASSIGN << ". " << "Assign driver to order" << endl;
    cout << setw(3) << (int)MenuItem::UPDATE << ". " << "Update order status" << endl;
    cout << setw(3) << (int)MenuItem::DIS_ORD << ". " << "Display order status" << endl;

    printHeader(1, "Information Management", true);
    cout << setw(3) << (int)MenuItem::DIS_CUS << ". " << "Display customer information" << endl;
    cout << setw(3) << (int)MenuItem::DIS_DRI << ". " << "Display driver information" << endl;
    cout << setw(3) << (int)MenuItem::CMP << ". " << "Compare two orders by total" << endl;
    cout << setw(3) << (int)MenuItem::DIS_SYS << ". " << "Display system statistics" << endl;

    printHeader(1, "File Operations", true);
    cout << setw(3) << (int)MenuItem::SAVE_ORDERS << ". " << "Save completed orders to a file" << endl;
    cout << setw(3) << (int)MenuItem::SAVE_DRIVERS << ". " << "Save driver statistics to a file" << endl;
    cout << setw(3) << (int)MenuItem::DIS_SYS << ". " << "Display system statistics" << endl;

    printHeader(1, "Extra Features", true);
    cout << setw(3) << (int)MenuItem::SAVE_ORDERS_BIN << ". " << "Save orders to a binary file" << endl;
    cout << setw(3) << (int)MenuItem::LOAD << ". " << "Load order by position" << endl;
    cout << setw(3) << (int)MenuItem::BIN_STAT << ". " << "Binary file statistics" << endl;

    breakLine("System");
    cout << setw(3) << (int)MenuItem::MENU << ". " << "Print This Menu" << endl;
    cout << setw(3) << (int)MenuItem::EXIT << ". " << "Exit" << endl;
    // breakLine("");
}

string dataTypeName(DataType dt) {
    switch(dt) {
        case DataType::INT: return "int";
        case DataType::STR: return "string";
        case DataType::DOUBLE: return "double";
    }
    return "Unknown";
}

void prompt(const string& str, DataType dt, void* out) {

	string input;
	
    while(true) {

		cout << str;

        cin.ignore();
        getline(cin, input);

        // now we try to find the expected datatype of input
        // assume by default it is an integer
        DataType inputType = DataType::INT;

        for(int i = 0; i < input.length(); i++) {

            // bool found_dot = false;
            bool is_integer = (input[i] >= 0x30) &&
                              (input[i] <= 0x39);

            // check for a double
            if(input[i] == '.') {

                if(inputType == DataType::DOUBLE) {
                    // we have already found a '.' before
                    // tread this input as string instead
                    inputType = DataType::STR;
                    break;
                }

                if(inputType == DataType::INT) {
                    // in this case, our input number becomes a double
                    inputType = DataType::DOUBLE;
                }

                // found_dot = true;
                continue;
            }

            if(!is_integer) {         
                inputType = DataType::STR;
                break;
            }
        }
		
		// special case, any input could be used as a string
		if(dt == DataType::STR) {
            *(string*)out = input;
			break;
		}
		
		// any int could be a double
		if(dt == DataType::DOUBLE && inputType == DataType::INT) {
			*(double*)out = stod(input);
			break;
		}

        if(dt == inputType) {

            switch(dt) {
                case DataType::STR:
                    *(string*)out = input;
                    break;
                case DataType::INT:
                    *(int*)out = stoi(input);
                    break;
                case DataType::DOUBLE:
                    *(double*)out = stod(input);
                    break;
            }
            
            break;
        }

        cout << "prompt: expected \"" << dataTypeName(dt )<< "\"\n";
    }
}