#include "Interface.h"
#include<unordered_map>
#include<vector>
#include<regex>

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

void MainInterface::print_help() {

	const string help = "Usage:\n \
------------------------------------ -\n \
Best used in a large window. \n\
Name parameters are case insesitive. Can be substituted for IDs.\n \
A few sample paramters - Location - Jita, Amarr, Hek, Rens, Dodixie (Major Hub Systems)\n\
								  - The Forge, Heimatar, Domain, Genesis (Regions)\n\
					   - Items	  - Gila, Muninn, Astero, Tritanium, Void S, Tremor M, PLEX, Large Shield Booster II \n\
\
list [<location_type>] \"<type_name>\"[\"location_name>\"] - lists currently available market orders of <type_name> in <location_name>,\n \
														   if no region is provided, lists from the default one.\n \
														 - avaliable <location_typ> - system, station, region \
set <paramater> \"<name>\"				- sets the default <parameter> to <name>\n \
										-available parameters : -region\n \
										- station\n \
										- system\n \
\
--------------------------------------\n \
\
Defaults:\n \
-region - The Forge\n \
- system - Jita\n \
- station - Jita IV - Moon 4 - Caldari Navy Assembly Plant";
	out_ << help << endl;
}

void MainInterface::setup_apis() {
	// Sets up the various API classes for interacting
	// with ESI
	asset_api_ = make_unique<AssetsApi>(api_client_);
	character_api_ = make_unique<CharacterApi>(api_client_);
	market_api_ = make_unique<MarketApi>(api_client_);
	universe_api_ = make_unique<UniverseApi>(api_client_);
}

void MainInterface::create_interfaces() {
	// Create the member interfaces
	market_ifc = make_unique<MarketInterface>(market_api_, this);
	universe_ifc = make_unique<UniverseInterface>(universe_api_);
	asset_ifc = make_unique<AssetInterface>(asset_api_);
	asset_ifc = make_unique<CharacterInterface>(character_api_);
}

void MainInterface::parse_command(stringstream& stream, string& line) {
	// Resolves the first token of the command, then calls the corresponding
	// function
	string first;
	stream >> first;
	if (first == "list") {
		list_orders_parser(stream, line);
	}
	else if (first == "set") {
		set_parser(stream, line);
	}

	else if (first == "help") {
		print_help();
	}

	else {
		out_ << ">Invalid argument. See \"help\" for usage." << endl;
	}
}

shared_ptr<vector<string>> MainInterface::get_parameters(string& params) {
	// Matches the arguments inside parentheses in the params.
	// Returns a shared_ptr to the vector of matches.
	const regex param_regex("[\"\']([\\w\\s]+)[\"\']"); // Inside parentheses
	vector<string> res;
	smatch matches;
	string::const_iterator search_start = params.cbegin();
	while (regex_search(search_start, params.cend(), matches, param_regex)) {
		// Has to find all matches, so continues where it left off after
		// the last match

		res.push_back(matches[1]);
		search_start = matches.suffix().first;
	}
	
	return make_shared<vector<string>>(res);
}

