#include<string>
#include<utility>
#include<iostream>
#include<cpprest/json.h>

using namespace utility::conversions;

class Orders
{
public:
	enum sort_by { price, station, system, duration, };
	enum sort_type { ascending, descending };

	Orders(std::ostream& out,std::vector<std::shared_ptr<web::json::value>> buy_order_json, std::vector<std::shared_ptr<web::json::value>> sell_order_json);
	void sort();
	void sort(std::vector<std::shared_ptr<web::json::value>> orders, sort_type type, sort_by field);
	void print();

private:
	std::ostream& out_;
	std::vector<std::shared_ptr<web::json::value>> buy_orders_json_;
	std::vector<std::shared_ptr<web::json::value>> sell_orders_json_;
};

struct OrderCompare {
	
};
