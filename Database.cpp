#include"Database.h"
using namespace std;
Database::Database(const string& host, const string& name,
	const string& psw, const string& db)
	:host(host), username(name), password(psw), dbname(db) {}

sql::Connection* Database::connect() {
	try {
		sql::mysql::MySQL_Driver* driver = sql::mysql::get_mysql_driver_instance();

		sql::Connection* con = driver->connect(host, username, password);

		con->setSchema(dbname);

		return con; 
	}
	catch (sql::SQLException& e) {
		cerr << "SQLException: " << e.what() << endl;
		cerr << "MySQL error code: " << e.getErrorCode() << endl;
		cerr << "SQLState: " << e.getSQLState() << endl;
		throw runtime_error("Unable to connect: " + string(e.what()));
	}
}


void Database::insertUser(shared_ptr<User> user){
	try{
		sql::Connection* con = connect();
		sql::SQLString sql = "INSERT INTO User (UserID,UserName,Pwd,Email,Balance) "
			"VALUES (?,?,?,?,?) "
			"ON DUPLICATE KEY UPDATE "
			"UserName = VALUES(UserName), "
			"Pwd = VALUES(Pwd), "
			"Email = VALUES(Email), "
			"Balance = VALUES(Balance);";
		sql::PreparedStatement* pstmt = con->prepareStatement(sql);
		pstmt->setInt(1, user->getUserID());
		pstmt->setString(2, user->getUserName());
		pstmt->setString(3, user->getPassword());
		pstmt->setString(4, user->getEmail());
		pstmt->setDouble(5, user->getbalance());
		pstmt->executeUpdate();
		if (user->getUserID()==0){
			sql::PreparedStatement* stmt
				= con->prepareStatement("SELECT LAST_INSERT_ID()");
			sql::ResultSet* res = stmt->executeQuery();
			if (res->next()) {
				user->setID(res->getInt(1));
			}
			delete res;
			delete stmt;
		}
		delete pstmt;
		delete con;
	}
	catch (sql::SQLException& e) {
		cerr << "Error in insertUser: " << e.what() << endl;
	}
}

void Database::insertProduct(shared_ptr<Product> prd) {
	try {
		sql::Connection* con = connect();
		sql::SQLString sql = "INSERT INTO Product (ProductID, Name, Description, Price, Stock) "
			"VALUES (?, ?, ?, ?, ?) "
			"ON DUPLICATE KEY UPDATE "
			"Name = VALUES(Name), "
			"Description = VALUES(Description), "  
			"Price = VALUES(Price), "             
			"Stock = VALUES(Stock)";               
		
		sql::PreparedStatement* pstmt = con->prepareStatement(sql);
		pstmt->setInt(1, prd->getProductID());
		pstmt->setString(2, prd->getName());
		pstmt->setString(3, prd->getDescription());
		pstmt->setDouble(4, prd->getPrice());
		pstmt->setInt(5, prd->getStock());
		pstmt->executeUpdate();

		if (prd->getProductID() == 0) {
			sql::PreparedStatement* stmt
				= con->prepareStatement("SELECT LAST_INSERT_ID()");
			sql::ResultSet* res = stmt->executeQuery();
			if (res->next()) {
				prd->setID(res->getInt(1));
			}
			delete res;
			delete stmt;
		}

		delete pstmt;
		delete con;
	}
	catch (sql::SQLException& e) {
		cerr << "Error in insertProduct: " << e.what() << endl;
	}
}


void Database::insertOrder(shared_ptr<Order> ord){
	try {
		sql::Connection* con = connect();


		sql::SQLString sql = "INSERT INTO `Order` (OrderID, UserID, TotalAmount, Sta) "
			"VALUES (? ,?, ?, ?) "
			"ON DUPLICATE KEY UPDATE "
			"UserID = VALUES(UserID), "
			"TotalAmount = VALUES(TotalAmount), "
			"Sta = VALUES(Sta);";

		sql::PreparedStatement* pstmt = con->prepareStatement(sql);

		pstmt->setInt(1, ord->getOrderID());
		pstmt->setInt(2, ord->getUserID());
		pstmt->setDouble(3, ord->getTotalPrice());
		pstmt->setString(4, ord->getStatus());

		pstmt->executeUpdate(); 

		if (ord->getOrderID()==0){
			sql::PreparedStatement* stmt
				= con->prepareStatement("SELECT LAST_INSERT_ID()");
			sql::ResultSet* res = stmt->executeQuery();
			if (res->next()) {
				ord->setID(res->getInt(1));
			}
			delete stmt;
			delete res;
		}
		delete pstmt;
		delete con;
		if(ord->getOrderID() == 0){
			this->insertOrderItems(*ord);
		}
	}
	catch (sql::SQLException& e) {
		cerr << "Error in insertOrder: " << e.what() << endl;
	}
}

