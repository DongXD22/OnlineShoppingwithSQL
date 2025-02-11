#pragma once

#include"Product.h"
#include"Order.h"
#include"Database.h"
#include<memory>
#include<string>
#include<vector>
using namespace std;

class User{
protected:
    int UserID=0;
    int status=1;
    string UserName,Password,Email;
    double balance;
    vector<Product> ShoppingHistory;
    vector<Order> OrderHistory;
public:
    User(string name,string psw,
        string mail,double blc);
    void setID(int userid);
    void setUserName(string name);
    void setPassword(string psw,string Newpsw);
    void setEmail(string email);
    void setbalance(double blc);

    int getUserID()const;
    string getUserName()const;
    string getPassword()const;
    string getEmail()const;
    double getbalance()const;

    shared_ptr<User> Register(Database& db);
    shared_ptr<User> Login(Database& db);
    void ChangeUserName();
    void ChangeEamil();
    void ChangePassword();
    void ChangeBalance();
    void ChangeUserInfo(Database& db);

    void ShowInfo()const;
};