void MainInterface::set_parser(stringstream& stream, string& line) {
	// set type command parser
	string type;
	stream >> type;
	string name = (*get_parameters(line))[0];

	// Corresponds to various set functions
	const unordered_map<string, string> param_types{
		{"region" ,"regions" },
		{"station", "stations"},
		{"system", "systems"}
	};

	auto it = param_types.find(type);
	if (it != param_types.end()) {
		// Valid command
		int id;
		string key_type = it->second;
		try {
			// Resolve name to ID
			id = universe_ifc->get_id_from_name(name, key_type);
		}
		catch (ApiException e) {
			out_ << e.what() << endl;
			return;
		}
		catch (web::json::json_exception e) {
			out_ << e.what() << endl;;
			return;
		}
		
		// Call a function based on token,
		// .compare has inverted logic
		if (!it->first.compare("region")) {
			market_ifc->set_region(id);
			out_ << ">Region set." << endl;
		}
		else if (!it->first.compare("station")) {
			market_ifc->set_station(id);
			out_ << ">Station set." << endl;
		}
		else if (!it->first.compare("system")) {
			market_ifc->set_system(id);
			out_ << ">System set." << endl;
		}
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

	long region_id = main_interface_->universe_ifc->get_region_id(location_id.get(), type);

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

void MainInterface::list_orders_parser(stringstream& stream, string& line) {
	long id;
	long region_id;
	const unordered_set<string> list_specifiers = { "region", "system", "station" };
	string type;
	string specifier;
	stream >> specifier;
	shared_ptr<vector<string>> commands = get_parameters(line);
	if (commands->size() > 0)
	{
		try {
			type = "inventory_types";
			id = universe_ifc->get_id_from_name((*commands)[0], type);
		}
		catch (ApiException e) {
			// Bad response from the server
			out_ << e.what() << endl;
			return;
		}
		catch (web::json::json_exception e) {
			// Likely a wrong ID
			if (e.what() == "Key was not found") {
				out_ << "Invalid ID" << endl;
				return;
			}
			out_ << e.what() << endl;
			return;
		}
		
		if ((*commands).size() > 1) {
			try {
				if (specifier == "region") {
					type = "regions";
					long region_id = universe_ifc->get_id_from_name((*commands)[1], type);
					market_ifc->get_type_orders(id, region_id, id_type::region)->print();
				}

				else if (specifier == "system") {
					type = "systems";
					long system_id = universe_ifc->get_id_from_name((*commands)[1], type);
					market_ifc->get_type_orders(id, system_id, id_type::system)->print();
				}

				else if (specifier == "station") {
					type = "stations";
					long system_id = universe_ifc->get_id_from_name((*commands)[1], type);
					market_ifc->get_type_orders(id, system_id, id_type::station)->print();
				}
				
				else if (specifier == "structure") {
					long long structure_id = stoll((*commands)[1]);
					market_ifc->get_type_orders(id, structure_id, id_type::system)->print();
				}
				
				return;
			}
			catch (ApiException e) {
				e.what();
				return;
			}
			catch (web::json::json_exception e) {
				if (e.what() == "Key was not found") {
					out_ << "Invalid ID" << endl;
					return;
				}
				out_ << e.what() << endl;
				return;
			}
		}

		if (specifier == "region") {
			market_ifc->get_type_orders(id, {}, id_type::region)->print();
		}

		else if (specifier == "system") {
			market_ifc->get_type_orders(id, {}, id_type::system)->print();
		}

		else if (specifier == "station") {
			market_ifc->get_type_orders(id, {}, id_type::station)->print();
		}

		else if (specifier == "strutcture") {
			market_ifc->get_type_orders(id, {}, id_type::structure)->print();
		}

		else {
			// Printing default region orders if no valid specifier available
			market_ifc->get_type_orders(id, {}, id_type::region)->print();
		}
	}
	
	else {
		out_ << "No arguments given/Wrong format" << endl;
	}
}

UniverseInterface::UniverseInterface(std::unique_ptr<UniverseApi>& universe_api) : universe_api_(universe_api) {};

shared_ptr<string> UniverseInterface::get_name_from_id(long id) {
	auto it = id_to_name_cache_.find(id);
	if (it != id_to_name_cache_.end()) {
		return make_shared<string>(id_to_name_cache_[id]);
	}

	else {
		vector<int> temp{ id };
		auto response = universe_api_->postUniverseNames(temp, {});
		auto json = response.get()[0]->toJson();
		try {
			auto res = to_utf8string(json.at(to_string_t("name")).as_string());
			name_to_id_cache_[res] = id;
			id_to_name_cache_[id] = res;
			return make_shared<string>(res);
		}
		catch (web::json::json_exception e) {
			throw(e);
		}
		catch (ApiException e) {
			throw(e);
		}
	}
}

long UniverseInterface::get_id_from_name(const string& name, const string& type) {
	try {
		long res = stoi(name);
		return res;
	}
	catch (invalid_argument) {
		auto it = name_to_id_cache_.find(name);
		if (it != name_to_id_cache_.end()) {
			return name_to_id_cache_[name];
		}


		vector<utility::string_t> temp{ to_string_t(name) };
		auto response = universe_api_->postUniverseIds(temp, {}, {}, {});
		auto json = response.get()->toJson();
		try {
			auto res = json.at(to_string_t(type))[0].at(to_string_t("id")).as_number().to_uint32();
			name_to_id_cache_[name] = res;
			id_to_name_cache_[res] = name;
			return res;
		}
		catch (web::json::json_exception e) {
			throw(e);
		}
	}
}

long UniverseInterface::get_region_id(const long long id, const id_type type) {
	Concurrency::task<shared_ptr<Object>> constell_response;
	Concurrency::task<shared_ptr<Object>> region_response;
	Concurrency::task<shared_ptr<Object>> system_response;
	long constell_id;
	long system_id;

	try {
		switch (type) {
		case id_type::region:
			return id;
			break;
		case id_type::structure:
			return -1;
			break;
		case id_type::station:
			system_response = universe_api_->getUniverseStationsStationId(id, {}, {});
			system_id = system_response.get()->toJson().at(to_string_t("system_id")).as_integer();
			constell_response = universe_api_->getUniverseSystemsSystemId(system_id, {}, {}, {}, {});
			constell_id = constell_response.get()->toJson().at(to_string_t("constellation_id")).as_integer();
			region_response = universe_api_->getUniverseConstellationsConstellationId(constell_id, {}, {}, {}, {});
			return region_response.get()->toJson().at(to_string_t("region_id")).as_integer();
			break;
		case id_type::system:
			constell_response = universe_api_->getUniverseSystemsSystemId(id, {}, {}, {}, {});
			constell_id = constell_response.get()->toJson().at(to_string_t("constellation_id")).as_integer();
			region_response = universe_api_->getUniverseConstellationsConstellationId(constell_id, {}, {}, {}, {});
			return region_response.get()->toJson().at(to_string_t("region_id")).as_integer();
			break;
		}
	}
	catch (ApiException e) {
		throw(e);
	}

	catch (web::json::json_exception e) {
		throw(e);
	}
}

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

AssetInterface::AssetInterface(std::unique_ptr<AssetsApi>& asset_api) : asset_api_(asset_api) {};

CharacterInterface::CharacterInterface(std::unique_ptr<CharacterApi>& character_api) : character_api_(character_api) {};

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

shared_ptr<string> json_field_to_string(web::json::value& value) {
	// Converts a field of the given json value to a string
	// Assumed to not be an array or another json value.

	string res;
	if (value.is_number()) {
		if (value.is_double()) {
			res = to_string(value.as_double());
		}

		if (value.is_integer()) {
			res = to_string(value.as_integer());
		}
	}

	if (value.is_string()) {
		res = to_utf8string(value.as_string());
	}
	return make_shared<string>(res);
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

void Orders::sort(std::vector<std::shared_ptr<web::json::value>>& orders, sort_type type, sort_by field) {
	// TODO
}

void MainInterface::print_head(const std::list<std::pair<std::string, std::string>>& descriptions, int width) {
	for (auto it = descriptions.begin(); it != descriptions.end(); it++) {
		int size = (*it).second.size();
		cout << (*it).second;
		for (int i = size; size < width; size++) {
			cout << " ";
		}
		cout << "|";
	}
	cout << "\n";
}

void MainInterface::print_line(const std::list<std::pair<std::string, std::string>>& descriptions, int width) {
	int des_size = descriptions.size();
	for (int i = 0; i < (width * des_size) + des_size; i++) {
		cout << "-";
	};
	cout << endl;
}

bool MainInterface::is_id(const std::unordered_set<std::string>& id_fields, const string& key) {
	auto it = id_fields.find(key);
	return (it != id_fields.end()) ? true : false;
}

void MainInterface::print_json_vector(std::vector<std::shared_ptr<web::json::value>>& vec,
	const std::list<std::pair<std::string, std::string>>& descriptions,
	const std::unordered_set<std::string>& id_fields,
	int width) {
	// Displays information from the fields specifiend in descriptions_
	// in a table-like format
	bool skip = false;
	string buffer = "";

	for (auto it = vec.begin(); it != vec.end(); it++) {
		skip = false;
		buffer = "";
		for (auto description_it = descriptions.begin(); description_it != descriptions.end(); description_it++) {
			// Display the information from the json at the given key
			auto json = **it;
			auto key = description_it->first;
			auto value = json.at(to_string_t(key));
			shared_ptr<string> field;
			if (is_id(id_fields, key)) {
				auto id = json.at(to_string_t(key)).as_number();
				if (id.is_int32()) {
					
					field = universe_ifc->get_name_from_id(id.to_int32());
				}
				else {
					// TODO: OAuth token required to resolve this ID
					skip = true;
					break;
				}
			}

			else {
				field = json_field_to_string(value);
			}

			if (field->size() > width) {
				// Too long, truncate it
				for (int i = 0; i < width - 3; i++) {
					buffer += (*field)[i];
				}
				buffer += "...";
			}

			else {
				// Can print the whole value
				buffer += (*field);
				for (int i = field->size(); i < width; i++) {
					buffer += " ";
				}
			}

			// Coulmn separator
			buffer += "|";
		}

		if (skip) {
			continue;
		}

		buffer += '\n';
		cout << buffer;
		print_line(descriptions, width);
	}
}

void Orders::print(int width) {
	cout << endl;
	cout << "Sell Orders" << endl << endl;
	main_interface_.print_head(descriptions_, width);
	main_interface_.print_line(descriptions_, width);
	main_interface_.print_json_vector(sell_orders_json_, descriptions_, id_fields_);

	cout << endl;
	cout << "Buy Orders" << endl << endl;
	main_interface_.print_head(descriptions_, width);
	main_interface_.print_line(descriptions_, width);
	main_interface_.print_json_vector(buy_orders_json_, descriptions_, id_fields_);
}