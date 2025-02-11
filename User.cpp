#include "User.h"
#include "Database.h"
#include "utils.h"
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

void User::ChangeUserInfo(Database& db) {
	while (true) {	//"1.Username\n""2.Email\n""3.Password\n""4.Balance\n"
		int ix = 0;
		ShowMenu("User_InfoMenu");
		this->ShowInfo();
		cout << "\nEnter the info you want to change:";
		cin >> ix;
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
			User nuser = *this;
			shared_ptr<User> user = make_shared<User>(nuser);
			db.insertUser(user);
			break;
		}
	}
}

void User::ChangeUserName() {
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

shared_ptr<User> User::Login(Database& db) {
	string username;
	cout << "Please enter your username:";
	cin >> username;
	string password;
	cout << "\nPlease enter your password:";
	cin >> password;
	User nuser = db.getUser(username);
	if (nuser.getPassword() != password) {
		throw "Wrong password!";
	}
	shared_ptr<User> user = make_shared<User>(nuser);
	return user;
}

shared_ptr<User> User::Register(Database& db) {
	string username;
	cout << "Please enter your username:";
	cin >> username;
	string email;
	cout << "\nPlease enter your Email:";
	cin >> email;
	string password;
	cout << "\nPlease enter your password:";
	cin >> password;
	double balance;
	cout << "\nPlease enter your balance:";
	cin >> balance;
	if (balance < 0) {
		throw "Your balance can't below 0!";
	}
	shared_ptr<User> user = make_shared<User>(username, password, email, balance);
	db.insertUser(user);
	return user;
}

void User::ShowInfo() const{
	cout << "\nUserID: " << UserID << endl;
	cout << "Name: " << UserName << endl;
	cout << "Email: " << Email << endl;
	cout << "Balance: " << balance << endl;
}


