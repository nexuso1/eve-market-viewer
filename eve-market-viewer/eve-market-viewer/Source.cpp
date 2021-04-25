#include <string>
#include <utility>
#include "cpprest-client/ApiClient.h"
#include "cpprest-client/ApiConfiguration.h"
#include "cpprest-client/api/CharacterApi.h"
#include "cpprest-client/api/MarketApi.h"
#include "cpprest-client/api/AssetsApi.h"
#include "cpprest-client/api/UniverseApi.h"
#include "Interface.h"

using namespace io::swagger::client::api;
using namespace utility::conversions;
using namespace std;

shared_ptr<ApiClient>& setup_api_client() {
	/// <summary>
	/// Sets up the the basic API client for interaction with ESI
	/// </summary>
	/// <returns>A shared pointer to the client</returns>
	utility::string_t base_URL = to_string_t("https://esi.evetech.net/latest/");

	auto api_config = make_shared<ApiConfiguration>();
	api_config->setBaseUrl(base_URL);
	api_config->setUserAgent(to_string_t("User-Agent"));

	auto api_client = make_shared<ApiClient>(api_config);

	api_client->setConfiguration(api_config);
	return api_client;
}

void init() {
	auto api_client = setup_api_client();
	auto market_api = make_shared<MarketApi>(api_client);
	auto asset_api = make_shared<AssetsApi>(api_client);
	auto universe_api = make_shared<UniverseApi>(api_client);
	auto character_api = make_shared<CharacterApi>(api_client);
	Interface api_interface()
}


int main() {
	utility::string_t base_URL = to_string_t("https://esi.evetech.net/latest/");

	auto api_config = make_shared<ApiConfiguration>();
	api_config->setBaseUrl(base_URL);
	api_config->setUserAgent(to_string_t("User-Agent"));

	auto api_client = make_shared<ApiClient>(api_config);
	
	api_client->setConfiguration(api_config);
	auto character_api = CharacterApi(api_client);
	auto response = character_api.getCharactersCharacterId(2112625428, to_string_t("tranquility"), to_string_t("None"));
	auto res = response.get()->toJson();
	cout << to_utf8string(res.at(to_string_t("name")).serialize()) << endl;
}