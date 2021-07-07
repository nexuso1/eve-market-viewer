#include "Interface.h"

using namespace io::swagger::client::api;
using namespace std;
using namespace utility::conversions;

bool compare_orders_price_ascending(std::shared_ptr<web::json::value>& order1, std::shared_ptr<web::json::value>& order2) {
	auto price1 = order1->at(to_string_t("price")).as_double();
	auto price2 = order2->at(to_string_t("price")).as_double();
	return (price1 < price2) ? true : false;
}

bool compare_orders_price_descending(std::shared_ptr<web::json::value>& order1, std::shared_ptr<web::json::value>& order2) {
	auto price1 = order1->at(to_string_t("price")).as_double();
	auto price2 = order2->at(to_string_t("price")).as_double();
	return (price1 > price2) ? true : false;
}

Orders::Orders(ostream& out, vector<shared_ptr<web::json::value>> buy_order_json,
	vector<shared_ptr<web::json::value>> sell_order_json,
	MainInterface& main_interface)
	: out_(out), buy_orders_json_(buy_order_json), sell_orders_json_(sell_order_json),
	main_interface_(main_interface) {
	sort();
}

void Orders::sort() {
	std::sort(buy_orders_json_.begin(), buy_orders_json_.end(), compare_orders_price_descending);
	std::sort(sell_orders_json_.begin(), sell_orders_json_.end(), compare_orders_price_ascending);
}

void Orders::sort(const utility::string_t& field, sort_type sort_t, field_type field_t) {
	FieldComparator cmp(field, field_t, sort_t);
	std::sort(sell_orders_json_.begin(), sell_orders_json_.end(), cmp);
	std::sort(buy_orders_json_.begin(), buy_orders_json_.end(), cmp);
}

void Orders::print(int width) {
	cout << endl;
	cout << "Sell Orders" << endl << endl;
	main_interface_.printer_->print_head(descriptions_, width);
	main_interface_.printer_->print_line(descriptions_, width);
	main_interface_.printer_->print_json_vector(sell_orders_json_, descriptions_, id_fields_);

	cout << endl;
	cout << "Buy Orders" << endl << endl;
	main_interface_.printer_->print_head(descriptions_, width);
	main_interface_.printer_->print_line(descriptions_, width);
	main_interface_.printer_->print_json_vector(buy_orders_json_, descriptions_, id_fields_);
}