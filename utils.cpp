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
	"Shopping history"
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
	"View Users"
	"View Products"
	"View Orders"
	"Create Products"
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

shared_ptr<User> Register(Database& db){
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
	clear_screen();
	shared_ptr<User> user=make_shared<User>(username, password, email, balance);
	db.insertUser(user);
	return user;
}

shared_ptr<User> Login(Database& db){
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

void ChangeUserName(shared_ptr<User> user){
	string username;
	cout << "\nEnter your new name:";
	cin >> username;
	user->setUserName(username);
}

void ChangeEamil(shared_ptr<User> user){
	string email;
	cout << "\nEnter your new Email:";
	cin >> email;
	user->setEmail(email);
}

void ChangePassword(shared_ptr<User> user){
	string psw, newpsw;
	cout << "\nEnter your old password:";
	cin >> psw;
	cout << "\nEnter your new password:";
	cin >> newpsw;
	user->setPassword(psw, newpsw);
}

void ChangeBalance(shared_ptr<User> user){
	double blc;
	cout << "\nEnter your balance:";
	cin >> blc;
	user->setbalance(blc);
}

void ChangeUserInfo(Database& db, shared_ptr<User> user){
	while (true) {	//"1.Username\n""2.Email\n""3.Password\n""4.Balance\n"
		int ix = 0;
		ShowMenu("User_InfoMenu");
		user->ShowInfo();
		cout << "\nEnter the info you want to change:";
		getInputandClear(ix);
		if (ix == 1) {
			ChangeUserName(user);
		}
		else if (ix == 2) {
			ChangeEamil(user);
		}
		else if (ix == 3) {
			ChangePassword(user);
		}
		else if (ix == 4) {
			ChangeBalance(user);
		}
		else {
			db.insertUser(user);
			break;
		}
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
	db.insertOrder(ord);
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
		cout << "\nEnter what you want to to:";
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

