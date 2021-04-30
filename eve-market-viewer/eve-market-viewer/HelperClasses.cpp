#include "HelperClasses.h"

using namespace std;

inline bool compare_orders_price_ascending(std::shared_ptr<web::json::value>& order1, std::shared_ptr<web::json::value>& order2) {
	auto price1 = order1->at(to_string_t("price")).as_integer();
	auto price2 = order1->at(to_string_t("price")).as_integer();
	return (price1 < price2) ? true : false;
}

Orders::Orders(std::ostream& out, std::vector<std::shared_ptr<web::json::value>> buy_order_json, std::vector<std::shared_ptr<web::json::value>> sell_order_json)
	: out_(out), buy_orders_json_(buy_order_json), sell_orders_json_(sell_order_json) {
	sort();
}

void Orders::sort() {
	out_ << "Orders got sorted" << endl;
}

void Orders::sort(bool buy, string type) {

}

void Orders::print() {
	out_ << "Orders were printed" << endl;
}