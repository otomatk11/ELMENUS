#ifndef User_H
#define User_H
class User
{
  protected:
    string userid;
    string name;
    string phonenumber;
    static int totalUsers;
  public:
    User();
    User(string id, string n, string p);
    virtual void displayinfo();
    virtual double calculateEarnings();
    static int getTotalUsers();
    string getUserID();
    string getName();
    string getPhoneNumber();
    virtual ~User();
};

#endif