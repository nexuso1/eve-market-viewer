#include "cpprest-client/ApiClient.h"
#include "cpprest-client/ApiConfiguration.h"
#include "cpprest-client/api/CharacterApi.h"
#include "cpprest-client/api/MarketApi.h"
#include "cpprest-client/api/AssetsApi.h"
#include "cpprest-client/api/UniverseApi.h"
#include "HelperClasses.h"

#include <iostream>
#include <string>
#include <cpprest/json.h>
#include <cpprest/details/basic_types.h>
#include <unordered_set>
#include <unordered_map>

using namespace io::swagger::client::api;

class AssetInterface;
class CharacterInterface;
class MarketInterface;
class UniverseInterface;
class Orders;

class MainInterface
{
/// <summary>
/// The main API interface, provides acces to the various APIs, and their respective interfaces.
/// </summary>
public:
	MainInterface(std::ostream& out);
	void parse_command(std::stringstream& stream, std::string& line);
	void print_help();
	void print_json_vector(std::vector<std::shared_ptr<web::json::value>>& vec,
		const std::list<std::pair<std::string, std::string>>& descriptions,
		const std::unordered_set<std::string>& id_fields,
		int width = 20);
	void print_line(const std::list<std::pair<std::string, std::string>>& descriptions, int width);
	void print_head(const std::list<std::pair<std::string, std::string>>& descriptions, int width);
	bool is_id(const std::unordered_set<std::string>& id_fields, const std::string& key);
	std::shared_ptr<std::vector <std::string>> get_parameters(std::string& params); // Uses regex to parse command parameters

private:
	void list_orders_parser(std::string& line);
	void set_parser(std::stringstream& stream, std::string& line);
	void create_interfaces();
	void init();
	void setup_api_client();
	void setup_apis();

	friend class MarketInterface;

	std::ostream& out_;

	std::shared_ptr<ApiClient> api_client_;
	std::shared_ptr<ApiConfiguration> api_configuration_;
	std::unique_ptr<MarketApi> market_api_;
	std::unique_ptr<UniverseApi> universe_api_;
	std::unique_ptr<AssetsApi> asset_api_;
	std::unique_ptr<CharacterApi> character_api_;

	std::unique_ptr<UniverseInterface> universe_st_;
	std::unique_ptr<MarketInterface> market_st_;
	std::unique_ptr<AssetInterface> asset_st_;
	std::unique_ptr<CharacterInterface> character_st_;
};

class UniverseInterface {
public:
	UniverseInterface(std::unique_ptr<UniverseApi>& universe_api);
	long get_id_from_name(std::string& name, std::string& type);
	std::shared_ptr<std::string> get_name_from_id(long id);
	std::shared_ptr<ItemInfo> get_type_info(long type_id);

	std::unordered_map<long, std::string> id_to_name_cache_;
	std::unordered_map<std::string, long> name_to_id_cache_;

private:
	std::unique_ptr<UniverseApi>& universe_api_;
};

class MarketInterface {
public:
	MarketInterface(std::unique_ptr<MarketApi>& market_api, MainInterface* main_interface);
	
	inline void set_region(int region_id = 10000002) {
		// Default is The Forge
		region_id_ = region_id;
	};

	inline void set_system(int system_id = 30000142) {
		// Default is Jita
		system_id_ = system_id_;
	};

	inline void set_station(int station_id = 60003760) {
		// Default is Jita 4 Moon 4 Caldari Navy Assembly Plant
		station_id_ = station_id;
	};

	void parse_orders(std::vector<std::shared_ptr<web::json::value>>& orders, bool buy, int region_id, int item_id);

	// Orders get_type_orders_region(const std::string& name, boost::optional<int> region_id, int page = 1);
	Orders get_type_orders_region(int item_id, boost::optional<int> region_id);
	// web::json::value get_prices_by_category(int category_id, int page = 1);
	// web::json::value get_type_history(int item_id, int page = 1);
	// web::json::value get_type_history(const std::string& name);

private:
	std::unique_ptr<MarketApi>& market_api_; // Makes the web requests
	MainInterface* main_interface_;
	int region_id_; // Current region (default The Forge)
	int system_id_; // Current system (default Jita)
	int station_id_; // Current Station (default Jita 4 Moon 4 Caldari Navy Assembly Plant)
};

class AssetInterface {
public:
	AssetInterface(std::unique_ptr<AssetsApi>& asset_api);

private:
	std::unique_ptr<AssetsApi>& asset_api_;
};


class CharacterInterface {
public:
	CharacterInterface(std::unique_ptr<CharacterApi>& character_api);

private:
	std::unique_ptr<CharacterApi>& character_api_;
};


class Orders
{
public:
	enum class sort_by { price, station, system, duration, };
	enum class sort_type { ascending, descending };

	Orders(std::ostream& out, std::vector<std::shared_ptr<web::json::value>> buy_order_json,
		std::vector<std::shared_ptr<web::json::value>> sell_order_json,
		MainInterface& main_interface);
	void sort();
	void sort(std::vector<std::shared_ptr<web::json::value>>& orders, sort_type type, sort_by field);
	void print(int width = 20);

private:
	const std::list<std::pair<std::string, std::string>> descriptions_{
		{"duration" , "Duration"},
		{"price", "Price"},
		{"location_id", "Station"},
		{"volume_remain", "Vol. Remaining"},
		{"min_volume", "Min. Volume"},
		{"range", "Range"},
		{"system_id", "System"},
		{"issued", "Date Issued"}
	};

	const std::unordered_set<std::string> id_fields_{
		"location_id", "system_id"
	};

	std::ostream& out_;
	MainInterface& main_interface_;
	std::vector<std::shared_ptr<web::json::value>> buy_orders_json_;
	std::vector<std::shared_ptr<web::json::value>> sell_orders_json_;
};