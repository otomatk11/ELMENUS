

#include <iostream>
#include "User.h"

using namespace std;

int User::totalUsers_ = 0;

User::User()
{
    userid_ = "";
    name_ = "";
    phonenumber_ = "";
	
	totalUsers_++;
}

User::User(string id, string n, string p)
{
    userid_ = id;
    name_ = n;
    phonenumber_ = p;
	
	totalUsers_++;
}

User::~User()
{
	totalUsers_--;
}

int User::getTotalUsers()
{
    return totalUsers_;
}

string User::getUserID()
{
    return userid_;
}

string User::getName()
{
    return name_;
}

string User::getPhoneNumber()
{
    return phonenumber_;
}