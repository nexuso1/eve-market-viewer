#include "HelperClasses.h"

Orders::Orders(std::ostream& out, std::shared_ptr<web::json::value> buy_order_json, std::shared_ptr<web::json::value> sell_order_json)
	: out_(out), buy_orders_json_(buy_order_json), sell_orders_json_(sell_order_json) {
	sort();
}