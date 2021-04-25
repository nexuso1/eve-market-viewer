#include "InfoClasses.h"

using namespace io::swagger::client::api;

UniverseStorage::UniverseStorage(std::shared_ptr<UniverseApi>& universe_api) : universe_api_(universe_api) {};

MarketStorage::MarketStorage(std::shared_ptr<MarketApi>& market_api) : market_api_(market_api) {};

AssetStorage::AssetStorage(std::shared_ptr<AssetsApi>& asset_api) : asset_api_(asset_api) {};

CharacterStorage::CharacterStorage(std::shared_ptr<CharacterApi>& character_api) : character_api_(character_api) {};

