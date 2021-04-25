#include "cpprest-client/ApiClient.h"
#include "cpprest-client/ApiConfiguration.h"
#include "cpprest-client/api/CharacterApi.h"
#include "cpprest-client/api/MarketApi.h"
#include "cpprest-client/api/AssetsApi.h"
#include "cpprest-client/api/UniverseApi.h"

using namespace io::swagger::client::api;

class Interface
{
public:
	Interface(std::shared_ptr<MarketApi>& market_api,
		std::shared_ptr<UniverseApi>& universe_api,
		std::shared_ptr<AssetsApi>& asset_api,
		std::shared_ptr<MarketApi>& character_api);

private:
	std::shared_ptr<MarketApi> market_api_;
	std::shared_ptr<UniverseApi> universe_api_;
	std::shared_ptr<AssetsApi> asset_api_;
	std::shared_ptr<CharacterApi> character_api_;
};

