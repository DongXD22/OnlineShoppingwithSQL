#pragma once

#include<string>
#include<vector>
#include<memory>
#include"Product.h"
using namespace std;
class Order{
private:
    int OrderID=0;
    string OrderStatus="Pending";
    string TimeStamp;
    vector<pair<shared_ptr<Product>,int>> PurchasedList;
    double TotalPrice;
public:    
    Order(string time, double prc, vector<pair <shared_ptr< Product>, int >> pcslist);
    void setID(int id);
    void setOrderStatus(string stt);

    int getOrderID()const;
    string getStatus()const;
    double getTotalPrice()const;
    vector<pair<shared_ptr<Product>, int>> getPurchasedList()const;
};