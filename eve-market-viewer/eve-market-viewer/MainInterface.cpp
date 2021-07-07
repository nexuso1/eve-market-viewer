#include "Interface.h"
#include<unordered_map>
#include<ctime>
#include<fstream>
#include<vector>
#include<regex>
#include<fstream>

using namespace io::swagger::client::api;
using namespace std;
using namespace utility::conversions;

MainInterface::MainInterface(std::ostream& out) : out_(out)
{
	setup_api_client();
	setup_apis();
	create_interfaces();
	printer_ = make_unique<Printer>(out_, *this);
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

void MainInterface::setup_apis() {
	// Sets up the various API classes for interacting
	// with ESI
	market_api_ = make_unique<MarketApi>(api_client_);
	universe_api_ = make_unique<UniverseApi>(api_client_);
	search_api_ = make_unique<SearchApi>(api_client_);
}

void MainInterface::create_interfaces() {
	// Create the member interfaces
	market_ifc_ = make_unique<MarketInterface>(market_api_, this);
	universe_ifc_ = make_unique<UniverseInterface>(universe_api_, this);
	search_ifc_ = make_unique<SearchInterface>(search_api_);
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

	else if (first == "history") {
		history_parser(stream, line);
	}

	else if (first == "describe") {
		describe_parser(stream, line);
	}

	else {
		out_ << "Invalid argument. See \"help\" for usage." << endl;
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
	long id; // type id
	long location_id;
	string type; // what location type are the orders
	string specifier; // location type specifier from input
	string sort; // potential sort keyword
	string sort_field; // field to sort by
	string sort_t_string; // sort type from input
	sort_type sort_t; // sort type enum
	id_type id_t; // id type enum
	field_type field_t; // field type enum
	bool sort_mode = false; // whether to sort the orders at the end
	stream >> specifier;

	if (specifier == "sort") {
		// might want to not specify the range, but sort anyway
		sort_mode = true;
		stream >> sort_field;
	}


	else {
		// Specified the range, and might try to sort
		stream >> sort;
		if (sort == "sort") {
			stream >> sort_field;
			sort_mode = true;
		}
	}

	if (sort_mode) {
		transform(sort_field.begin(), sort_field.end(), sort_field.begin(), ::tolower); // normalize format
		if (sort_field[0] == '\"') {
			out_ << "Invalid sort mode." << endl;
			return;
		}
		
		try {
			stream >> sort_t_string;
			transform(sort_t_string.begin(), sort_t_string.end(), sort_t_string.begin(), ::tolower); // normalize format
			if (sort_t_string == "ascending") {
				sort_t = sort_type::ascending;
			}

			else if (sort_t_string == "descending") {
				sort_t = sort_type::descending;
			}

			else {
				out_ << "Invalid sort order" << endl;
				return;
			}

			field_t = mode_to_field_type.at(sort_field);
		}

		catch (exception e) {
			out_ << "Wrong input." << endl;
			return;
		}

	}

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

		if (commands->size() > 1) {
			try {
				if (specifier == "region") {
					type = "regions";
					location_id = universe_ifc_->get_id_from_name((*commands)[1], type);
					id_t = id_type::region;
				}

				else if (specifier == "system") {
					type = "systems";
					location_id = universe_ifc_->get_id_from_name((*commands)[1], type);
					id_t = id_type::system;
				}

				else if (specifier == "station") {
					type = "stations";
					location_id = universe_ifc_->get_id_from_name((*commands)[1], type);
					id_t = id_type::station;
				}

				else {
					type = "regions";
					location_id = universe_ifc_->get_id_from_name((*commands)[1], type);
					id_t = id_type::region;
					
				}
				auto orders = market_ifc_->get_type_orders(id, location_id, id_t);
				if (sort_mode) {
					orders->sort(to_string_t(sort_field), sort_t, field_t);
				}
				orders->print();
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
			id_t = id_type::region;
		}

		else if (specifier == "system") {
			id_t = id_type::system;
		}

		else if (specifier == "station") {
			id_t = id_type::station;
		}

		else {
			// Printing default region orders if no valid specifier available
			id_t = id_type::region;
		}
		auto orders = market_ifc_->get_type_orders(id, {}, id_t);
		if (sort_mode) {
			orders->sort(to_string_t(sort_field), sort_t, field_t);
		}
		orders->print();
	}
	
	else {
		out_ << "No arguments given/Wrong format" << endl;
	}
}

void MainInterface::history_parser(stringstream& stream, string& line) {
	long type_id;
	long region_id;
	auto params = *get_parameters(line).get();
	string sort; // potential sort keyword
	string sort_field; // field to sort by
	string sort_t_string; // sort type from input
	sort_type sort_t; // sort type enum
	id_type id_t; // id type enum
	field_type field_t; // field type enum
	bool sort_mode = false; // whether to sort the orders at the end

	if (params.size() > 0) {
		// Might try to sort
		stream >> sort;
		if (sort == "sort") {
			stream >> sort_field;
			sort_mode = true;
		}

		if (sort_mode) {
			transform(sort_field.begin(), sort_field.end(), sort_field.begin(), ::tolower); // normalize format
			if (sort_field[0] == '\"') {
				out_ << "Invalid sort mode." << endl;
				return;
			}

			try {
				stream >> sort_t_string;
				transform(sort_t_string.begin(), sort_t_string.end(), sort_t_string.begin(), ::tolower); // normalize format
				if (sort_t_string == "ascending") {
					sort_t = sort_type::ascending;
				}

				else if (sort_t_string == "descending") {
					sort_t = sort_type::descending;
				}

				else {
					out_ << "Invalid sort order" << endl;
					return;
				}

				field_t = mode_to_field_type.at(sort_field);
			}

			catch (exception e) {
				out_ << "Wrong input." << endl;
				return;
			}
		}

		try {
			type_id = universe_ifc_->get_id_from_name(params[0], "inventory_types"); // convert the name to ID
			if (params.size() > 1) {
				region_id = universe_ifc_->get_id_from_name(params[1], "regions"); // convert region name to ID

				// Print info
				auto info = universe_ifc_->get_type_info(type_id);
				printer_->print_description(info);

				// Print history
				auto history = market_ifc_->get_type_history(type_id, region_id);
				if (sort_mode) {
					history->sort(to_string_t(sort_field), sort_t, field_t);
				}
				history->print();
			}

			else {
				// Default region
				auto info = universe_ifc_->get_type_info(type_id);
				printer_->print_description(info);
				auto history = market_ifc_->get_type_history(type_id, {});
				if (sort_mode) {
					history->sort(to_string_t(sort_field), sort_t, field_t);
				}
				history->print();
			}
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
	}
}

void MainInterface::describe_parser(stringstream& stream, string& line) {
	// Prints the description of the given types in input. Exact matches only.

	auto params = *get_parameters(line).get();
	if (params.size() > 0) {
		string name;
		string type = "inventory_types";
		long id;
		for (int i = 0; i < params.size(); i++) {
			// Go through every name and print the description
			name = params[i];
			try {
				id = universe_ifc_->get_id_from_name(name, type);
			}
			catch (web::json::json_exception e) {
				out_ << "Invalid name." << endl;
				return;
			}
			auto info = universe_ifc_->get_type_info(id);
			printer_->print_description(info);
			out_ << endl;
		}

	}

	else {
		out_ << "No paramters given." << endl;
	}
}

bool MainInterface::is_id(const std::unordered_set<std::string>& id_fields, const string& key) {
	auto it = id_fields.find(key);
	return (it != id_fields.end()) ? true : false;
}