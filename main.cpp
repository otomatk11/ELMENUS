


#include <iostream>
#include <fstream>
#include <iomanip>
#include "Type.h"
#include "Status.h"
#include "User.h"
#include "Order.h"
#include "FileData.h"

using namespace std;

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
	SAVE_ORDERS,     // save completed orders to a file
	SAVE_DRIVERS,    // save driver statistics to a file
	SAVE_ORDERS_BIN, // save orders to a binary file	
	LOAD,            // load order by position
	BIN_STAT,        // binary file statistics

	// System
	MENU,            // print this menu
	EXIT,            // exit the system
};

// width of menu 
const int MENU_WIDTH = 40;

// title of the application
const string TITLE = "ELMENUS MANAGEMENT SYSTEM v1.0";


// data for program
int drivers_counter = 0;
int customers_counter = 0;
User*  users[50];  int user_i = 0;
Order* orders[50]; int order_i = 0;


void   breakLine(const string& title);
void   printHeader(int rows, const string& title, bool bottom_line);
void   printMenu();
void   prompt(const string& str, DataType dt, void* out);
Order* findOrder(string str);
User*  findUser(string str);


int main() {

	bool shouldExit = false;

	FileData* fd = new FileData;
	
    // print program's splash and menu
    printHeader(3, TITLE, false);
    printMenu();

    while(!shouldExit) {

        int option;

        prompt(">> ", DataType::INT, &option);

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
				
                customers_counter++;
				users[user_i++] = new Customer(
					id,
					n,
					p,
					deliveryA,
					loyaltyP
				);
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
				
                drivers_counter++;
				users[user_i++] = new DliveryDriver(
                    id,
                    n,
                    p,
                    vehicalType,
                    completeDeliveries,
                    totalEarning
				);
			} break;
			
			case MenuItem::NEW_ORDER: // create a new order
			{
                if(customers_counter == 0) {
                    cout << " . No Customers\n";
                    break;
                }

                cout << "select customer by id\n";
                for(int i = 0; i < user_i; i++) {
                    cout << setw(3) << i << ". "
                         << "id: " << users[i]->getUserID()
                         << ", name: " << users[i]->getName()
                         << ", type: " << userTypeName(users[i]->getType())
                         << endl;
                }
				
				string customerID;
                prompt("CustomerID: ", DataType::STR, &customerID);

				User* user = findUser(customerID);
				if(!user) break;

                // check user vaild, and if it is customer
                if(user->getType() != UserType::Customer) {
                    cout << "User is not a customer!\n";
                    break;
                }

                int id;
				prompt("New OrderID: ", DataType::INT, &id);
				
                // create the order
				orders[order_i++] = new Order(id, (Customer*)user);                
			} break;
			
			case MenuItem::ADD:       // adds items to order
			{
                int numAddItems;
                string addOrder_ID;

                prompt("OrderID: ", DataType::STR, &addOrder_ID);
				
				// check order
				Order* order = findOrder(addOrder_ID);
				if(!order) break;
				
                prompt("Number of items: ", DataType::INT, &numAddItems); 

                for(int i = 0; i< numAddItems; i++)
                {
					FoodItem item;
					
                    cout << "Item " << i+1 << "\n";

                    string name;
                    int quantity;
                    double price;

                    // request
                    prompt("\tName: ", DataType::STR, &name);
                    prompt("\tPrice: ", DataType::DOUBLE, &price);
                    prompt("\tQuantity: ", DataType::INT, &quantity);

                    // fill in
                    item.setItemName(name);
                    item.setPrice(price);
                    item.setQuantity(quantity);
					
					order->addItem(item);
                }
				
            } break;
			
			case MenuItem::ASSIGN:    // assign driver to order
			{	
				if(drivers_counter == 0) {
                    cout << " . No drivers\n";
                    break;
                }

                cout << "select driver by id\n";
                for(int i = 0; i < user_i; i++) {
                    cout << setw(3) << i << ". "
                         << "id: " << users[i]->getUserID()
                         << ", name: " << users[i]->getName()
                         << ", type: " << userTypeName(users[i]->getType())
                         << endl;
                }

                string driver_ID;
                prompt("DriverID: ", DataType::STR, &driver_ID);

                User* user = findUser(driver_ID);
				if(!user) break;

                // check user type
				if(user->getType() != UserType::Driver) {
					cout << "user is not a driver!\n";
					break;
				}

                string order_ID;
				prompt("OrderID: ", DataType::STR, &order_ID);
				
                Order* order = findOrder(order_ID);
				if(!order) break;

				order->assignDriver((DliveryDriver*)user);
            } break;
			
			case MenuItem::UPDATE:    // update order status
			{
                string orderID;

                prompt("OrderID: ", DataType::STR, &orderID);
				
				Order* order = findOrder(orderID);
				if(!order) break;

                // avilable status
                const int STATUS_SIZE = 5;
				const OrderStatus STATUS[STATUS_SIZE] = {
				    OrderStatus::PENDING,
				    OrderStatus::PREPARING,
				    OrderStatus::OUT_OF_DELIVERY,
				    OrderStatus::DELIVERED,
				    OrderStatus::CANCELLED
                };

                // ask for new status

                cout << "pick status by index: " << endl;
                for(int i = 0; i < STATUS_SIZE; i++) {
                    cout << setw(3) << i << ". "
                         << orderStatusName(STATUS[i])
                         << endl;
                }
                
                int pickIndex;
                prompt("index: ", DataType::INT, &pickIndex);

                // checking
                if(pickIndex < 0 || pickIndex >= STATUS_SIZE) {
                    cout << "out or range! aborting\n";
                    break;
                }
                        
                order->updateStatus(STATUS[pickIndex]);
            } break;
			
			case MenuItem::DIS_ORD:   // display order status
			{
                if(order_i == 0) {
                    cout << " . no orders yet\n";
                    break;
                }

                string idOfOrder;
                prompt("OrderID: ", DataType::STR, &idOfOrder);

                Order* dispOrder = findOrder(idOfOrder);
                if(!dispOrder) break;
				
				cout << "Order " << idOfOrder << "\'s status: " 
                     << orderStatusName(dispOrder->getStatus())
                     << endl;
            } break;
			
			case MenuItem::DIS_CUS: // display custorm information
			{
                if(customers_counter == 0) {
                    cout << "no customers yet\n";
                    break;
                }

                string cusID;

                prompt("CustomerID: ", DataType::STR, &cusID);

                User* dispCus = findUser(cusID);
                if(!dispCus) break;

                dispCus->displayInfo();
            } break;
			
			case MenuItem::DIS_DRI: // display dirver information
			{
                if(drivers_counter == 0) {
                    cout << "no drivers yet\n";
                    break;
                }

                string drivID;

                prompt("DriverID: ", DataType::STR, &drivID);

                User* dispDriver = findUser(drivID);
                if(!dispDriver) break;

                dispDriver->displayInfo();
            } break;
			
			case MenuItem::CMP:     // compare two orders by total
			{
                if(order_i < 2) {
                    cout << "no orders to compare\n";
                    break;
                }

                string orderID_1, orderID_2;

                prompt("Order 1\'s ID: ", DataType::STR, &orderID_1);
                prompt("Order 2\'s ID: ", DataType::STR, &orderID_2);

                Order* order1 = findOrder(orderID_1);
                if(!order1) break;

                Order* order2 = findOrder(orderID_2);
                if(!order2) break;
                
                if(*order1 > *order2)
                    cout << "The first order cost more than the second order" << endl;
                else
                    cout << "The second order cost more than the first order" << endl;
            } break;
			
			case MenuItem::DIS_SYS: // display system statistics
			{
                // in this case, we just print some info about the system.
                // like number of customers, delivery drivers. And Orders.

                cout << " . System Statistics:\n";

                // Users
                cout << "Registered Users: " << User::getTotalUsers() << endl;
                // cout << customers_counter << " Customers, ";
                // cout << drivers_counter << " Drivers.\n";

                for(int i = 0; i < user_i; i++) {
                    cout << "-----User" << i << endl;
                    users[i]->displayInfo();
                }
                cout << "-----" << endl;

                // Orders
                cout << "Number of Orders: " << Order::getTotalOrders() << endl;
                for(int i = 0; i < order_i; i++) {
                    cout << "-----Order" << i << endl;
                    orders[i]->displayOrder();
                }
                cout << "-----" << endl;

            } break;
			
			case MenuItem::SAVE_ORDERS:  // save completed orders to a file
			{
                if(order_i == 0) {
                    cout << " . No orders registered\n";
                    continue;
                }

                int counter = 0;
                for(int i = 0; i < order_i; i++) {
                    fd->saveOrder( *(orders[i]) );
					counter++;
                }

                cout << "written " << counter << " orders\n";
            } break;
			
			case MenuItem::SAVE_DRIVERS: // save driver statistics to a file
			{
				if(drivers_counter == 0) {
					cout << " . No Drivers registered\n";
					continue;
				}

                int counter = 0;
                for(int i = 0; i < user_i; i++) {

                    if(users[i]->getType() != UserType::Driver)
                        continue;

                    fd->saveDriver((DliveryDriver&)( *(users[i])) );
					counter++;
                }

                cout << "written " << counter << " drivers\n";
            } break;
			
			case MenuItem::SAVE_ORDERS_BIN: // save orders to a binary file
			{
				if(drivers_counter == 0) {
					cout << " . No Orders\n";
					continue;
				}

                int counter = 0;
                for(int i = 0; i < order_i; i++) {
					
                    fd->saveOrderBIN( *(orders[i]) );
					counter++;
                }

                cout << "written " << counter << " order\n";
			} break;
			
			case MenuItem::LOAD:            // load order by position
			{
                // given a file with orders, load an order 
                // from the file based on its position in file.

                int position;

                prompt("Order Position: ", DataType::INT, &position);

                OrderDetails* od = fd->loadOrder(position);
				if(!od) {
					cout << "order position does not exist in file\n";
					break;
				}

                printOrderDetails(od);
				
				delete od;
            } break;
			
			case MenuItem::BIN_STAT:        // binary file statistics
			{
                const int BYTES = fd->getBINSize();
                cout << BYTES << " Bytes are writter\n";
            } break;
			
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

    delete fd;

    return 0;
}

