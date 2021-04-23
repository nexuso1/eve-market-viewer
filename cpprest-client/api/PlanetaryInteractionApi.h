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
 * PlanetaryInteractionApi.h
 *
 * 
 */

#ifndef IO_SWAGGER_CLIENT_API_PlanetaryInteractionApi_H_
#define IO_SWAGGER_CLIENT_API_PlanetaryInteractionApi_H_


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

class  PlanetaryInteractionApi
{
public:
    PlanetaryInteractionApi( std::shared_ptr<ApiClient> apiClient );
    virtual ~PlanetaryInteractionApi();
    /// <summary>
    /// Get colonies
    /// </summary>
    /// <remarks>
    /// Returns a list of all planetary colonies owned by a character.  --- Alternate route: &#x60;/dev/characters/{character_id}/planets/&#x60;  Alternate route: &#x60;/legacy/characters/{character_id}/planets/&#x60;  Alternate route: &#x60;/v1/characters/{character_id}/planets/&#x60;  --- This route is cached for up to 600 seconds
    /// </remarks>
    /// <param name="characterId">An EVE character ID</param>
    /// <param name="datasource">The server name you would like data from (optional, default to tranquility)</param>
    /// <param name="ifNoneMatch">ETag from a previous request. A 304 will be returned if this matches the current ETag (optional)</param>
    /// <param name="token">Access token to use if unable to set a header (optional)</param>
    pplx::task<std::vector<std::shared_ptr<Object>>> getCharactersCharacterIdPlanets(
        int32_t characterId,
        boost::optional<utility::string_t> datasource,
        boost::optional<utility::string_t> ifNoneMatch,
        boost::optional<utility::string_t> token
    );
    /// <summary>
    /// Get colony layout
    /// </summary>
    /// <remarks>
    /// Returns full details on the layout of a single planetary colony, including links, pins and routes. Note: Planetary information is only recalculated when the colony is viewed through the client. Information will not update until this criteria is met.  --- Alternate route: &#x60;/dev/characters/{character_id}/planets/{planet_id}/&#x60;  Alternate route: &#x60;/v3/characters/{character_id}/planets/{planet_id}/&#x60; 
    /// </remarks>
    /// <param name="characterId">An EVE character ID</param>
    /// <param name="planetId">Planet id of the target planet</param>
    /// <param name="datasource">The server name you would like data from (optional, default to tranquility)</param>
    /// <param name="token">Access token to use if unable to set a header (optional)</param>
    pplx::task<std::shared_ptr<Object>> getCharactersCharacterIdPlanetsPlanetId(
        int32_t characterId,
        int32_t planetId,
        boost::optional<utility::string_t> datasource,
        boost::optional<utility::string_t> token
    );
    /// <summary>
    /// List corporation customs offices
    /// </summary>
    /// <remarks>
    /// List customs offices owned by a corporation  --- Alternate route: &#x60;/dev/corporations/{corporation_id}/customs_offices/&#x60;  Alternate route: &#x60;/legacy/corporations/{corporation_id}/customs_offices/&#x60;  Alternate route: &#x60;/v1/corporations/{corporation_id}/customs_offices/&#x60;  --- This route is cached for up to 3600 seconds  --- Requires one of the following EVE corporation role(s): Director 
    /// </remarks>
    /// <param name="corporationId">An EVE corporation ID</param>
    /// <param name="datasource">The server name you would like data from (optional, default to tranquility)</param>
    /// <param name="ifNoneMatch">ETag from a previous request. A 304 will be returned if this matches the current ETag (optional)</param>
    /// <param name="page">Which page of results to return (optional, default to 1)</param>
    /// <param name="token">Access token to use if unable to set a header (optional)</param>
    pplx::task<std::vector<std::shared_ptr<Object>>> getCorporationsCorporationIdCustomsOffices(
        int32_t corporationId,
        boost::optional<utility::string_t> datasource,
        boost::optional<utility::string_t> ifNoneMatch,
        boost::optional<int32_t> page,
        boost::optional<utility::string_t> token
    );
    /// <summary>
    /// Get schematic information
    /// </summary>
    /// <remarks>
    /// Get information on a planetary factory schematic  --- Alternate route: &#x60;/dev/universe/schematics/{schematic_id}/&#x60;  Alternate route: &#x60;/legacy/universe/schematics/{schematic_id}/&#x60;  Alternate route: &#x60;/v1/universe/schematics/{schematic_id}/&#x60;  --- This route is cached for up to 3600 seconds
    /// </remarks>
    /// <param name="schematicId">A PI schematic ID</param>
    /// <param name="datasource">The server name you would like data from (optional, default to tranquility)</param>
    /// <param name="ifNoneMatch">ETag from a previous request. A 304 will be returned if this matches the current ETag (optional)</param>
    pplx::task<std::shared_ptr<Object>> getUniverseSchematicsSchematicId(
        int32_t schematicId,
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

#endif /* IO_SWAGGER_CLIENT_API_PlanetaryInteractionApi_H_ */

