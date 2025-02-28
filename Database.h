#pragma once

#ifdef __cplusplus

#include <string>
#include <cppconn/connection.h>
#include <cppconn/driver.h>
#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/prepared_statement.h>
#include <stdexcept>
#include <memory>
#include "User.h"
#include"Product.h"
#include "Order.h"

using namespace std;

class User;

class Database {
private:
	sql::SQLString host;
	sql::SQLString username;
	sql::SQLString password;
	sql::SQLString dbname;
public:
	Database(const string& host, const string& name,
		const string& psw, const string& db);
	sql::Connection* connect();

	void insertUser(shared_ptr<User> user);
	void insertProduct(shared_ptr<Product> prd);
	void insertOrder(shared_ptr<Order> ord);
	void insertOrderItems(Order ord);
	void insertBrowsingHistory(User user, Product prd);

	void exportUsers();
	void exportProducts();
	void exportOrders(User user);
	void exportBrowsingHistory(User user);

	User getUser(string username);
	Product getProduct(int id);
	Order getOrder(int id);

	void deleteUser(int id);
	void deleteProduct(int id);
	void deleteOrder(int id);
};
#endif