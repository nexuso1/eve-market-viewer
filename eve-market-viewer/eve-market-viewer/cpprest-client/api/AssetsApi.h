/**
 * EVE Swagger Interface
 * An OpenAPI for EVE Online
 *
 * OpenAPI spec version: 1.7.15
 * 
 *
 * NOTE: This class is auto generated by the swagger code generator 2.4.19.
 * https://github.com/swagger-api/swagger-codegen.git
 * Do not edit the class manually.
 */

/*
 * AssetsApi.h
 *
 * 
 */

#ifndef IO_SWAGGER_CLIENT_API_AssetsApi_H_
#define IO_SWAGGER_CLIENT_API_AssetsApi_H_


#include "../ApiClient.h"

#include "../model/Bad_request.h"
#include "../model/Error_limited.h"
#include "../model/Forbidden.h"
#include "../model/Gateway_timeout.h"
#include "../model/Internal_server_error.h"
#include "../Object.h"
#include "../model/Service_unavailable.h"
#include "../model/Unauthorized.h"
#include <vector>
#include <cpprest/details/basic_types.h>

#include <boost/optional.hpp>

namespace io {
namespace swagger {
namespace client {
namespace api {

using namespace io::swagger::client::model;

class  AssetsApi
{
public:
    AssetsApi( std::shared_ptr<ApiClient> apiClient );
    virtual ~AssetsApi();
    /// <summary>
    /// Get character assets
    /// </summary>
    /// <remarks>
    /// Return a list of the characters assets  --- Alternate route: &#x60;/dev/characters/{character_id}/assets/&#x60;  Alternate route: &#x60;/v5/characters/{character_id}/assets/&#x60;  --- This route is cached for up to 3600 seconds
    /// </remarks>
    /// <param name="characterId">An EVE character ID</param>
    /// <param name="datasource">The server name you would like data from (optional, default to tranquility)</param>
    /// <param name="ifNoneMatch">ETag from a previous request. A 304 will be returned if this matches the current ETag (optional)</param>
    /// <param name="page">Which page of results to return (optional, default to 1)</param>
    /// <param name="token">Access token to use if unable to set a header (optional)</param>
    pplx::task<std::vector<std::shared_ptr<Object>>> getCharactersCharacterIdAssets(
        int32_t characterId,
        boost::optional<utility::string_t> datasource,
        boost::optional<utility::string_t> ifNoneMatch,
        boost::optional<int32_t> page,
        boost::optional<utility::string_t> token
    );
    /// <summary>
    /// Get corporation assets
    /// </summary>
    /// <remarks>
    /// Return a list of the corporation assets  --- Alternate route: &#x60;/dev/corporations/{corporation_id}/assets/&#x60;  Alternate route: &#x60;/v5/corporations/{corporation_id}/assets/&#x60;  --- This route is cached for up to 3600 seconds  --- Requires one of the following EVE corporation role(s): Director 
    /// </remarks>
    /// <param name="corporationId">An EVE corporation ID</param>
    /// <param name="datasource">The server name you would like data from (optional, default to tranquility)</param>
    /// <param name="ifNoneMatch">ETag from a previous request. A 304 will be returned if this matches the current ETag (optional)</param>
    /// <param name="page">Which page of results to return (optional, default to 1)</param>
    /// <param name="token">Access token to use if unable to set a header (optional)</param>
    pplx::task<std::vector<std::shared_ptr<Object>>> getCorporationsCorporationIdAssets(
        int32_t corporationId,
        boost::optional<utility::string_t> datasource,
        boost::optional<utility::string_t> ifNoneMatch,
        boost::optional<int32_t> page,
        boost::optional<utility::string_t> token
    );
    /// <summary>
    /// Get character asset locations
    /// </summary>
    /// <remarks>
    /// Return locations for a set of item ids, which you can get from character assets endpoint. Coordinates for items in hangars or stations are set to (0,0,0)  --- Alternate route: &#x60;/dev/characters/{character_id}/assets/locations/&#x60;  Alternate route: &#x60;/v2/characters/{character_id}/assets/locations/&#x60; 
    /// </remarks>
    /// <param name="characterId">An EVE character ID</param>
    /// <param name="itemIds">A list of item ids</param>
    /// <param name="datasource">The server name you would like data from (optional, default to tranquility)</param>
    /// <param name="token">Access token to use if unable to set a header (optional)</param>
    pplx::task<std::vector<std::shared_ptr<Object>>> postCharactersCharacterIdAssetsLocations(
        int32_t characterId,
        std::vector<int64_t> itemIds,
        boost::optional<utility::string_t> datasource,
        boost::optional<utility::string_t> token
    );
    /// <summary>
    /// Get character asset names
    /// </summary>
    /// <remarks>
    /// Return names for a set of item ids, which you can get from character assets endpoint. Typically used for items that can customize names, like containers or ships.  --- Alternate route: &#x60;/dev/characters/{character_id}/assets/names/&#x60;  Alternate route: &#x60;/legacy/characters/{character_id}/assets/names/&#x60;  Alternate route: &#x60;/v1/characters/{character_id}/assets/names/&#x60; 
    /// </remarks>
    /// <param name="characterId">An EVE character ID</param>
    /// <param name="itemIds">A list of item ids</param>
    /// <param name="datasource">The server name you would like data from (optional, default to tranquility)</param>
    /// <param name="token">Access token to use if unable to set a header (optional)</param>
    pplx::task<std::vector<std::shared_ptr<Object>>> postCharactersCharacterIdAssetsNames(
        int32_t characterId,
        std::vector<int64_t> itemIds,
        boost::optional<utility::string_t> datasource,
        boost::optional<utility::string_t> token
    );
    /// <summary>
    /// Get corporation asset locations
    /// </summary>
    /// <remarks>
    /// Return locations for a set of item ids, which you can get from corporation assets endpoint. Coordinates for items in hangars or stations are set to (0,0,0)  --- Alternate route: &#x60;/dev/corporations/{corporation_id}/assets/locations/&#x60;  Alternate route: &#x60;/v2/corporations/{corporation_id}/assets/locations/&#x60;   --- Requires one of the following EVE corporation role(s): Director 
    /// </remarks>
    /// <param name="corporationId">An EVE corporation ID</param>
    /// <param name="itemIds">A list of item ids</param>
    /// <param name="datasource">The server name you would like data from (optional, default to tranquility)</param>
    /// <param name="token">Access token to use if unable to set a header (optional)</param>
    pplx::task<std::vector<std::shared_ptr<Object>>> postCorporationsCorporationIdAssetsLocations(
        int32_t corporationId,
        std::vector<int64_t> itemIds,
        boost::optional<utility::string_t> datasource,
        boost::optional<utility::string_t> token
    );
    /// <summary>
    /// Get corporation asset names
    /// </summary>
    /// <remarks>
    /// Return names for a set of item ids, which you can get from corporation assets endpoint. Only valid for items that can customize names, like containers or ships  --- Alternate route: &#x60;/dev/corporations/{corporation_id}/assets/names/&#x60;  Alternate route: &#x60;/legacy/corporations/{corporation_id}/assets/names/&#x60;  Alternate route: &#x60;/v1/corporations/{corporation_id}/assets/names/&#x60;   --- Requires one of the following EVE corporation role(s): Director 
    /// </remarks>
    /// <param name="corporationId">An EVE corporation ID</param>
    /// <param name="itemIds">A list of item ids</param>
    /// <param name="datasource">The server name you would like data from (optional, default to tranquility)</param>
    /// <param name="token">Access token to use if unable to set a header (optional)</param>
    pplx::task<std::vector<std::shared_ptr<Object>>> postCorporationsCorporationIdAssetsNames(
        int32_t corporationId,
        std::vector<int64_t> itemIds,
        boost::optional<utility::string_t> datasource,
        boost::optional<utility::string_t> token
    );

protected:
    std::shared_ptr<ApiClient> m_ApiClient;
};

}
}
}
}

#endif /* IO_SWAGGER_CLIENT_API_AssetsApi_H_ */

