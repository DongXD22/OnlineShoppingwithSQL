#pragma once
#include "utils.h"
#include <cstdlib>
#include <vector>
using namespace std;
const vector<string> MainMenu = {
	"Regist",
	"Login",
	"Admin",
	"Exit"
};


const vector<string> UserMenu = {
	"View products",
	"Show Cart",
	"Checkout",
	"Shopping history",
	"Order history",
	"Change information"
};

const vector<string> User_InfoMenu = {
	"Username",
	"Email",
	"Password",
	"Balance"
};

const vector<string> AdminMenu = {
	"View Users",
	"View Products",
	"View Orders",
	"Create Products",
};
	
const map<string, vector<string>> Menu = {
	{"MainMenu",MainMenu},
	{"UserMenu",UserMenu},
	{"User_InfoMenu",User_InfoMenu},
	{"AdminMenu",AdminMenu}
};

void clear_screen(){
#ifdef _WIN32
	system("cls");
#else
	system("clear");
#endif
}

void ShowMenu(string menu){
	auto it = Menu.find(menu);
	if (it != Menu.end()) {
		int cnt = 1;
		for (auto opt : it->second) {
			cout <<cnt<<". "<< opt << endl;
			cnt++;
		}
		cout << "Enter your option :";
	}
	else {
		cout << "Menu not found!" << endl; 
	}
}

shared_ptr<User> RegisterUser(Database& db){
	User user("","","",3);
	user.ChangeUserName();
	user.ChangeEamil();
	user.ChangePassword();
	user.ChangePassword();
	clear_screen();
	shared_ptr<User> _user=make_shared<User>(user);
	db.insertUser(_user);
	return _user;
}

shared_ptr<User> Login(Database& db){
	try{
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
		clear_screen();
		return user;
	}
	catch (const char* msg) {
		cerr << msg << endl;
	}
}


void Shopping(Database& db, shared_ptr<User> user,shared_ptr<Cart> cart){
	while (true) {
		int px = 0;
		db.exportProducts();
		cout << "\nEnter product id you want:";
		getInputandClear(px);
		if (px) {
			shared_ptr<Product> prd = make_shared<Product>(db.getProduct(px));
			prd->displayInfo();
			db.insertBrowsingHistory(*user, *prd);

			int amount;
			cout << "\nEnter the amount you need:";
			cin >> amount;
			if(amount){
				cart->addProduct(prd, amount);
			}
			clear_screen();
		}
		else break;
	}
}

void Payment(Database& db, shared_ptr<User> user, shared_ptr<Order> ord){
	try{
		if (ord->getStatus() != "Pending") {
			throw ord->getStatus();
		}
		if (user->getbalance() < ord->getTotalPrice()) {
			throw "Not enough balance!" ;
		}
		user->setbalance(user->getbalance() - ord->getTotalPrice());
		db.insertUser(user);
		ord->setOrderStatus("Completed");
		db.insertOrder(ord);
	}
	catch (const char* msg) {
		cerr << msg << endl;
	}
}

void PayOrder(Database& db, shared_ptr<User> user) {
	while (true) {
		int ox = 0;
		db.exportOrders(*user);
		cout << "\nEnter order id you want to pay:";
		getInputandClear(ox);
		if (ox) {
			shared_ptr<Order> ord = make_shared<Order>(db.getOrder(ox));
			Payment(db, user, ord);
		}
		else break;
	}
}

void Admin(Database& db){
	while(true){
		ShowMenu("AdminMenu");
		int ax = 0;
		getInputandClear(ax);
		if (ax == 1) {
			while(true){
				db.exportUsers();
				int dx;
				cout << "\nEnter UserID you want to delete:";
				getInputandClear(dx);
				if (dx) {
					db.deleteUser(dx);
				}
				else break;
			}
		}
		else if (ax == 2) {
			while(true){
				db.exportProducts();
				int dx;
				cout << "\nEnter ProductID you want to delete:";
				getInputandClear(dx);
				if (dx) {
					db.deleteProduct(dx);
				}
				else break;
			}
		}
		else if (ax == 3) {
			cout << "Error!" << endl;
		}
		else if (ax == 4) {
			CreateProduct(db);
		}
		else break;
	}

}

void CreateProduct(Database& db){
	string name, des;
	double price;
	int stock;
	shared_ptr<Product> prd = make_shared<Product>("", "", 0, 0);

	cout << "\nEnter productname:";
	cin >> name;
	prd->setName(name);

	cout << "\nEnter description for your product:";
	cin >> des;
	prd->setDescription(des);

	cout << "\nEnter price:";
	cin >> price;
	prd->setPrice(price);

	cout << "\nEnter stock:";
	cin >> stock;
	prd->setStock(stock);

	db.insertProduct(prd);
}