bool displayUsers(UserType filter) {

	if(user_i == 0)
        return false;

    int counter = 0;
	
	string typeName = userTypeName(filter);
	
	cout << "ID.  Name: " << " Type: " << typeName << "\n";

    for(int i = 0; i < user_i; i++) {
        if(users[i]->getType() == filter) {

            cout << setw(4) << users[i]->getUserID() << ". "
                 << users[i]->getName() << endl;

            counter++;
        }
    }

	cout << endl;

    return counter > 0;
}

void breakLine(const string& title) {

    const char EDGE_CH = '+';
    const char LINE_CH = '-';
    const int HALF_WAY = (MENU_WIDTH-title.length()) / 2;

    cout << EDGE_CH;

    // check if title is odd numbered, just spit out an empty space
    // this is done to fix some issues with headers
    if(title.length() % 2 == 1)
        cout << " ";

    const string LINE(HALF_WAY-1, LINE_CH);

    cout << LINE;
    cout << title;
    cout << LINE;

    cout << EDGE_CH;
    cout << endl;
}

void printHeader(int rows, const string& title, bool bottom_line) {

    // print top line
    breakLine("");

    const char EMPTY_CH = ' ';
    const char BAR_CH = '|';

    const int HALF_WAY = (MENU_WIDTH-title.length()) / 2;
    const string EMPTY1(HALF_WAY - 1, ' ');
    const string EMPTY2(MENU_WIDTH - 2, ' ');

    for(int i = 0; i < rows; i++) {

        cout << BAR_CH;
        if(i == (rows-1) / 2) {

            // check if title is odd numbered, just spit out an empty space
            // this is done to fix some issues with headers
            if(title.length() % 2 == 1)
                cout << " ";

            // print title
            cout << EMPTY1;
            cout << title;
            cout << EMPTY1;
        } else {

            // print empty
            cout << EMPTY2;
        }
        cout << BAR_CH;
        cout << endl;
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
	cout << setw(3) << (int)MenuItem::SAVE_ORDERS_BIN << ". " << "Save orders to a binary file" << endl;

    // printHeader(1, "Extra Features", true);
    cout << setw(3) << (int)MenuItem::LOAD << ". " << "Load order by position" << endl;
    cout << setw(3) << (int)MenuItem::BIN_STAT << ". " << "Binary file statistics" << endl;

    breakLine("System");
    cout << setw(3) << (int)MenuItem::MENU << ". " << "Print This Menu" << endl;
    cout << setw(3) << (int)MenuItem::EXIT << ". " << "Exit" << endl;
    // breakLine("");
}

void prompt(const string& str, DataType dt, void* out) {

	string input = "";
	
    while(true) {

		cout << str;

        {
            // Source - https://stackoverflow.com/a
            // Posted by Evan Teran, modified by community. See post 'Timeline' for change history
            // Retrieved 2025-12-07, License - CC BY-SA 3.0

            // std::cin.ignore((unsigned int)~0);
        }

        getline(cin, input);

        if(input.length() == 0)
            continue;

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

        // sensitive check
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

        // error message
        cout << "prompt: expected \"" << dataTypeName(dt )<< "\"\n";
    }
}

Order* findOrder(string str) {
    for(int j = 0; j < order_i; j++)
    {
        if(str.compare(orders[j]->getOrderId()) == 0)
        {
            return orders[j];
        }
    }
    cout << "No order exits with the ID enterd" << endl;
    return NULL;
}

User* findUser(string str) {
    for(int j = 0; j < user_i; j++)
    {
        if(str.compare(users[j]->getUserID()) == 0)
        {
            return users[j];
        }
    }
    cout <<"No customer or driver exits with the ID enterd"<< endl;
    return NULL;
}