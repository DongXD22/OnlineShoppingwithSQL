#pragma once

#include<string>

using namespace std;

class Product{
protected:
    int ProductID=0;
    string ProductName,Description;
    double Price;
    int Stock;
public:
    Product(string name,string dsp,double prc,int stock);

    void setID(const int& id);
    void setName(const string& name);
    void setDescription(const string& dsp);
    void setPrice(const double& prc);
    void setStock(const int& stk);

    int getProductID()const;
    string getName() const;
    string getDescription() const;
    double getPrice() const;
    int getStock() const;

    void displayInfo() const;
};