void Database::insertOrderItems(Order ord){
	try {
		sql::Connection* con = connect();
		vector<pair<shared_ptr<Product>, int>> prdlist = ord.getPurchasedList();
		for (const auto& product : prdlist) {
			sql::SQLString sql = "INSERT INTO OrderItems (OrderId,ProductID,Quantity,Price) "
						 "VALUES (?,?,?,?)";
			sql::PreparedStatement* pstmt = con->prepareStatement(sql);
			pstmt->setInt(1, ord.getOrderID());   
			pstmt->setInt(2, product.first->getProductID());  
			pstmt->setInt(3, product.second); 
			pstmt->setDouble(4, product.first->getPrice()); 
			pstmt->executeUpdate();
			delete pstmt;
		}
		delete con;
	}
	catch (sql::SQLException& e) {
		cerr << "Error on insertOrderItems: " << e.what() << endl;
	}
}

void Database::insertBrowsingHistory(User user, Product prd){
	try {
		sql::Connection* con = connect();

		sql::SQLString sql = "INSERT INTO BrowsingHistory (UserID, ProductID, BrowsedAt) "
			"VALUES (?, ?, NOW())";

		sql::PreparedStatement* pstmt = con->prepareStatement(sql);

		pstmt->setInt(1, user.getUserID()); 
		pstmt->setInt(2, prd.getProductID());

		pstmt->executeUpdate();  

		delete pstmt;
		delete con;
	}
	catch (sql::SQLException& e) {
		cerr << "Error on insertBrowsingHistory: " << e.what() << endl;
	}
}

void Database::exportUsers(){
	try {
		sql::Connection* con = connect();
		sql::SQLString sql = "SELECT * FROM User";
		sql::Statement* stmt = con->createStatement();
		sql::ResultSet* res = stmt->executeQuery(sql);

		cout << "Info of Users:" << endl;
		while (res->next()) {
			cout << "UserID: " << res->getInt("UserID") << ", "
				<< "UserName: " << res->getString("UserName").c_str() << ", "
				<< "Email: " << res->getString("Email").c_str() << ", "
				<< "Balance: " << res->getDouble("Balance") << endl;
		}

		delete res;
		delete stmt;
		delete con;
	}
	catch (sql::SQLException& e) {
		cerr << "Error on exportUsers: " << e.what() << endl;
	}
}

void Database::exportProducts(){
	try {
		sql::Connection* con = connect();
		sql::SQLString sql = "SELECT * FROM Product";
		sql::Statement* stmt = con->createStatement();
		sql::ResultSet* res = stmt->executeQuery(sql);
		cout << "Info of Products:" << endl;
		while (res->next()) {
			cout << "ProductID: " << res->getInt("ProductID") << ", "
				<< "Name: " << res->getString("Name").c_str() << ", "
				<< "Price: " << res->getDouble("Price") << ", "
				<< "Stock: " << res->getInt("Stock") << endl;
		}

		delete res;
		delete stmt;
		delete con;
	}
	catch (sql::SQLException& e) {
		cerr << "Error on exportProducts: " << e.what() << endl;
	}
}

void Database::exportOrders(User user){
	try {
		sql::Connection* con = connect();
		sql::SQLString sql = "SELECT * FROM `Order` WHERE UserID = ?";
		sql::PreparedStatement* pstmt = con->prepareStatement(sql);

		pstmt->setInt(1, user.getUserID());

		sql::ResultSet* res = pstmt->executeQuery();

		cout << "User: " << user.getUserName()<<" :Info" << endl;
		while (res->next()) {
			cout << "OrderID: " << res->getInt("OrderID") << ", "
				<< "TotalAmount: " << res->getDouble("TotalAmount") << ", "
				<< "Status: " << res->getString("Sta").c_str() << endl;
		}

		delete res;
		delete pstmt;
		delete con;
	}
	catch (sql::SQLException& e) {
		cerr << "Error on exportOrders: " << e.what() << endl;
	}
}

void Database::exportBrowsingHistory(User user){
	try {
        sql::Connection* con = connect();
        sql::SQLString sql = "SELECT pv.HistoryID, p.Name, p.Price, pv.BrowsedAt "
                     "FROM BrowsingHistory pv "
                     "JOIN Product p ON pv.ProductID = p.ProductID "
                     "WHERE pv.UserID = ?";
        sql::PreparedStatement* pstmt = con->prepareStatement(sql);
        
        pstmt->setInt(1, user.getUserID());
        
        sql::ResultSet* res = pstmt->executeQuery();

		cout << "User: " << user.getUserName() << "'sBrowsingHistory:" << endl;
        while (res->next()) {
				cout << "HistoryID: " << res->getInt("HistoryID") << ", "
					 << "ProductName: " << res->getString("Name").c_str() << ", "
					 << "Price: " << res->getDouble("Price") << ", "
					 << "BrowsedAtAt: " << res->getString("BrowsedAt").c_str() << endl;
        }
        
        delete res;
        delete pstmt;
        delete con;
    }
    catch (sql::SQLException& e) {
        cerr << "Error on exportBrowsingHistory: " << e.what() << endl;
    }
}

