#ifndef Customer_h
#define Customer_h

class Customer : public User
{
    private:
        string deliveryAddress;
        int loyaltyPoints=0;
    public:
        Customer();
        Customer(string deliveryA, int loyaltyP);
        void displayinfo();
        double calculateEarnings();
        void setDeliveryAddress(string a);
        void setLoyaltyPoints(int p);
        string getDeliveryAddress();
        int getLoyaltyPoints();
        void operator+=(int o);
};

#endif