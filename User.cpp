//
//
// Author: Mahmoud Shalaby

#include <iostream>
#include "User.h"

using namespace std;

int User::totalUsers=0;

User::User()
{
    userid = "";
    name = "";
    phonenumber = "";
}

User::User(string id, string n, string p)
{
    userid = id;
    name = n;
    phonenumber = p;
}

User::~User()
{ 
}

void User::displayInfo()
{
    cout << userid << endl;
    cout << name << endl;
    cout << phonenumber << endl;
    cout << UserTypeName(userType) << endl;
}

int User::getTotalUsers()
{
    return totalUsers;
}

string User::getUserID()
{
    return userid;
}

string User::getName()
{
    return name;
}

string User::getPhoneNumber()
{
    return phonenumber;
}