#include "Interface.h"

using namespace io::swagger::client::api;
using namespace std;
using namespace utility::conversions;

MainInterface::MainInterface(std::ostream& out) : out_(out)
{
	init();
}

void MainInterface::setup_api_client() {
	// Initiliazes the api_client_, which is used as a parameter
	// for other APIs.
	utility::string_t base_URL = to_string_t("https://esi.evetech.net/latest/");

	api_configuration_ = make_shared<ApiConfiguration>(); // Has to be shared because of ApiClient functions
	api_configuration_->setBaseUrl(base_URL);
	api_configuration_->setUserAgent(to_string_t("User-Agent"));

	api_client_ = make_shared<ApiClient>(api_configuration_); // Has to be unique because of other API classes
	api_client_->setConfiguration(api_configuration_);
}

void MainInterface::init() {
	setup_api_client();
	setup_apis();
	create_interfaces();
}

void MainInterface::setup_apis() {
	asset_api_ = make_unique<AssetsApi>(api_client_);
	character_api_ = make_unique<CharacterApi>(api_client_);
	market_api_ = make_unique<MarketApi>(api_client_);
	universe_api_ = make_unique<UniverseApi>(api_client_);
}

void MainInterface::create_interfaces() {
	// Create the member interfaces
	market_st_ = make_unique<MarketStorage>(market_api_, this);
	universe_st_ = make_unique<UniverseStorage>(universe_api_);
	asset_st_ = make_unique<AssetStorage>(asset_api_);
	character_st_ = make_unique<CharacterStorage>(character_api_);
}

UniverseStorage::UniverseStorage(std::unique_ptr<UniverseApi>& universe_api) : universe_api_(universe_api) {};

MarketStorage::MarketStorage(std::unique_ptr<MarketApi>& market_api, MainInterface* main_interface) : market_api_(market_api) {
	set_region();
	set_system();
	set_station();
};

Orders MarketStorage::get_type_orders_region(int item_id, boost::optional<int> region_id, int page = 1) {
	// Returns an Orders instance consisting of orders of the items specified, page 1 by default, in the default reagion

	if (!region_id.is_initialized()) {
		// No region specified, so set to default
		region_id = region_id_;
	}

	// boost:optional arguments can be skipped by {} in C++11
	auto sell_orders = market_api_->getMarketsRegionIdOrders(to_string_t("sell"), region_id.get(), {}, {}, page, item_id);
	auto buy_orders = market_api_->getMarketsRegionIdOrders(to_string_t("buy"), region_id.get(), {}, {}, page, item_id);
	auto sell_ptr = make_shared<web::json::value>(sell_orders.get()[0]->toJson());
	auto buy_ptr = make_shared<web::json::value>(buy_orders.get()[0]->toJson());
	return Orders(main_interface_->out_, buy_ptr, sell_ptr);
}

void MarketStorage::print_type_orders(ostream& out, web::json::value& orders) {

}

shared_ptr<web::json::value> get_type_orders_region(const string& name, boost::optional<int> region_id, int page = 1) {
}

AssetStorage::AssetStorage(std::unique_ptr<AssetsApi>& asset_api) : asset_api_(asset_api) {};

CharacterStorage::CharacterStorage(std::unique_ptr<CharacterApi>& character_api) : character_api_(character_api) {};