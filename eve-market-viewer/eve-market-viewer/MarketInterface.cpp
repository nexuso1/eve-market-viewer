#include "Interface.h"

using namespace io::swagger::client::api;
using namespace std;
using namespace utility::conversions;

MarketInterface::MarketInterface(std::unique_ptr<MarketApi>& market_api, MainInterface* main_interface) : market_api_(market_api), main_interface_(main_interface) {
	set_region();
	set_system();
	set_station();
};

void MarketInterface::parse_orders(vector<shared_ptr<web::json::value>>& orders, bool buy, int region_id, int item_id) {
	// Gets all of the orders for the given item in the region, and stores them in orders
	// ESI can only provide a specific page, so get pages until no more are available.
	// Pages are not sorted, so it will have to be storted later.

	int page_n = 1;
	string order_type = "sell";
	if (buy) {
		// Get the buy orders
		order_type = "buy";
	}

	while (true) {
		try {
			auto page = market_api_->getMarketsRegionIdOrders(to_string_t(order_type), region_id, {}, {}, page_n, item_id).get();
			for (int i = 0; i < page.size(); i++) {
				orders.push_back(make_shared<web::json::value>(page[i]->toJson()));
			}
		}
		catch (ApiException e) {
			// No more pages to get
			break;
		}
		page_n++;
	}
}

shared_ptr<Orders> MarketInterface::get_type_orders(int item_id, boost::optional<int> location_id, const id_type type) {
	// Gets the orders for item item_id in the station station_id
	// Only way to do this is to query orders from the whole region 
	// and remove the ones from 
	if (!location_id.is_initialized()) {
		// No region specified, so set to default
		switch (type) {
		case id_type::region:
			location_id = region_id_;
			break;
		case id_type::system:
			location_id = system_id_;
			break;
		case id_type::station:
			location_id = station_id_;
			break;
		case id_type::structure:
			throw(exception("No structure ID specified"));
			break;
		}
	}

	// Map for specific json fields, needed to compare the id of the 
	// corresponding field to location_id
	const unordered_map<id_type, string> fields{
		{ id_type::system, "system_id"},
		{ id_type::station, "location_id"},
		{ id_type::structure, "location_id"}
	};

	long region_id = main_interface_->universe_ifc_->get_region_id(location_id.get(), type);

	vector<shared_ptr<web::json::value>> sell_orders;
	vector<shared_ptr<web::json::value>> buy_orders;

	// Get orders from ESI
	parse_orders(sell_orders, false, region_id, item_id);
	parse_orders(buy_orders, true, region_id, item_id);

	if (type != id_type::region) {
		auto fields_it = fields.find(type);
		// If listing only some specific orders is required, remove the invalid ones
		for (int i = 0; i != sell_orders.size(); i++) {
			if (sell_orders[i]->at(to_string_t(fields_it->second)).as_integer() != location_id.get()) {
				// This genius way of erasing elements is due to Peter G. from Stack Overflow. 
				// Thanks a lot man.
				// Changes order, but they aren't sorted anyway.
				sell_orders[i] = sell_orders.back();
				sell_orders.pop_back();
			}
		}

		// Same for buy orders
		for (int i = 0; i < buy_orders.size(); i++) {
			int order_loc_id = buy_orders[i]->at(to_string_t(fields_it->second)).as_integer();
			if (order_loc_id != location_id.get()) {
				buy_orders[i] = buy_orders.back();
				buy_orders.pop_back();
			}
		}
	}

	return make_shared<Orders>(main_interface_->out_, buy_orders, sell_orders, *main_interface_);
}