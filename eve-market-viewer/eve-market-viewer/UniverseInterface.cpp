#include "Interface.h"

using namespace io::swagger::client::api;
using namespace std;
using namespace utility::conversions;

UniverseInterface::UniverseInterface(std::unique_ptr<UniverseApi>& universe_api, MainInterface* main_interface) : 
	universe_api_(universe_api), main_interface_(main_interface) {};

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

shared_ptr<web::json::value>  UniverseInterface::get_type_info(long type_id) {
	auto response = universe_api_->getUniverseTypesTypeId(type_id, {}, {}, {}, {});
	return make_shared<web::json::value>(response.get()->toJson());
}

long UniverseInterface::get_id_from_name(const string& name, const string& type) {
	try {
		// Maybe it's an ID already
		long res = stoi(name);
		return res;
	}
	catch (invalid_argument) {
		// Try to find it in the cache first
		auto it = name_to_id_cache_.find(name);
		if (it != name_to_id_cache_.end()) {
			return name_to_id_cache_[name];
		}

		// First find the closest match

		if (type != "inventory_types") {
			// Since there is a lot of clutter in inventory types, 
			// the first match would be very unreliable (since ESI 
			// doesn't order it)
			try {
				unsigned int first_match;
				unordered_map<string, string> type_names{
					// Could potentially be different for some 
					// future category, so doing it this way
					{"regions", "region"},
					{"stations", "station"},
					{"systems", "system"},
				};
				auto matches = main_interface_->search_ifc_->search(name, type_names[type])->at(to_string_t(type_names[type])).as_array();
				first_match = matches[0].as_number().to_uint32();
				// Add it to cache
				name_to_id_cache_[name] = first_match;
				id_to_name_cache_[first_match] = *get_name_from_id(first_match); // convert the id to the correct name
				return first_match;
			}
			catch (web::json::json_exception e) {
				throw(e);
			}
			catch (invalid_argument e) {
				throw(e);
			}
		}

		// Take only exact names for inventory types
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
			// Already have it
			return id;
			break;
		case id_type::structure:
			// Cant resolve structures
			return -1;
			break;
		case id_type::station:
			// Have to find the system, then the constellation of the system and finally
			// the region of the constellation (thanks ESI)
			system_response = universe_api_->getUniverseStationsStationId(id, {}, {});
			system_id = system_response.get()->toJson().at(to_string_t("system_id")).as_integer();
			constell_response = universe_api_->getUniverseSystemsSystemId(system_id, {}, {}, {}, {});
			constell_id = constell_response.get()->toJson().at(to_string_t("constellation_id")).as_integer();
			region_response = universe_api_->getUniverseConstellationsConstellationId(constell_id, {}, {}, {}, {});
			return region_response.get()->toJson().at(to_string_t("region_id")).as_integer();
			break;
		case id_type::system:
			// Have to find the constellation, and then find the region it
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