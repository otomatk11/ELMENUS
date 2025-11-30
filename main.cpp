


#include <iostream>
#include <iomanip>

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

static const char* PROMPT = (const char*)">> ";

// width of menu, in characters
static const std::string TITLE = "ELMENUS MANAGEMENT SYSTEM v1.0";
static const int MENU_WIDTH = 60;

void BreakLine(const string& title);
void PrintHeader(int rows, const std::string& title, bool bottom_line);
void PrintMenu();


int main() {

    bool shouldExit = false;

    // print program's splash
    PrintHeader(3, TITLE, false);
    PrintMenu();

    while(!shouldExit) {

        cout << PROMPT;

        MenuItem item;
        cin >> (int&)item;

        switch(item) {
            case MenuItem::MENU:
            {
                PrintMenu();
            } break;

            case MenuItem::EXIT:
            {
                shouldExit = true;
            } break;

            default:
                cout << "Unknow option\n";
        }
    }

    return 0;
}

void BreakLine(const string& title) {

    cout << "+";
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

void PrintHeader(int rows, const std::string& title, bool bottom_line) {

    // print top line
    BreakLine("");

    for(int i = 0; i < rows; i++) {

        cout << "|";
        if(i == (rows-1) / 2) {

            // fix '|' not in place, because of title being odd size
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
        BreakLine("");
}

void PrintMenu() {

    PrintHeader(1, "User Management", true);
    cout << setw(3) << (int)MenuItem::REG_CUS << ". " << "Register a new customer" << endl;
    cout << setw(3) << (int)MenuItem::REG_DRI << ". " << "Register a new driver" << endl;

    PrintHeader(1, "Order Management", true);
    cout << setw(3) << (int)MenuItem::NEW_ORDER << ". " << "Create a new order" << endl;
    cout << setw(3) << (int)MenuItem::ADD << ". " << "Add items to order" << endl;
    cout << setw(3) << (int)MenuItem::ASSIGN << ". " << "Assign driver to order" << endl;
    cout << setw(3) << (int)MenuItem::UPDATE << ". " << "Update order status" << endl;
    cout << setw(3) << (int)MenuItem::DIS_ORD << ". " << "Display order status" << endl;

    PrintHeader(1, "Information Management", true);
    cout << setw(3) << (int)MenuItem::DIS_CUS << ". " << "Display customer information" << endl;
    cout << setw(3) << (int)MenuItem::DIS_DRI << ". " << "Display driver information" << endl;
    cout << setw(3) << (int)MenuItem::CMP << ". " << "Compare two orders by total" << endl;
    cout << setw(3) << (int)MenuItem::DIS_SYS << ". " << "Display system statistics" << endl;

    PrintHeader(1, "File Operations", true);
    cout << setw(3) << (int)MenuItem::SAVE_ORDERS << ". " << "Save completed orders to a file" << endl;
    cout << setw(3) << (int)MenuItem::SAVE_DRIVERS << ". " << "Save driver statistics to a file" << endl;
    cout << setw(3) << (int)MenuItem::DIS_SYS << ". " << "Display system statistics" << endl;

    PrintHeader(1, "Extra Features", true);
    cout << setw(3) << (int)MenuItem::SAVE_ORDERS_BIN << ". " << "Save orders to a binary file" << endl;
    cout << setw(3) << (int)MenuItem::LOAD << ". " << "Load order by position" << endl;
    cout << setw(3) << (int)MenuItem::BIN_STAT << ". " << "Binary file statistics" << endl;

    BreakLine("System");
    cout << setw(3) << (int)MenuItem::MENU << ". " << "Print This Menu" << endl;
    cout << setw(3) << (int)MenuItem::EXIT << ". " << "Exit" << endl;
    BreakLine("");
}