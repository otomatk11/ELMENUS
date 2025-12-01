//
//
// Author: Haytham Ashraf

#include "Status.h"

using namespace std;

string OrderStatusName(OrderStatus st) {
    
    switch(st) {
        case OrderStatus::NONE: return "None";
        case OrderStatus::PENDING: return "Pending";
        case OrderStatus::PREPARING: return "Preparing";
        case OrderStatus::OUT_OF_DLIVERY: return "Out_of_dlivery";
        case OrderStatus::DELIVERED: return "Delivered";
        case OrderStatus::CANCELLED: return "Cancelled";
    }
    return "Unknown Status";
}

string UserTypeName(UserType ut) {
    
    switch(ut) {
        case UserType::CUSTOMER: return "Customer";
        case UserType::DRIVER: return "Driver";
    }
    return "Unknown";
}