User Database::getUser(string username){
	try {
		sql::Connection* con = connect();
		sql::SQLString sql = "SELECT * FROM User WHERE UserName = ?";
		sql::PreparedStatement* pstmt = con->prepareStatement(sql);
		pstmt->setString(1, username);
		sql::ResultSet* res = pstmt->executeQuery();
		string email;
		string password;
		double balance;
		if (res->next()) {
			email = res->getString("Email").c_str();
			password = res->getString("Pwd").c_str();
			balance = res->getDouble("Balance");
			User ans(username, password, email, balance);
			ans.setID(res->getInt("UserID"));
			delete res;
			delete pstmt;
			delete con;
			return ans;
		}
	}
	catch (sql::SQLException& e) {
		cerr << "Error on getUser: " << e.what() << endl;
	}
}

Product Database::getProduct(int id) {
	try {
		unique_ptr<sql::Connection> con(connect());
		sql::SQLString sqlQuery = "SELECT * FROM Product WHERE ProductID = ?"; 
		unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement(sqlQuery));
		pstmt->setInt(1, id);  

		unique_ptr<sql::ResultSet> res(pstmt->executeQuery());  

		if (res->next()) {  
			string name = res->getString("Name").c_str();
			string description = res->getString("Description").c_str();
			double price = res->getDouble("Price");
			int stock = res->getInt("Stock");

			Product product(name, description, price, stock);
			product.setID(res->getInt("ProductID"));
			return product;
		}
		else {
			cerr << "Product Not Found" << endl;
			throw runtime_error("Product not found");
		}
	}
	catch (sql::SQLException& e) {
		cerr << "Error on getProduct: " << e.what() << endl;
	}
}


Order Database::getOrder(int id) {
	try {
		unique_ptr<sql::Connection> con(connect()); 

		sql::SQLString sqlOrder = "SELECT * FROM `Order` WHERE OrderID = ?";
		unique_ptr<sql::PreparedStatement> pstmtOrder(con->prepareStatement(sqlOrder));
		pstmtOrder->setInt(1, id); 

		unique_ptr<sql::ResultSet> resOrder(pstmtOrder->executeQuery()); 

		if (resOrder->next()) {
			
			int orderID = resOrder->getInt("OrderID");
			string orderStatus = resOrder->getString("Sta").c_str();
			string timestamp = resOrder->getString("CreatedAt").c_str();
			double totalPrice = resOrder->getDouble("TotalAmount");
			int userID = resOrder->getInt("UserID");

			sql::SQLString sqlItems = "SELECT * FROM OrderItems WHERE OrderID = ?";
			unique_ptr<sql::PreparedStatement> pstmtItems(con->prepareStatement(sqlItems));
			pstmtItems->setInt(1, id);  

			unique_ptr<sql::ResultSet> resItems(pstmtItems->executeQuery());  

			vector<pair<shared_ptr<Product>, int>> purchasedList; 
			while (resItems->next()) {
				int productID = resItems->getInt("ProductID");
				int quantity = resItems->getInt("Quantity");
				double price = resItems->getDouble("Price");

				Product productObj = getProduct(productID);
				shared_ptr<Product> product = make_shared<Product>(move(productObj));

				purchasedList.push_back({ product, quantity });  
			}
			Order order(timestamp, totalPrice, purchasedList,userID);
			order.setID(orderID);  
			order.setOrderStatus(orderStatus);  
			return order;
		}
		else {
			cerr << "Order Not Found" << endl;
			throw runtime_error("Order not found");
		}
	}
	catch (sql::SQLException& e) {
		cerr << "Error on getOrder: " << e.what() << endl;
	}
}

void Database::deleteUser(int id){
	try {
		sql::Connection* con = connect();
		sql::SQLString sql = "DELETE FROM BrowsingHistory WHERE UserID = ?";
		sql::PreparedStatement* pstmt = con->prepareStatement(sql);
		pstmt->setInt(1, id);
		pstmt->executeUpdate();

		sql = "DELETE FROM User WHERE UserID = ?";
		pstmt = con->prepareStatement(sql);
		pstmt->setInt(1, id);
		pstmt->executeUpdate();
		delete pstmt;
		delete con;
	}
	catch (sql::SQLException& e) {
		cerr << "Error on deleteUser: " << e.what() << endl;
	}
}
void Database::deleteProduct(int id) {
	try {
		sql::Connection* con = connect();
		sql::SQLString sql = "DELETE FROM OrderItems WHERE ProductID = ?";
		sql::PreparedStatement* pstmt = con->prepareStatement(sql);
		pstmt->setInt(1, id);
		pstmt->executeUpdate();

		sql= "DELETE FROM Product WHERE ProductID = ?";
		pstmt = con->prepareStatement(sql);
		pstmt->setInt(1, id);
		pstmt->executeUpdate();
		delete pstmt;
		delete con;
	}
	catch (sql::SQLException& e) {
		cerr << "Error on deleteProduct: " << e.what() << endl;
	}
}
void Database::deleteOrder(int id) {
	try {
		sql::Connection* con = connect();
		sql::SQLString sql = "DELETE FROM `Order` WHERE OrderID = ?";
		sql::PreparedStatement* pstmt = con->prepareStatement(sql);
		pstmt->setInt(1, id);
		pstmt->executeUpdate();
		delete pstmt;
		delete con;
	}
	catch (sql::SQLException& e) {
		cerr << "Error on deleteOrder: " << e.what() << endl;
	}
}



