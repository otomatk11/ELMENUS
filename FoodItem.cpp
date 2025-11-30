#include "FoodItem.h"
FoodItem::FoodItem()
    {
        itemname = " ";
        price =0;
        quantity =0;
    }
FoodIte::FoodItem(string name, double p, int q)
    {
        setname(name);
        setprice(p);
        setquantity(q);
    }
void Fooditem::setname(string name)
    {
        itemname= name;
    }
void FoodItem::setprice(double p)
    {
        price= p;
    }
void FoofItem::setquantity(int q)
    {
        quantity= q;
    }
string FoodItem::getItemName()
    {
        return itemname;
    }
double FoodItem::getprice()
    {
        return price;
    }
int FoodItem::getquantity()
    {
        return quantity;
    }
double FoodItem::calculateItemTotal()
    {
        return quantity*price;
    }
void FoodItem::displayItem()
    {
        cout << itemname<< " x" <<quantity<< " @"<< price<<" = "<< calculateItemTotal()<< endl;
    }