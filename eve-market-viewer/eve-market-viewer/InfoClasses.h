#include "cpprest-client/ApiClient.h"
#include "cpprest-client/ApiConfiguration.h"
#include "cpprest-client/api/CharacterApi.h"
#include "cpprest-client/api/MarketApi.h"
#include "cpprest-client/api/AssetsApi.h"
#include "cpprest-client/api/UniverseApi.h"

using namespace io::swagger::client::api;

class UniverseStorage {
public:
	UniverseStorage(std::shared_ptr<UniverseApi>& universe_api);

private:
	std::shared_ptr<UniverseApi>& universe_api_;
};

class MarketStorage {
public:
	MarketStorage(std::shared_ptr<MarketApi>& market_api);

private:
	std::shared_ptr<MarketApi>& market_api_;
};

class AssetStorage {
public:
	AssetStorage(std::shared_ptr<AssetsApi>& asset_api);

private:
	std::shared_ptr<AssetsApi>& asset_api_;
};


class CharacterStorage {
public:
	CharacterStorage(std::shared_ptr<CharacterApi>& character_api);

private:
	std::shared_ptr<CharacterApi>& character_api_;
};
