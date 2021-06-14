#include "Interface.h"
#include<unordered_map>
#include<fstream>
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
	printer_ = make_unique<Printer>(out_, *this);
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
	market_ifc_ = make_unique<MarketInterface>(market_api_, this);
	universe_ifc_ = make_unique<UniverseInterface>(universe_api_);
	asset_ifc_ = make_unique<AssetInterface>(asset_api_);
	character_ifc_ = make_unique<CharacterInterface>(character_api_);
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
		printer_->print_help();
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
			id = universe_ifc_->get_id_from_name(name, key_type);
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
			market_ifc_->set_region(id);
			out_ << ">Region set." << endl;
		}
		else if (!it->first.compare("station")) {
			market_ifc_->set_station(id);
			out_ << ">Station set." << endl;
		}
		else if (!it->first.compare("system")) {
			market_ifc_->set_system(id);
			out_ << ">System set." << endl;
		}
	}
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
			id = universe_ifc_->get_id_from_name((*commands)[0], type);
		}
		catch (ApiException e) {
			// Bad response from the server
			out_ << e.what() << endl;
			return;
		}
		catch (web::json::json_exception e) {
			// Likely a wrong ID
			const string temp = "Key not found";
			if (temp.compare(e.what())) {
				out_ << "Invalid ID/Name" << endl;
				return;
			}
			out_ << e.what() << endl;
			return;
		}
		
		auto info = universe_ifc_->get_type_info(id);
		printer_->print_description(info);

		if ((*commands).size() > 1) {
			try {
				if (specifier == "region") {
					type = "regions";
					long region_id = universe_ifc_->get_id_from_name((*commands)[1], type);
					market_ifc_->get_type_orders(id, region_id, id_type::region)->print();
				}

				else if (specifier == "system") {
					type = "systems";
					long system_id = universe_ifc_->get_id_from_name((*commands)[1], type);
					market_ifc_->get_type_orders(id, system_id, id_type::system)->print();
				}

				else if (specifier == "station") {
					type = "stations";
					long system_id = universe_ifc_->get_id_from_name((*commands)[1], type);
					market_ifc_->get_type_orders(id, system_id, id_type::station)->print();
				}
				
				else if (specifier == "structure") {
					long long structure_id = stoll((*commands)[1]);
					market_ifc_->get_type_orders(id, structure_id, id_type::system)->print();
				}

				else {
					type = "regions";
					long region_id = universe_ifc_->get_id_from_name((*commands)[1], type);
					market_ifc_->get_type_orders(id, {}, id_type::region)->print();
				}
				
				return;
			}
			catch (ApiException e) {
				e.what();
				return;
			}
			catch (web::json::json_exception e) {
				const string temp = "Key not found";
				if (!temp.compare(e.what())) {
					out_ << "Invalid ID/Name" << endl;
					return;
				}
				out_ << e.what() << endl;
				return;
			}
		}

		if (specifier == "region") {
			market_ifc_->get_type_orders(id, {}, id_type::region)->print();
		}

		else if (specifier == "system") {
			market_ifc_->get_type_orders(id, {}, id_type::system)->print();
		}

		else if (specifier == "station") {
			market_ifc_->get_type_orders(id, {}, id_type::station)->print();
		}

		else if (specifier == "strutcture") {
			market_ifc_->get_type_orders(id, {}, id_type::structure)->print();
		}

		else {
			// Printing default region orders if no valid specifier available
			market_ifc_->get_type_orders(id, {}, id_type::region)->print();
		}
	}
	
	else {
		out_ << "No arguments given/Wrong format" << endl;
	}
}

AssetInterface::AssetInterface(std::unique_ptr<AssetsApi>& asset_api) : asset_api_(asset_api) {};

CharacterInterface::CharacterInterface(std::unique_ptr<CharacterApi>& character_api) : character_api_(character_api) {};

bool MainInterface::is_id(const std::unordered_set<std::string>& id_fields, const string& key) {
	auto it = id_fields.find(key);
	return (it != id_fields.end()) ? true : false;
}