

#ifndef _USER_H_
#define _USER_H_

#include <string>
#include "Status.h"


class User
{
protected:

    std::string userid_;
    std::string name_;
    std::string phonenumber_;

    UserType userType_;

    // total users created by constructors
    static int totalUsers_;
public:

    User();
    User(std::string id, std::string n, std::string p);
    virtual ~User();

    virtual void displayInfo()=0;
    virtual double calculateEarnings() = 0;

    static int getTotalUsers();
    std::string getUserID();
    std::string getName();
    std::string getPhoneNumber();

    // EXTRA
    UserType getType();
    // bool checkType(UserType type);
};

#endif // _USER_H_