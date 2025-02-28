#include "User.h"
#include <iostream>
#include <memory>
using namespace std;

User::User(string name,string psw,string mail,double blc)
    :UserName(name),Password(psw),Email(mail),balance(blc){}

void User::setID(int userid){
    UserID = userid;
}
void User::setUserName(string name){
    if (name.find_first_not_of(" ") == string::npos) { 
        throw "Invalid Name!"; 
    }
    UserName=name;
}
void User::setPassword(string psw,string Newpsw){
	try{
		if (psw != Password) {
			throw "Wrong Password!";
		}
		Password = Newpsw;
	}
	catch (const char* msg) {
		cerr << msg << endl;
	}
}

void User::setEmail(string email){
    Email = email;
}

void User::setbalance(double blc){
	try{
		if (blc <= 0) {
			throw "Invalid Number!";
		}
		balance = blc;
	}
	catch (const char* msg) {
		cerr << msg << endl;
	}
}

int User::getUserID()const{return UserID;}
string User::getUserName()const{return UserName;}
string User::getPassword()const{return Password;}
string User::getEmail()const{return Email;}
double User::getbalance()const{return balance;}

void User::ChangeUserName(){
    string username;
    cout << "\nEnter your new name:";
    cin >> username;
    this->setUserName(username);
}

void User::ChangeEamil() {
	string email;
	cout << "\nEnter your new Email:";
	cin >> email;
	this->setEmail(email);
}

void User::ChangePassword() {
	string psw, newpsw;
	cout << "\nEnter your old password:";
	cin >> psw;
	cout << "\nEnter your new password:";
	cin >> newpsw;
	this->setPassword(psw, newpsw);
}

void User::ChangeBalance() {
	double blc;
	cout << "\nEnter your balance:";
	cin >> blc;
	this->setbalance(blc);
}

void User::ChangeUserInfo(Database& db) {
	while (true) {
		int ix = 0;
		this->ShowInfo();
		ShowMenu("User_InfoMenu");
		getInputandClear(ix);
		if (ix == 1) {
			this->ChangeUserName();
		}
		else if (ix == 2) {
			this->ChangeEamil();
		}
		else if (ix == 3) {
			this->ChangePassword();
		}
		else if (ix == 4) {
			this->ChangeBalance();
		}
		else {
			db.insertUser(make_shared<User>(*this));
			break;
		}
	}
}

void User::ShowInfo() const{
	cout << "\nUserID: " << UserID << endl;
	cout << "Name: " << UserName << endl;
	cout << "Email: " << Email << endl;
	cout << "Balance: " << balance << endl;
}


