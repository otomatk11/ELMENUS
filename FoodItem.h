

//
//
// Author: Mahmoud Shalaby

#ifndef _FOOD_ITEM_H_
#define _FOOD_ITEM_H_

#include <string>

class FoodItem
{
private:

    std::string itemName_;
    double price_;
    int quantity_;

public:

    FoodItem();
    FoodItem(std::string name, double p, int q);

    void setItemName(std::string name);
    void setPrice(double p);
    void setQuantity(int q);

    std::string getItemName() const;
    double getPrice() const;
    int getQuantity() const;

    double calculateItemTotal() const;
    void displayItem();
};

#endif // _FOOD_ITEM_H_