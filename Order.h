

#ifndef _ORDER_H_
#define _ORDER_H_

#include <string>
#include <fstream>
#include "FoodItem.h"
#include "Customer.h"
#include "DliveryDriver.h"

struct OrderDetails {
    std::string id;
    OrderStatus status;
    // number of foodItems that were stored
    int items;
    int capacity;
};

void printOrderDetails(OrderDetails& details);

class Order
{
private:

    // ID
    std::string orderId_;

    // associations
    Customer* customer_;
    DliveryDriver* driver_;

    // food info
    int itemCount_;
    FoodItem* items_;

    // how many items are inside item_
    int capacity_;

    // order status
    OrderStatus status_;
    static int totalOrders_;
public:

    Order();
    Order(int orderId, Customer* cus);
    Order(const Order& order);
    ~Order();

    void addItem(const FoodItem& item);
    void assignDriver(DliveryDriver* driver);

    // update order status. And if status is 'OrderStatus::DELIVERD'-
    // call drivers's completeDlivery(), and add loyality points to customer.
    void updateStatus(OrderStatus status);

    // return sum of all items
    double calculateTotal() const;

    // display complete orders details
    void displayOrder();

    static int getTotalOrders();

    // getters
    std::string getOrderId();
    const Customer* getCustomer();
    const DliveryDriver* getDriver();
    int getItemCount();

    // add food item
    void operator+=(const FoodItem& item);

    // combine two orders into one order, adds order to *this
    Order& operator+ (const Order& order);

    // print order details
    friend std::ostream& operator<<(std::ostream& os, const Order& order);

    // comparison, based on total price
    friend bool operator>(const Order& o1, const Order& o2);

    // retrive foot item by index
    FoodItem& operator[](int index);
private:

    // resize current items_, and copy old content
    void resize_(int moreSize);
};



#endif // _ORDER_H_