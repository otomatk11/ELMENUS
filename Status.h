//
//
// Author: Haytham Ashraf

#ifndef _ORDER_STATUS_H_
#define _ORDER_STATUS_H_

#include <string>

enum class OrderStatus {
    NONE = 0,
    PENDING,
    PREPARING,
    OUT_OF_DLIVERY,
    DELIVERED,
    CANCELLED
};

enum class UserType {
    CUSTOMER,
    DRIVER
};


std::string OrderStatusName(OrderStatus st);
std::string UserTypeName(UserType ut);

#endif // _ORDER_STATUS_H_