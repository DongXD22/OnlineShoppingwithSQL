#include"Order.h"
#include <iterator>
using namespace std;
Order::Order(string time, double prc,
    vector<pair<shared_ptr<Product>, int>> pcslist)
    : TimeStamp(time), TotalPrice(prc) {
    // 使用 back_inserter 确保动态插入元素
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

string Order::getStatus() const{
    return OrderStatus;
}
