//
//
//
// Haytham Ashraf  - 20246070 - G8
// Mahmoud Shalaby - 20246102 - G8

#ifndef _ORDER_H_
#define _ORDER_H_

#include <string>
#include <fstream>
#include "FoodItem.h"
#include "Customer.h"
#include "DliveryDriver.h"

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

	OrderStatus getStatus();
    std::string getOrderId();
    Customer* getCustomer();
    DliveryDriver* getDriver();
    int getItemCount();
	
    void operator+=(const FoodItem& item);

    Order& operator+ (const Order& order);

    friend std::ostream& operator<<(std::ostream& os, const Order& order);

    friend bool operator>(const Order& o1, const Order& o2);

    FoodItem& operator[](int index);
private:

    // resize current items_, and copy old content
    void resize_(int moreSize);
};



#endif // _ORDER_H_