#pragma
#include"Product.h"
#include"User.h"
#include"Order.h"
#include"Database.h"
#include<memory>
using namespace std;
void PayOrder(Database& db,shared_ptr<User> user,shared_ptr<Order> ord);