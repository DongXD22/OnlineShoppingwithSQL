#pragma once
#include"Cart.h"
#include"Database.h"
#include"Order.h"
#include"Product.h"
#include"User.h"
#include"utils.h"
#include<iostream>
#include<exception>
using namespace std;

int main() {
	try {
		Database db("tcp://127.0.0.1:3306", "root", "root", "shopdb");
		if (!db.connect()) {
			cout << "Unable to connect!" << endl;
		}
		while (true) {
			int x = 0;
			ShowMenu("MainMenu");
			getInputandClear(x);
			if (x == 1 || x == 2) {		//User
				shared_ptr<User> user;
				shared_ptr<Cart> cart = make_shared<Cart>();
				if (x == 1) {	//Register
					user = RegisterUser(db);
				}
				else {		//Login
					user = Login(db);
				}
				while (true) {
					int ux = 0;
					ShowMenu("UserMenu");	
					getInputandClear(ux);
					if (ux == 1) {	
						Shopping(db, user, cart);
					}
					else if (ux == 2) {	
						cart->ShowSelectedProduct();
					}
					else if (ux == 3) {	
						cart->checkout(db, user);
					}
					else if (ux == 4) {	
						db.exportBrowsingHistory(*user);
					}
					else if (ux == 5) {	
						PayOrder(db, user);
					}
					else if (ux == 6) {	
						user->ChangeUserInfo(db);
					}
					else break;
				}
			}
			else if (x == 3) {
				Admin(db);
			}
			else break;
		}
	}
	catch (const std::exception& e) {
		cerr << string(e.what()) << endl;
	}
	catch (const sql::SQLException& e) {
		cerr << string(e.what()) << endl;
	}
	catch (const string& e) {
		cerr << e << endl;
	}
	catch (...) {
		cerr << "UKE ERROR" << endl;
	}
}