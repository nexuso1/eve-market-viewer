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
Name parameters are case insesitive.Can be substituted for IDs.\n \
\
list \"<type_name>\"[\"<region_name>\"] - lists currently available market orders of <type_name> in <region_name>,\n \
											if no region is provided, lists from the defaultone\n \
set <paramater> \"<name>\"				- sets the default <parameter> to <name>\n \
										-available parameters : -region\n \
										- station(TODO)\n \
										- sets the station, but orders by station aren't\n \
										implemented yet.\n \
										- system(TODO)\n \
										- same for system\n \
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
	market_st_ = make_unique<MarketInterface>(market_api_, this);
	universe_st_ = make_unique<UniverseInterface>(universe_api_);
	asset_st_ = make_unique<AssetInterface>(asset_api_);
	character_st_ = make_unique<CharacterInterface>(character_api_);
}

void MainInterface::parse_command(stringstream& stream, string& line) {
	// Resolves the first token of the command, then calls the corresponding
	// function
	string first;
	stream >> first;
	if (first == "list") {
		list_orders_parser(line);
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
			id = universe_st_->get_id_from_name(name, key_type);
		}
		catch (ApiException e) {
			out_ << e.what();
			return;
		}
		catch (web::json::json_exception e) {
			out_ << e.what();
			return;
		}
		
		// Call a function based on token,
		// .compare has inverted logic
		if (!it->first.compare("region")) {
			market_st_->set_region(id);
			out_ << ">Region set." << endl;
		}
		else if (!it->first.compare("station")) {
			market_st_->set_station(id);
			out_ << ">Station set." << endl;
		}
		else if (!it->first.compare("system")) {
			market_st_->set_system(id);
			out_ << ">System set." << endl;
		}
	}
}

void MainInterface::list_orders_parser(string& line) {
	long id;
	string type;
	shared_ptr<vector<string>> commands = get_parameters(line);
	if (commands->size() > 0)
	{
		try {
			type = "inventory_types";
			id = universe_st_->get_id_from_name((*commands)[0], type);
		}
		catch (ApiException e) {
			// Bad response from the server
			out_ << e.what();
			return;
		}
		catch (web::json::json_exception e) {
			// Likely a wrong ID
			if (e.what() == "Key was not found") {
				out_ << "Invalid ID" << endl;
				return;
			}
			out_ << e.what();
			return;
		}
		
		if ((*commands).size() > 1) {
			try {
				type = "regions";
				long region_id = universe_st_->get_id_from_name((*commands)[1], type);
				market_st_->get_type_orders_region(id, region_id).print();
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

		market_st_->get_type_orders_region(id, {}).print();
	}
	
	else {
		out_ << "No arguments given" << endl;
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

//shared_ptr<string> UniverseInterface::get_name_from_id(int64_t id) {
//	// TODO (requires OAuth, which isn't implemented at the moment)
//	// Int64 is used for player-made structures and other dynamic things,
//	// and specifically these structurures may require access permissions,
//	// so we're going to need to authenticate a character.
//	auto it = id_to_name_cache_.find(id);
//	if (it != id_to_name_cache_.end()) {
//		return make_shared<string>(id_to_name_cache_[id]);
//	}
//
//	else {
//		vector<int> temp{ id };
//		auto response = universe_api_->postUniverseNames(temp, {});
//		auto json = response.get()[0]->toJson();
//		try {
//			auto res = to_utf8string(json.at(to_string_t("name")).as_string());
//			name_to_id_cache_[res] = id;
//			id_to_name_cache_[id] = res;
//			return make_shared<string>(res);
//		}
//		catch (web::json::json_exception e) {
//			throw(e);
//		}
//		catch (ApiException e) {
//			throw(e);
//		}
//	}
//}

long UniverseInterface::get_id_from_name(string& name, string& type) {
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

Orders MarketInterface::get_type_orders_region(int item_id, boost::optional<int> region_id) {
	// Returns an Orders instance consisting of orders of the items specified, page 1 by default, in the default reagion

	if (!region_id.is_initialized()) {
		// No region specified, so set to default
		region_id = region_id_;
	}

	vector<shared_ptr<web::json::value>> sell_orders;
	vector<shared_ptr<web::json::value>> buy_orders;

	parse_orders(sell_orders, false, region_id.get(), item_id);
	parse_orders(buy_orders, true, region_id.get(), item_id);
	return Orders(main_interface_->out_, buy_orders, sell_orders, *main_interface_);
}

//shared_ptr<web::json::value> get_type_orders_region(const string& name, boost::optional<int> region_id, int page = 1) {
//}

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
					
					field = universe_st_->get_name_from_id(id.to_int32());
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