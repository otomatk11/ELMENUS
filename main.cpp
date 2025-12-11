


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


bool   displayUsers(UserType filter);
void   breakLine(const string& title);
void   printHeader(int rows, const string& title, bool bottom_line);
void   printMenu();
void   prompt(const string& str, DataType dt, void* out);
int    prompt_constraints(const string& str, int size, const string* list);
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

                // cout << id << " has been added\n";
			} break;
			
			case MenuItem::NEW_ORDER: // create a new order
			{
				// choose customer
				if(!displayUsers(UserType::Customer)) {
                    cout << " . No Customers\n";
                    continue;
                }
				
				string customerID;
				int id;
				
                prompt("CustomerID: ", DataType::STR, &customerID);

				// check user vaild, and if it is customer
				User* user = findUser(customerID);
				if(!user) {
					// cout << "User does not exist\n";
					break;
				}
				
				if(user->getType() != UserType::Customer) {
					cout << "please select a customer\n";
					break;
				}
				
				prompt("New OrderID: ", DataType::INT, &id);
				
				Customer* cus = static_cast<Customer*>(user);
				orders[order_i++] = new Order(id, cus);
				
				cout << "New order has been created\n";
			} break;
			
			case MenuItem::ADD:       // adds items to order
			{
                int numAddItems;
                // int addOrderID;
                string addOrder_ID;
                
                prompt("OrderID: ", DataType::STR, &addOrder_ID);
				
				// check order
				Order* order = findOrder(addOrder_ID);
				if(!order) {
					// cout << "invalid order\n";
					break;
				}
				
                prompt("Number of items: ", DataType::INT, &numAddItems); 
                
                // addOrderID = stoi(addOrder_ID);

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
                string driver_ID, order_ID;
				
				if(!displayUsers(UserType::Driver)) {
					cout << " . No drivers\n";
					break;
				}
				
				prompt("DriverID: ", DataType::STR, &driver_ID);
				prompt("OrderID: ", DataType::STR, &order_ID);
				
                Order* order = findOrder(order_ID);
                User* user = findUser(driver_ID);
				if(!order || !user) {
					// cout << "error, order or driver does not exist\n";
					break;
				}
				
				// check user type
				if(user->getType() != UserType::Driver) {
					cout << "invalid user, select a driver instead\n";
					break;
				}
                
				DliveryDriver* dd = static_cast<DliveryDriver*>(user);
				order->assignDriver(dd);
            } break;
			
			case MenuItem::UPDATE:    // update order status
			{
                string orderID;

                prompt("OrderID: ", DataType::STR, &orderID);
				
				Order* order = findOrder(orderID);
				if(!order) {
					// cout << "invalid order\n";
					break;
				}

                // to update order status, we create two lists
                //  1. status list, for all avilable status.
                //  2. list name, for status strings name
                // we let the user choose the status based on its index in list
                // and we map that index into 'status'.

                // ask for new status
				OrderStatus status[5];
				status[0] = OrderStatus::PENDING;
				status[1] = OrderStatus::PREPARING;
				status[2] = OrderStatus::OUT_OF_DELIVERY;
				status[3] = OrderStatus::DELIVERED;
				status[4] = OrderStatus::CANCELLED;

                string list[5];
                list[0] = orderStatusName(status[0]);
                list[1] = orderStatusName(status[1]);
                list[2] = orderStatusName(status[2]);
                list[3] = orderStatusName(status[3]);
                list[4] = orderStatusName(status[4]);

                int pickIndex = 
                    prompt_constraints("Choose a status: ", 5, list);

                order->updateStatus(status[pickIndex]);
            } break;
			
			case MenuItem::DIS_ORD:   // display order status
			{
                string idOfOrder;
                Order* dispOrder;

                prompt("OrderID: ", DataType::STR, &idOfOrder);
                dispOrder= findOrder(idOfOrder);

                if(dispOrder == NULL)
                {
                    // cout<< "No order with entered ID"<< endl;
                    break;
                }
                // dispOrder->displayOrder();
				
				string statusName = orderStatusName(dispOrder->getStatus());
				cout << "Order status: " << statusName << endl;
				
            } break;
			
			case MenuItem::DIS_CUS: // display custorm information
			{
                string cusID;
                User* dispCus;

                prompt("CustomerID: ", DataType::STR, &cusID);
                dispCus= findUser(cusID);

                if(dispCus == NULL)
                {
                    // cout<< "No customer with the entered ID "<< endl;
                    break;
                }

                dispCus->displayInfo();
            } break;
			
			case MenuItem::DIS_DRI: // display dirver information
			{
                string drivID;
                User* dispDriver;

                prompt("DriverID: ", DataType::STR, &drivID);
                dispDriver= findUser(drivID);
                
                if(dispDriver == NULL)
                {
                    // cout <<"No driver with the entered ID "<< endl;
                    break;
                }

                dispDriver->displayInfo();
            } break;
			
			case MenuItem::CMP:     // compare two orders by total
			{
                Order* order1;
                Order* order2;
                string orderID_1, orderID_2;

                prompt("Order 1\'s ID: ", DataType::STR, &orderID_1);
                prompt("Order 2\'s ID: ", DataType::STR, &orderID_2);

                order1 = findOrder(orderID_1);
                order2 = findOrder(orderID_2);

                if(!order1 || !order2) {
                    // cout << " . No Orders!\n";
                    break;
                }
                
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
                cout << "Registered Users: " << User::getTotalUsers() << ": ";
                cout << customers_counter << " Customers, ";
                cout << drivers_counter << " Drivers.\n";

                // Orders
                cout << "Number of Orders: " << Order::getTotalOrders() << "\n";
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
                    if(users[i]->getType() == UserType::Driver) {
                        fd->saveDriver((DliveryDriver&)( *(users[i])) );
						counter++;
					}
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
                // in this case, just print how many orders are writter to the 
                // binary file.

                const int bytes = fd->getBINSize();
                cout << bytes << " Bytes are writter\n";
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
	
	delete fd;

	for(int i = 0; i < user_i; i++)
		delete users[i];
	
	for(int i = 0; i < order_i; i++)
		delete orders[i];

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

		// Source - https://stackoverflow.com/a
		// Posted by Evan Teran, modified by community. See post 'Timeline' for change history
		// Retrieved 2025-12-07, License - CC BY-SA 3.0
		// std::cin.ignore((unsigned int)~0);

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

int prompt_constraints(const string& str, int size, const string* list) {

    // print list
    for(int i = 0; i < size; i++) {
        cout << setw(3) << i << ". " 
             << list[i] << endl;
    }

    int index;
	
	while(true) {
		prompt(str, DataType::INT, &index);
		
        // is in range?
		if(index < size && index >= 0)
			break;
		
		cout << "out of range!\n";
	}

    return index;
}

Order* findOrder(string str)
{
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

User* findUser(string str)
{
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