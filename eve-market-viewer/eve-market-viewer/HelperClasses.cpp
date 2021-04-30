#include "HelperClasses.h"

using namespace std;

Orders::Orders(std::ostream& out, std::shared_ptr<web::json::value> buy_order_json, std::shared_ptr<web::json::value> sell_order_json)
	: out_(out), buy_orders_json_(buy_order_json), sell_orders_json_(sell_order_json) {
	sort();
}

void Orders::sort() {
	out_ << "Orders got sorted" << endl;
}

void Orders::print() {
	out_ << "Orders were printed" << endl;
}