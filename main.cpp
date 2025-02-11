#include"Cart.h"
#include"Database.h"
#include"Order.h"
#include"Product.h"
#include"User.h"
#include"utils.h"
#include"Order.h"
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
			cin >> x;
			if (x == 1 || x == 2) {		//User
				shared_ptr<User> user;
				shared_ptr<Cart> cart = make_shared<Cart>();
				if (x == 1) {	//Register
					user = Register(db);
				}
				else {		//Login
					user = Login(db);
				}
				while (true) {
					int ux = 0;
					ShowMenu("UserMenu");	//"1.View products\n""2.Show Cart""3.Checkout""4.Shopping history\n""5.Order history\n""6.Change information\n"
					cin >> ux;
					if (ux == 1) {	//View product
						Shopping(db, user, cart);
					}
					else if (ux == 2) {	//Show Cart
						cart->ShowSelectedProduct();
					}
					else if (ux == 3) {	//Checkout
						cart->checkout(db, user);
					}
					else if (ux == 4) {	//Shopping history
						db.exportBrowsingHistory(*user);
					}
					else if (ux == 5) {	//Order history
						PayOrder(db, user);
					}
					else if (ux == 6) {	//Change information
						ChangeUserInfo(db, user);
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