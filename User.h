//
//
// Author: Mahmoud Shalaby

#ifndef _USER_H_
#define _USER_H_

#include <string>
#include "Status.h"


class User
{
protected:

    std::string userid;
    std::string name;
    std::string phonenumber;

    UserType userType;

    // total users created by constructors
    static int totalUsers;
public:

    User();
    User(std::string id, std::string n, std::string p);
    virtual ~User();

    virtual void displayInfo();
    virtual double calculateEarnings() = 0;

    static int getTotalUsers();
    std::string getUserID();
    std::string getName();
    std::string getPhoneNumber();
};

#endif // _USER_H_