#include<cpprest/http_headers.h>
#include <string>
#include <utility>
#include "cpprest-client/ApiClient.h"
#include "cpprest-client/ApiException.h"
#include "cpprest-client/ApiConfiguration.h"
#include "cpprest-client/api/CharacterApi.h"


using namespace io::swagger::client::api;
using namespace utility::conversions;
using namespace std;


int main() {
	utility::string_t base_URL = to_string_t("https://esi.evetech.net/latest/");

	shared_ptr<ApiClient> api_client(new ApiClient);
	shared_ptr<ApiConfiguration> api_config(new ApiConfiguration);

	api_config->setBaseUrl(base_URL);
	api_config->setUserAgent(to_string_t("User-Agent"));
	
	api_client->setConfiguration(api_config);
	auto character_api = CharacterApi(api_client);
	auto response = character_api.getCharactersCharacterId(2112625428);
}