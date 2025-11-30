

#ifndef _ORDER_H_
#define _ORDER_H_

#include <string>
#include "OrderStatus.h"
#include "Custormer.h"
#include "DilveryDriver.h"
#include "FoodItem.h"

class Order
{
private:

    std::string orderId_;
    Custormer* customer_;
    DilveryDriver* dirver_;
    int itemCount_;
    FoodItem* items_;
    int itemCount_;
    int capacity_;
    OrderStatus status_;
    static int totalOrders_;
public:

    Order();
    Order(const Order& order);
    Order(int orderId, Custormer* cus);
    ~Order();

    void addItem(const FoodItem& item);
    void assignDriver(DilveryDriver* driver);

    // TBD ...
};



#endif // _ORDER_H_