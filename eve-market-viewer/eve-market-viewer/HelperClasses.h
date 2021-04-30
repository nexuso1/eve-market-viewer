#include<string>
#include<utility>
#include<iostream>
#include<cpprest/json.h>


class Orders
{
public:
	Orders(std::ostream& out,std::shared_ptr<web::json::value> buy_order_json, std::shared_ptr<web::json::value> sell_order_json);
	void sort();
	void print();

private:
	std::ostream& out_;
	std::shared_ptr<web::json::value> buy_orders_json_;
	std::shared_ptr<web::json::value> sell_orders_json_;
};

