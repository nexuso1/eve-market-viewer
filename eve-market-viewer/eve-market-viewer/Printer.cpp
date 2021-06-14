#include "Interface.h"

using namespace io::swagger::client::api;
using namespace std;
using namespace utility::conversions;

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

void Printer::print_head(const std::list<std::pair<std::string, std::string>>& descriptions, int width) {
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

void Printer::print_line(const std::list<std::pair<std::string, std::string>>& descriptions, int width) {
	int des_size = descriptions.size();
	for (int i = 0; i < (width * des_size) + des_size; i++) {
		cout << "-";
	};
	cout << endl;
}

void Printer::print_line(int length) {
	for (int i = 0; i < length; i++) {
		cout << "-";
	};
	cout << endl;
}

void Printer::print_help() {

	string line;
	ifstream help("help.txt");
	while (getline(help, line)) {
		out_ << line << endl;
	}
	out_ << endl;
}

void Printer::print_description(std::shared_ptr<web::json::value>& json) {
	// Prints the description at the start of the listing, just for nicer
	// presentation

	bool skip = false;
	auto name = json_field_to_string(json->at(to_string_t("name")));
	auto desc = json_field_to_string(json->at(to_string_t("description")));
	out_ << *name.get() << endl;
	print_line(name.get()->length());
	int counter = 0;
	stringstream stream(*desc.get());
	string buf;
	while (stream >> buf) {
		if (counter > 80) {
			out_ << endl;
			counter = 0;
		}

		out_ << buf;
		out_ << " ";
		counter += buf.length();
	}
	out_ << endl;
}

void Printer::print_json_vector(std::vector<std::shared_ptr<web::json::value>>& vec,
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
			if (main_ifc_.is_id(id_fields, key)) {
				auto id = json.at(to_string_t(key)).as_number();
				if (id.is_int32()) {

					field = main_ifc_.universe_ifc_->get_name_from_id(id.to_int32());
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