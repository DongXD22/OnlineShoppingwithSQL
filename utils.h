#pragma
#include"Product.h"
#include"User.h"
#include"Database.h"
#include"Cart.h"
#include<iostream>
#include<map>
using namespace std;

void ShowMenu(string menu);

shared_ptr<User> Register(Database& db);
shared_ptr<User> Login(Database& db);
void ChangeUserName(shared_ptr<User> user);
void ChangeEamil(shared_ptr<User> user);
void ChangePassword(shared_ptr<User> user);
void ChangeBalance(shared_ptr<User> user);
void ChangeUserInfo(Database& db, shared_ptr<User> user);

void Shopping(Database& db, shared_ptr<User> user,shared_ptr<Cart> cart);

void Payment(Database& db, shared_ptr<User> user, shared_ptr<Order> ord);
void PayOrder(Database& db, shared_ptr<User> user);

void Admin(Database& db);
void CreateProduct(Database& db);


