#include "Product.h"
#include <iostream>
using namespace std;
Product::Product(string name,string dsp,double prc,int stock)
        :ProductName(name),Description(dsp),Price(prc),Stock(stock){}

void Product::setID(const int& id){
    ProductID = id;
}

void Product::setName(const string& name){
    try{
        if (name.find_first_not_of(" ") == string::npos) {
            throw "Invalid Name!";
        }
        ProductName = name;
    }
    catch (const char* msg) {
        cerr << msg << endl;
    }
}

int Product::getProductID() const{
    return ProductID;
}

string Product::getName() const{
    return ProductName;
}

void Product::setDescription(const string& dsp){
    Description=dsp;
}

string Product::getDescription() const{
    return Description;
}

void Product::setPrice(const double& prc){
    try{
        if (prc <= 0) {
            throw "Wrong Price";
        }
        Price = prc;
    }
    catch (const char* msg) {
        cerr << msg << endl;
    }
}

double Product::getPrice() const{
    return Price;
}

void Product::setStock(const int& stk){
    try{
        if (stk < 0) {
            throw "Wrong Stock";
        }
        Stock = stk;
    }
    catch (const char* msg) {
        cerr << msg << endl;
    }
}

int Product::getStock() const{
    return Stock;
}

void Product::displayInfo() const{
    cout<<"Name:"<<ProductName<<endl;
    cout<<"Price:"<<Price<<endl;
    cout<<"Stock:"<<Stock<<endl;
    cout<<"Description:"<<Description<<endl;
}