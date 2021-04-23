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
 * LocationApi.h
 *
 * 
 */

#ifndef IO_SWAGGER_CLIENT_API_LocationApi_H_
#define IO_SWAGGER_CLIENT_API_LocationApi_H_


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

class  LocationApi
{
public:
    LocationApi( std::shared_ptr<ApiClient> apiClient );
    virtual ~LocationApi();
    /// <summary>
    /// Get character location
    /// </summary>
    /// <remarks>
    /// Information about the characters current location. Returns the current solar system id, and also the current station or structure ID if applicable  --- Alternate route: &#x60;/dev/characters/{character_id}/location/&#x60;  Alternate route: &#x60;/legacy/characters/{character_id}/location/&#x60;  Alternate route: &#x60;/v1/characters/{character_id}/location/&#x60;  Alternate route: &#x60;/v2/characters/{character_id}/location/&#x60;  --- This route is cached for up to 5 seconds
    /// </remarks>
    /// <param name="characterId">An EVE character ID</param>
    /// <param name="datasource">The server name you would like data from (optional, default to tranquility)</param>
    /// <param name="ifNoneMatch">ETag from a previous request. A 304 will be returned if this matches the current ETag (optional)</param>
    /// <param name="token">Access token to use if unable to set a header (optional)</param>
    pplx::task<std::shared_ptr<Object>> getCharactersCharacterIdLocation(
        int32_t characterId,
        boost::optional<utility::string_t> datasource,
        boost::optional<utility::string_t> ifNoneMatch,
        boost::optional<utility::string_t> token
    );
    /// <summary>
    /// Get character online
    /// </summary>
    /// <remarks>
    /// Checks if the character is currently online  --- Alternate route: &#x60;/dev/characters/{character_id}/online/&#x60;  Alternate route: &#x60;/v2/characters/{character_id}/online/&#x60;  Alternate route: &#x60;/v3/characters/{character_id}/online/&#x60;  --- This route is cached for up to 60 seconds
    /// </remarks>
    /// <param name="characterId">An EVE character ID</param>
    /// <param name="datasource">The server name you would like data from (optional, default to tranquility)</param>
    /// <param name="ifNoneMatch">ETag from a previous request. A 304 will be returned if this matches the current ETag (optional)</param>
    /// <param name="token">Access token to use if unable to set a header (optional)</param>
    pplx::task<std::shared_ptr<Object>> getCharactersCharacterIdOnline(
        int32_t characterId,
        boost::optional<utility::string_t> datasource,
        boost::optional<utility::string_t> ifNoneMatch,
        boost::optional<utility::string_t> token
    );
    /// <summary>
    /// Get current ship
    /// </summary>
    /// <remarks>
    /// Get the current ship type, name and id  --- Alternate route: &#x60;/dev/characters/{character_id}/ship/&#x60;  Alternate route: &#x60;/legacy/characters/{character_id}/ship/&#x60;  Alternate route: &#x60;/v1/characters/{character_id}/ship/&#x60;  Alternate route: &#x60;/v2/characters/{character_id}/ship/&#x60;  --- This route is cached for up to 5 seconds
    /// </remarks>
    /// <param name="characterId">An EVE character ID</param>
    /// <param name="datasource">The server name you would like data from (optional, default to tranquility)</param>
    /// <param name="ifNoneMatch">ETag from a previous request. A 304 will be returned if this matches the current ETag (optional)</param>
    /// <param name="token">Access token to use if unable to set a header (optional)</param>
    pplx::task<std::shared_ptr<Object>> getCharactersCharacterIdShip(
        int32_t characterId,
        boost::optional<utility::string_t> datasource,
        boost::optional<utility::string_t> ifNoneMatch,
        boost::optional<utility::string_t> token
    );

protected:
    std::shared_ptr<ApiClient> m_ApiClient;
};

}
}
}
}

#endif /* IO_SWAGGER_CLIENT_API_LocationApi_H_ */

