#include "Interface.h"


using namespace io::swagger::client::api;
using namespace std;
using namespace utility::conversions;

shared_ptr<web::json::value> SearchInterface::search(const string& query, const id_type type) {
	// Find the list of strings, which contain query as a substring, among predefined type category
	string type_name;
	switch (type) {
	case id_type::system:
		type_name = "solar_system";
		break;
	case id_type::region:
		type_name = "region";
		break;
	case id_type::station:
		type_name = "station";
		break;
	default:
		break;
	}

	auto response = search_api_->getSearch(vector<utility::string_t>({ to_string_t(type_name) }), to_string_t(query), {}, {}, {}, {}, {});
	return make_shared<web::json::value> (response.get()->toJson());
}

shared_ptr<web::json::value> SearchInterface::search(const string& query, const string& type) {
	auto response = search_api_->getSearch(vector<utility::string_t>({ to_string_t(type) }), to_string_t(query), {}, {}, {}, {}, {});
	return make_shared<web::json::value>(response.get()->toJson());
}
