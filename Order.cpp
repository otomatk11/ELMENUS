//
//
//
// Haytham Ashraf  - 20246070 - G8
// Mahmoud Shalaby - 20246102 - G8

#include <iostream>
// #include <iomanip>
#include <cstring>
#include "Status.h"
#include "Order.h"

using namespace std;

// default number of items
#define DEF_ITEMS_COUNT (10)

int Order::totalOrders_ = 0;




Order::Order()
{
    ++totalOrders_;

    orderId_ = "";
    customer_ = NULL;
    driver_ = NULL;

    // dynamic array
    capacity_ = 0;
    itemCount_ = DEF_ITEMS_COUNT;
    items_ = new FoodItem[DEF_ITEMS_COUNT];

    // status
    status_ = OrderStatus::PENDING;
}

Order::Order(int orderId, Customer* cus)
{
    ++totalOrders_;

    // convert to string
    orderId_ = to_string(orderId);

    customer_ = cus;
    driver_ = NULL;

    // dynamic array
    capacity_ = 0;
    itemCount_ = DEF_ITEMS_COUNT;
    items_ = new FoodItem[DEF_ITEMS_COUNT];

    // status
    status_ = OrderStatus::PENDING;
}

Order::Order(const Order& order)
{
    ++totalOrders_;

    orderId_ = order.orderId_;

    // associations
    customer_ = order.customer_;
    driver_ = order.driver_;

    // food info
    itemCount_ = order.itemCount_;
    items_ = new FoodItem[itemCount_];
    
    for(int i = 0 ;i < itemCount_; i++)
        items_[i] = order.items_[i];

    capacity_ = order.capacity_;

    // order status
    status_ = order.status_;
}

Order::~Order()
{
    --totalOrders_;

    // if(customer_)
    //     delete customer_;

    // if(driver_)
    //     delete driver_;

    if(items_) {
        // for(int i = 0; i < itemCount_; i++)
        delete[] items_;
        items_ = NULL;
    }
}

OrderStatus Order::getStatus()
{
	return status_;
}

void Order::addItem(const FoodItem& item)
{
    *this += item;
}

void Order::assignDriver(DliveryDriver* driver)
{
    driver_ = driver;
}

// update order status. And if status is 'OrderStatus::DELIVERD'-
// call drivers's completeDlivery(), and add loyality points to customer.
void Order::updateStatus(OrderStatus status) 
{
    status_ = status;
	if(status == OrderStatus::DELIVERED) {
		
		double orderValues = calculateTotal();
		driver_->completeDlivery(orderValues);
	}
}

// return sum of all items
double Order::calculateTotal() const
{
    // calculate all prices in items_

    double total = 0;

    for(int i = 0; i < capacity_; i++)
        total += items_[i].calculateItemTotal();

    return total;
}

// display complete orders details
void Order::displayOrder()
{
    cout << "ID: " << orderId_ << endl;
    cout << "Capacity: " << capacity_ << endl;
    cout << "Order Status: " << orderStatusName(status_) << endl;
}

int Order::getTotalOrders()
{
    return Order::totalOrders_;
}

string Order::getOrderId()
{
    return orderId_;
}

Customer* Order::getCustomer()
{
    return customer_;
}

DliveryDriver* Order::getDriver()
{
    return driver_;
}

int Order::getItemCount()
{
    return capacity_;
}

// add food item
void Order::operator+=(const FoodItem& item)
{
    if(capacity_ == itemCount_)
        resize_(DEF_ITEMS_COUNT);

    items_[capacity_].setItemName(item.getItemName());
    items_[capacity_].setPrice(item.getPrice());
    items_[capacity_].setQuantity(item.getQuantity());
    capacity_++;
}

// combine two orders into one order, adds order to *this
Order& Order::operator+ (const Order& order)
{
    if(capacity_ + order.capacity_ >= itemCount_)
        resize_(capacity_ + order.capacity_ - itemCount_);

    int index = 0;

    while(index < order.capacity_) {

        items_[capacity_ + index].setItemName(order.items_[index].getItemName());
        items_[capacity_ + index].setPrice(order.items_[index].getPrice());
        items_[capacity_ + index].setQuantity(order.items_[index].getQuantity());
        index++;
    }

    return *this;
}

// print order details, "What Details?"
ostream& operator<<(ostream& os, const Order& order)
{

    // following the same order as in OrderDetails
    os << "ID: " << stoi(order.orderId_);		//  4 + sizeof(int)
    os << ", Status: " << (int)order.status_;	// 10 + sizeof(int)
    // os << ", Items: " << order.itemCount_;		//  9 + sizeof(int)
    os << ", Capacity: " << order.capacity_;   	// 12 + sizeof(int)
	os << "\n";
    
	// total size: sizeof(OrderDetails) + 35
	
    return os;
}

// comparison, based on total price
bool operator> (const Order& o1, const Order& o2)
{
    return o1.calculateTotal() > o2.calculateTotal();
}

// retrive foot item by index
FoodItem& Order::operator[](int index)
{
    return items_[index];
}

void Order::resize_(int moreSize) {

    // resize, by DEF_ITEMS_COUNT
    FoodItem* temp = new FoodItem[moreSize + itemCount_];

    // copy old content to this new place
    memcpy(temp, items_, sizeof(FoodItem) * itemCount_);

    // update size
    itemCount_ += moreSize;

    delete[] items_;
    items_ = temp;
}