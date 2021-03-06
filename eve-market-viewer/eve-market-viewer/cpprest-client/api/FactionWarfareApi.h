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
 * FactionWarfareApi.h
 *
 * 
 */

#ifndef IO_SWAGGER_CLIENT_API_FactionWarfareApi_H_
#define IO_SWAGGER_CLIENT_API_FactionWarfareApi_H_


#include "../ApiClient.h"

#include "Bad_request.h"
#include "Error_limited.h"
#include "Forbidden.h"
#include "Gateway_timeout.h"
#include "Internal_server_error.h"
#include "Object.h"
#include "Service_unavailable.h"
#include "Unauthorized.h"
#include <cpprest/details/basic_types.h>

#include <boost/optional.hpp>

namespace io {
namespace swagger {
namespace client {
namespace api {

using namespace io::swagger::client::model;

class  FactionWarfareApi
{
public:
    FactionWarfareApi( std::shared_ptr<ApiClient> apiClient );
    virtual ~FactionWarfareApi();
    /// <summary>
    /// Overview of a character involved in faction warfare
    /// </summary>
    /// <remarks>
    /// Statistical overview of a character involved in faction warfare  --- Alternate route: &#x60;/dev/characters/{character_id}/fw/stats/&#x60;  Alternate route: &#x60;/legacy/characters/{character_id}/fw/stats/&#x60;  Alternate route: &#x60;/v1/characters/{character_id}/fw/stats/&#x60;  Alternate route: &#x60;/v2/characters/{character_id}/fw/stats/&#x60;  --- This route expires daily at 11:05
    /// </remarks>
    /// <param name="characterId">An EVE character ID</param>
    /// <param name="datasource">The server name you would like data from (optional, default to tranquility)</param>
    /// <param name="ifNoneMatch">ETag from a previous request. A 304 will be returned if this matches the current ETag (optional)</param>
    /// <param name="token">Access token to use if unable to set a header (optional)</param>
    pplx::task<std::shared_ptr<Object>> getCharactersCharacterIdFwStats(
        int32_t characterId,
        boost::optional<utility::string_t> datasource,
        boost::optional<utility::string_t> ifNoneMatch,
        boost::optional<utility::string_t> token
    );
    /// <summary>
    /// Overview of a corporation involved in faction warfare
    /// </summary>
    /// <remarks>
    /// Statistics about a corporation involved in faction warfare  --- Alternate route: &#x60;/dev/corporations/{corporation_id}/fw/stats/&#x60;  Alternate route: &#x60;/legacy/corporations/{corporation_id}/fw/stats/&#x60;  Alternate route: &#x60;/v1/corporations/{corporation_id}/fw/stats/&#x60;  Alternate route: &#x60;/v2/corporations/{corporation_id}/fw/stats/&#x60;  --- This route expires daily at 11:05
    /// </remarks>
    /// <param name="corporationId">An EVE corporation ID</param>
    /// <param name="datasource">The server name you would like data from (optional, default to tranquility)</param>
    /// <param name="ifNoneMatch">ETag from a previous request. A 304 will be returned if this matches the current ETag (optional)</param>
    /// <param name="token">Access token to use if unable to set a header (optional)</param>
    pplx::task<std::shared_ptr<Object>> getCorporationsCorporationIdFwStats(
        int32_t corporationId,
        boost::optional<utility::string_t> datasource,
        boost::optional<utility::string_t> ifNoneMatch,
        boost::optional<utility::string_t> token
    );
    /// <summary>
    /// List of the top factions in faction warfare
    /// </summary>
    /// <remarks>
    /// Top 4 leaderboard of factions for kills and victory points separated by total, last week and yesterday  --- Alternate route: &#x60;/dev/fw/leaderboards/&#x60;  Alternate route: &#x60;/legacy/fw/leaderboards/&#x60;  Alternate route: &#x60;/v1/fw/leaderboards/&#x60;  Alternate route: &#x60;/v2/fw/leaderboards/&#x60;  --- This route expires daily at 11:05
    /// </remarks>
    /// <param name="datasource">The server name you would like data from (optional, default to tranquility)</param>
    /// <param name="ifNoneMatch">ETag from a previous request. A 304 will be returned if this matches the current ETag (optional)</param>
    pplx::task<std::shared_ptr<Object>> getFwLeaderboards(
        boost::optional<utility::string_t> datasource,
        boost::optional<utility::string_t> ifNoneMatch
    );
    /// <summary>
    /// List of the top pilots in faction warfare
    /// </summary>
    /// <remarks>
    /// Top 100 leaderboard of pilots for kills and victory points separated by total, last week and yesterday  --- Alternate route: &#x60;/dev/fw/leaderboards/characters/&#x60;  Alternate route: &#x60;/legacy/fw/leaderboards/characters/&#x60;  Alternate route: &#x60;/v1/fw/leaderboards/characters/&#x60;  Alternate route: &#x60;/v2/fw/leaderboards/characters/&#x60;  --- This route expires daily at 11:05
    /// </remarks>
    /// <param name="datasource">The server name you would like data from (optional, default to tranquility)</param>
    /// <param name="ifNoneMatch">ETag from a previous request. A 304 will be returned if this matches the current ETag (optional)</param>
    pplx::task<std::shared_ptr<Object>> getFwLeaderboardsCharacters(
        boost::optional<utility::string_t> datasource,
        boost::optional<utility::string_t> ifNoneMatch
    );
    /// <summary>
    /// List of the top corporations in faction warfare
    /// </summary>
    /// <remarks>
    /// Top 10 leaderboard of corporations for kills and victory points separated by total, last week and yesterday  --- Alternate route: &#x60;/dev/fw/leaderboards/corporations/&#x60;  Alternate route: &#x60;/legacy/fw/leaderboards/corporations/&#x60;  Alternate route: &#x60;/v1/fw/leaderboards/corporations/&#x60;  Alternate route: &#x60;/v2/fw/leaderboards/corporations/&#x60;  --- This route expires daily at 11:05
    /// </remarks>
    /// <param name="datasource">The server name you would like data from (optional, default to tranquility)</param>
    /// <param name="ifNoneMatch">ETag from a previous request. A 304 will be returned if this matches the current ETag (optional)</param>
    pplx::task<std::shared_ptr<Object>> getFwLeaderboardsCorporations(
        boost::optional<utility::string_t> datasource,
        boost::optional<utility::string_t> ifNoneMatch
    );
    /// <summary>
    /// An overview of statistics about factions involved in faction warfare
    /// </summary>
    /// <remarks>
    /// Statistical overviews of factions involved in faction warfare  --- Alternate route: &#x60;/dev/fw/stats/&#x60;  Alternate route: &#x60;/legacy/fw/stats/&#x60;  Alternate route: &#x60;/v1/fw/stats/&#x60;  Alternate route: &#x60;/v2/fw/stats/&#x60;  --- This route expires daily at 11:05
    /// </remarks>
    /// <param name="datasource">The server name you would like data from (optional, default to tranquility)</param>
    /// <param name="ifNoneMatch">ETag from a previous request. A 304 will be returned if this matches the current ETag (optional)</param>
    pplx::task<std::vector<std::shared_ptr<Object>>> getFwStats(
        boost::optional<utility::string_t> datasource,
        boost::optional<utility::string_t> ifNoneMatch
    );
    /// <summary>
    /// Ownership of faction warfare systems
    /// </summary>
    /// <remarks>
    /// An overview of the current ownership of faction warfare solar systems  --- Alternate route: &#x60;/dev/fw/systems/&#x60;  Alternate route: &#x60;/legacy/fw/systems/&#x60;  Alternate route: &#x60;/v2/fw/systems/&#x60;  Alternate route: &#x60;/v3/fw/systems/&#x60;  --- This route is cached for up to 1800 seconds
    /// </remarks>
    /// <param name="datasource">The server name you would like data from (optional, default to tranquility)</param>
    /// <param name="ifNoneMatch">ETag from a previous request. A 304 will be returned if this matches the current ETag (optional)</param>
    pplx::task<std::vector<std::shared_ptr<Object>>> getFwSystems(
        boost::optional<utility::string_t> datasource,
        boost::optional<utility::string_t> ifNoneMatch
    );
    /// <summary>
    /// Data about which NPC factions are at war
    /// </summary>
    /// <remarks>
    /// Data about which NPC factions are at war  --- Alternate route: &#x60;/dev/fw/wars/&#x60;  Alternate route: &#x60;/legacy/fw/wars/&#x60;  Alternate route: &#x60;/v1/fw/wars/&#x60;  Alternate route: &#x60;/v2/fw/wars/&#x60;  --- This route expires daily at 11:05
    /// </remarks>
    /// <param name="datasource">The server name you would like data from (optional, default to tranquility)</param>
    /// <param name="ifNoneMatch">ETag from a previous request. A 304 will be returned if this matches the current ETag (optional)</param>
    pplx::task<std::vector<std::shared_ptr<Object>>> getFwWars(
        boost::optional<utility::string_t> datasource,
        boost::optional<utility::string_t> ifNoneMatch
    );

protected:
    std::shared_ptr<ApiClient> m_ApiClient;
};

}
}
}
}

#endif /* IO_SWAGGER_CLIENT_API_FactionWarfareApi_H_ */

