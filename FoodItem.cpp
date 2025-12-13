//
//
//
// Haytham Ashraf  - 20246070 - G8
// Mahmoud Shalaby - 20246102 - G8

#include <iostream>
#include "FoodItem.h"

using namespace std;

FoodItem::FoodItem()
{
    itemName_ = "";
    price_ = 0;
    quantity_ = 0;
}

FoodItem::FoodItem(string name, double p, int q)
{
    setItemName(name);
    setPrice(p);
    setQuantity(q);
}

void FoodItem::setItemName(string name)
{
    itemName_ = name;
}

void FoodItem::setPrice(double p)
{
    price_ = p;
}

void FoodItem::setQuantity(int q)
{
    quantity_ = q;
}

string FoodItem::getItemName() const
{
    return itemName_;
}

double FoodItem::getPrice() const
{
    return price_;
}

int FoodItem::getQuantity() const
{
    return quantity_;
}

double FoodItem::calculateItemTotal() const
{
    return quantity_ * price_;
}

void FoodItem::displayItem()
{
    cout << itemName_ << " x" << quantity_ << " @" << price_ << " = " << calculateItemTotal() << endl;
}