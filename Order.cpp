#include"Order.h"
#include <iterator>
using namespace std;
Order::Order(string time, double prc,
    vector<pair<shared_ptr<Product>, int>> pcslist,int userid)
    : TimeStamp(time), TotalPrice(prc), UserID(userid){
    copy(pcslist.begin(), pcslist.end(), back_inserter(PurchasedList));
}

void Order::setID(int id){
    OrderID = id;
};

double Order::getTotalPrice()const{
    return TotalPrice;
}

vector<pair<shared_ptr<Product>, int>> Order::getPurchasedList() const{
    return PurchasedList;
}

void Order::setOrderStatus(string stt){
    OrderStatus=stt;
}

int Order::getOrderID() const{
    return OrderID;
}

int Order::getUserID() const
{
    return UserID;
}

string Order::getStatus() const{
    return OrderStatus;
}
