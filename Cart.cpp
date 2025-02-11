#include"Cart.h"
#include<iostream>
#include<cstdlib>
#include<chrono>
using namespace std;

void Cart::addProduct(shared_ptr<Product> prd, int num) {
    if(num<=0||num>prd->getStock()){
        throw "Invalid number!";
    }
    ProductList.push_back({prd,num});
}

void Cart::ShowSelectedProduct()const{
    if(ProductList.size()==0){
        cout<<"Empty!"<<endl;
        return;
    }
    for(int i=1;i<=ProductList.size();i++){
        cout<<i<<" : "<<(ProductList[i-1].first)->getName()<<" : "
        <<ProductList[i-1].second<<endl;
    }
    cout << "Total amount :" << this->getTotalAmount() << endl;
}

void Cart::setQuantity(int od,int num){
    int l=ProductList.size();
    if(od>l||od<1||num<=0||num>ProductList[od-1].first->getStock()){
        throw "Invalid number!";
    }
    ProductList[od-1].second=num;
}

void Cart::removeProduct(int od){
    int l=ProductList.size();
    if(od>l||od<=0){
        throw "Invalid number!";
    }
    ProductList.erase(ProductList.begin() + od - 1);
}

void Cart::clearCart(){
    int l=ProductList.size();
    while(l--){
        this->removeProduct(1);
    }
}

double Cart::getTotalAmount()const{
    double ans=0;
    for(int i=0;i<ProductList.size();i++){
        ans+=ProductList[i].second*ProductList[i].first->getPrice();
    }
    return ans;
}

void Cart::checkout(Database& db,shared_ptr<User> user){
    auto now=chrono::system_clock::now();
    string t=to_string(chrono::duration_cast<chrono::seconds>(now.time_since_epoch()).count());
    double all=this->getTotalAmount();
    shared_ptr<Order> ord = make_shared<Order>(t, all, ProductList);
    db.insertOrder(ord, *user);

    for(int i=0;i<ProductList.size();i++){
        shared_ptr<Product> prd=ProductList[i].first;
        prd->setStock(prd->getStock()-ProductList[i].second);
        db.insertProduct(prd);
    }
    this->clearCart();
}

