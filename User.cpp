#include "User.h"
#include <iostream>
using namespace std;
User::User(string name,string psw,string mail,double blc)
    :UserName(name),Password(psw),Email(mail),balance(blc){}

void User::setID(int userid){
    UserID = userid;
}
void User::setUserName(string name){
    if (name.find_first_not_of(" ") == string::npos) { // 检查是否为空白字符串
        throw "Invalid Name!"; 
    }
    UserName=name;
}
void User::setPassword(string psw,string Newpsw){
    if(psw!=Password){
        throw "Wrong Password!";
    }
    Password=Newpsw;
}
void User::setEmail(string email){
    Email = email;
}
void User::setbalance(double blc){
    if(blc<=0){
        throw "Invalid Number!";
    }
    balance=blc;
}

int User::getUserID()const{return UserID;}
string User::getUserName()const{return UserName;}
string User::getPassword()const{return Password;}
string User::getEmail()const{return Email;}
double User::getbalance()const{return balance;}

void User::ShowInfo() const{
	cout << "\nUserID: " << UserID << endl;
	cout << "Name: " << UserName << endl;
	cout << "Email: " << Email << endl;
	cout << "Balance: " << balance << endl;
}


