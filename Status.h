


#ifndef _ORDER_STATUS_H_
#define _ORDER_STATUS_H_

#include <string>

enum class OrderStatus {
    PENDING,
    PREPARING,
    OUT_OF_DELIVERY,
    DELIVERED,
    CANCELLED
};

enum class UserType {
    Customer,
    Driver
};


std::string orderStatusName(OrderStatus st);
std::string userTypeName(UserType ut);

#endif // _ORDER_STATUS_H_