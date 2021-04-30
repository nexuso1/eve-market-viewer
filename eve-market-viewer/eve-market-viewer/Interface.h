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


using namespace io::swagger::client::api;

class AssetStorage;
class CharacterStorage;
class MarketStorage;
class UniverseStorage;

class MainInterface
{
/// <summary>
/// The main API interface, provides acces to the various APIs, and their respective interfaces.
/// </summary>
public:
	MainInterface(std::ostream& out);
	void parse_command(std::stringstream& stream);

private:
	void list_orders_parser(std::stringstream& stream);
	void set_parser(std::stringstream& stream);
	void create_interfaces();
	void init();
	void setup_api_client();
	void setup_apis();

	friend class MarketStorage;

	std::ostream& out_;

	std::shared_ptr<ApiClient> api_client_;
	std::shared_ptr<ApiConfiguration> api_configuration_;
	std::unique_ptr<MarketApi> market_api_;
	std::unique_ptr<UniverseApi> universe_api_;
	std::unique_ptr<AssetsApi> asset_api_;
	std::unique_ptr<CharacterApi> character_api_;

	std::unique_ptr<UniverseStorage> universe_st_;
	std::unique_ptr<MarketStorage> market_st_;
	std::unique_ptr<AssetStorage> asset_st_;
	std::unique_ptr<CharacterStorage> character_st_;
};

class UniverseStorage {
public:
	UniverseStorage(std::unique_ptr<UniverseApi>& universe_api);
	long get_id_from_name(std::string& name, std::string& type);

private:
	std::unique_ptr<UniverseApi>& universe_api_;
};

class MarketStorage {
public:
	MarketStorage(std::unique_ptr<MarketApi>& market_api, MainInterface* main_interface);
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

	// Orders get_type_orders_region(const std::string& name, boost::optional<int> region_id, int page = 1);
	Orders get_type_orders_region(int item_id, boost::optional<int> region_id, int page);
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

class AssetStorage {
public:
	AssetStorage(std::unique_ptr<AssetsApi>& asset_api);

private:
	std::unique_ptr<AssetsApi>& asset_api_;
};


class CharacterStorage {
public:
	CharacterStorage(std::unique_ptr<CharacterApi>& character_api);

private:
	std::unique_ptr<CharacterApi>& character_api_;
};
