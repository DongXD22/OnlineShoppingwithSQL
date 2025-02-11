#pragma once

#include<string>
#include<vector>
#include<memory>
#include"User.h"
#include"Product.h"
#include"Order.h"
#include"Database.h"

using namespace std;

class Cart{
private:
    vector<pair<shared_ptr<Product>, int>> ProductList = {};
public:
    void addProduct(shared_ptr<Product> prd,int num);
    void ShowSelectedProduct()const;
    void setQuantity(int od,int num);
    void removeProduct(int od);
    void clearCart();
    double getTotalAmount()const;
    void checkout(Database& db,shared_ptr<User> user);
};

