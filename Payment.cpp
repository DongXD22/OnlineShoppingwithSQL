#include"Payment.h"
void PayOrder(Database& db,shared_ptr<User> user,shared_ptr<Order> ord){
    if (ord->getStatus() != "Pending") {
        throw ord->getStatus();
    }
    if(user->getbalance()<ord->getTotalPrice()){
        throw "Not enough balance!";
    }
    user->setbalance(user->getbalance()-ord->getTotalPrice());
    db.insertUser(user);
    ord->setOrderStatus("Completed");
    db.insertOrder(ord,*user);
}