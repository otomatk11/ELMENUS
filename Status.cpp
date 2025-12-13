//
//
//
// Haytham Ashraf  - 20246070 - G8
// Mahmoud Shalaby - 20246102 - G8


#include "Status.h"

using namespace std;


string orderStatusName(OrderStatus st) {
    
    switch(st) {
        case OrderStatus::PENDING: return "Pending";
        case OrderStatus::PREPARING: return "Preparing";
        case OrderStatus::OUT_OF_DELIVERY: return "Out_of_delivery";
        case OrderStatus::DELIVERED: return "Delivered";
        case OrderStatus::CANCELLED: return "Cancelled";
    }
    return "Unknown Status";
}

string userTypeName(UserType ut) {
    
    switch(ut) {
        case UserType::Customer: return "Customer";
        case UserType::Driver: return "Driver";
    }
    return "Unknown";
}