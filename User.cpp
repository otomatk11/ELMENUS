#include "User.h"

int User::totalUsers=0;

User::User()
{
    userid= " ";
    name= " ";
    phonenumber= " ";
}

User::User(string id, string n, string p)
{
    userid= id;
    name= n;
    phonenumber= p;
}
void User::displayinfo()
{
    cout<< userid << endl;
    cout<< name << endl;
    cout<< phonenumber << endl;
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
User::~User()
{
    
}