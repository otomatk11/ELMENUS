class FoodItem
{
  private:
    string itemname;
    double price;
    int quantity;
  public:
    FoodItem();

    FoodItem(string name, double p, int q);

    void setname(string name);

    void setprice(double p);

    void setquantity(int q);
    
    string getItemName();
    
    double getprice();

    int getquantity();  

    double calculateItemTotal()
    
    void displayItem();
        
};