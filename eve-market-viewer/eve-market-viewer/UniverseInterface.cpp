#include "Interface.h"

using namespace io::swagger::client::api;
using namespace std;
using namespace utility::conversions;

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

shared_ptr<web::json::value>  UniverseInterface::get_type_info(long type_id) {
	auto response = universe_api_->getUniverseTypesTypeId(type_id, {}, {}, {}, {});
	return make_shared<web::json::value>(response.get()->toJson());
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