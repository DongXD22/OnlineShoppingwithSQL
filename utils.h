#pragma once

#include "User.h"
#include "Database.h"
#include "Cart.h"
#include "Order.h"
#include <iostream>
#include <map>
using namespace std;
class User;
class Cart;
void clear_screen();
void ShowMenu(string menu);

shared_ptr<User> RegisterUser(Database& db);
shared_ptr<User> Login(Database& db);

void Shopping(Database& db, shared_ptr<User> user, shared_ptr<Cart> cart);

void Payment(Database& db, shared_ptr<User> user, shared_ptr<Order> ord);
void PayOrder(Database& db, shared_ptr<User> user);

void Admin(Database& db);
void CreateProduct(Database& db);

template<typename T>
inline void getInputandClear(T& input) {
    cin >> input;
    clear_screen();
}
