#include "Interface.h"

Interface::Interface(std::shared_ptr<MarketApi>& market_api,
	std::shared_ptr<UniverseApi>& universe_api,
	std::shared_ptr<AssetsApi>& asset_api,
	std::shared_ptr<CharacterApi>& character_api) : market_api_(market_api), universe_api_(universe_api),
	asset_api_(asset_api), character_api_(character_api) {


};

