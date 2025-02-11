#include "utils.h"
using namespace std;
const string MainMenu = 
"\n1.Regist\n"
"2.Login\n"
"3.Admin\n"
"4.Exit\n";
const string UserMenu =
"\n1.View products\n"
"2.Show Cart\n"
"3.Checkout\n"
"4.Shopping history\n"
"5.Order history\n"
"6.Change information\n"
;
const string User_InfoMenu = 
"\n1.Username\n"
"2.Email\n"
"3.Password\n"
"4.Balance\n"
;
const string AdminMenu = 
"\n1.View Users\n"
"2.View Products\n"
"3.View Orders\n"
"4.Create Products\n"
;

		
const map<string, string> Menu = {
	{"MainMenu",MainMenu},
	{"UserMenu",UserMenu},
	{"User_InfoMenu",User_InfoMenu},
	{"AdminMenu",AdminMenu}
};

void ShowMenu(string menu){
	auto it = Menu.find(menu);
	if (it != Menu.end()) {
		cout << it->second;
	}
	else {
		cout << "Menu not found!" << endl; // 如果没有找到菜单，输出提示信息
	}
}


void Shopping(Database& db, shared_ptr<User> user,shared_ptr<Cart> cart){
	while (true) {
		int px = 0;
		db.exportProducts();
		cout << "\nEnter product id you want:";
		cin >> px;
		if (px) {
			shared_ptr<Product> prd = make_shared<Product>(db.getProduct(px));
			cout << endl << prd->getDescription() << endl;
			db.insertBrowsingHistory(*user, *prd);

			int amount;
			cout << "\nEnter the amount you need:";
			cin >> amount;
			if(amount){
				cart->addProduct(prd, amount);
			}
		}
		else break;
	}
}

void Payment(Database& db, shared_ptr<User> user, shared_ptr<Order> ord){
	if (ord->getStatus() != "Pending") {
		cout << ord->getStatus() << endl;
		return;
	}
	if (user->getbalance() < ord->getTotalPrice()) {
		cout << "Not enough balance!" << endl;
		return;
	}
	user->setbalance(user->getbalance() - ord->getTotalPrice());
	db.insertUser(user);
	ord->setOrderStatus("Completed");
	db.insertOrder(ord, *user);
}

void PayOrder(Database& db, shared_ptr<User> user) {
	while (true) {
		int ox = 0;
		db.exportOrders(*user);
		cout << "\nEnter order id you want to pay:";
		cin >> ox;
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
		cout << "\nEnter what you want to to:";
		cin >> ax;
		if (ax == 1) {
			while(true){
				db.exportUsers();
				int dx;
				cout << "\nEnter UserID you want to delete:";
				cin >> dx;
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
				cin >> dx;
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

