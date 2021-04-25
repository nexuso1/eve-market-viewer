#include "cpprest-client/ApiClient.h"
#include "cpprest-client/ApiConfiguration.h"
#include "cpprest-client/api/CharacterApi.h"
#include "cpprest-client/api/MarketApi.h"
#include "cpprest-client/api/AssetsApi.h"
#include "cpprest-client/api/UniverseApi.h"
#include "InfoClasses.h"

using namespace io::swagger::client::api;

class Interface
{
/// <summary>
/// The main API interface, provides acces to the various APIs, and their respective storages.
/// </summary>
public:
	Interface(std::shared_ptr<MarketApi>& market_api,
		std::shared_ptr<UniverseApi>& universe_api,
		std::shared_ptr<AssetsApi>& asset_api,
		std::shared_ptr<CharacterApi>& character_api);

private:
	std::shared_ptr<MarketApi> market_api_;
	std::shared_ptr<UniverseApi> universe_api_;
	std::shared_ptr<AssetsApi> asset_api_;
	std::shared_ptr<CharacterApi> character_api_;

	std::shared_ptr<UniverseStorage> universe_st_;
	std::shared_ptr<MarketStorage> market_st_;
	std::shared_ptr<AssetStorage> asset_st_;
	std::shared_ptr<CharacterStorage> character_st_;
};

