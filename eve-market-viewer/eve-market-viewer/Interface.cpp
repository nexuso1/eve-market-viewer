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

void MainInterface::setup_apis() {
	asset_api_ = make_unique<AssetsApi>(api_client_);
	character_api_ = make_unique<CharacterApi>(api_client_);
	market_api_ = make_unique<MarketApi>(api_client_);
	universe_api_ = make_unique<UniverseApi>(api_client_);
}

void MainInterface::create_interfaces() {
	// Create the member interfaces
	market_st_ = make_unique<MarketInterface>(market_api_, this);
	universe_st_ = make_unique<UniversInterface>(universe_api_);
	asset_st_ = make_unique<AssetInterface>(asset_api_);
	character_st_ = make_unique<CharacterInterface>(character_api_);
}

void MainInterface::parse_command(stringstream& stream, string& line) {
	string first;
	stream >> first;
	if (first == "list") {
		list_orders_parser(line);
	}
	else if (first == "set") {
		set_parser(stream, line);
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
		res.push_back(matches[1]);
		search_start = matches.suffix().first;
	}
	
	return make_shared<vector<string>>(res);
}

void MainInterface::set_parser(stringstream& stream, string& line) {
	string type;
	stream >> type;
	string name = (*get_parameters(line))[0];

	// Correspond to various set functions
	const unordered_map<string, string> param_types{
		{"region" ,"regions" },
		{"station", "stations"},
		{"system", "systems"}
	};

	auto it = param_types.find(type);
	if (it != param_types.end()) {
		int id;
		string key_type = it->second;
		try {
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
			out_ << e.what();
			return;
		}
		catch (web::json::json_exception e) {
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

UniversInterface::UniversInterface(std::unique_ptr<UniverseApi>& universe_api) : universe_api_(universe_api) {};

long UniversInterface::get_id_from_name(string& name, string& type) {
	try {
		long res = stoi(name);
		return res;
	}
	catch (invalid_argument) {
		vector<utility::string_t> temp{ to_string_t(name) };
		auto response = universe_api_->postUniverseIds(temp, {}, {}, {});
		auto json = response.get()->toJson();
		try {
			return json.at(to_string_t(type))[0].at(to_string_t("id")).as_number().to_uint32();
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
	int page_n = 1;
	string order_type = "sell";
	if (buy) {
		order_type = "buy";
	}

	while (true) {
		try {
			auto page = market_api_->getMarketsRegionIdOrders(to_string_t(order_type), region_id, {}, {}, page_n, item_id).get();
			for (int i = 0; i < page.size(); i++) {
				orders.push_back(make_shared<web::json::value>(page[0]->toJson()));
			}
		}
		catch (ApiException e) {
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
	parse_orders(buy_orders, false, region_id.get(), item_id);
	return Orders(main_interface_->out_, buy_orders, sell_orders);
}

//shared_ptr<web::json::value> get_type_orders_region(const string& name, boost::optional<int> region_id, int page = 1) {
//}

AssetInterface::AssetInterface(std::unique_ptr<AssetsApi>& asset_api) : asset_api_(asset_api) {};

CharacterInterface::CharacterInterface(std::unique_ptr<CharacterApi>& character_api) : character_api_(character_api) {};