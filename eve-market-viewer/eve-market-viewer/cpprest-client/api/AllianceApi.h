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
 * AllianceApi.h
 *
 * 
 */

#ifndef IO_SWAGGER_CLIENT_API_AllianceApi_H_
#define IO_SWAGGER_CLIENT_API_AllianceApi_H_


#include "../ApiClient.h"

#include "Bad_request.h"
#include "Error_limited.h"
#include "Gateway_timeout.h"
#include "Internal_server_error.h"
#include "Object.h"
#include "Service_unavailable.h"
#include <cpprest/details/basic_types.h>

#include <boost/optional.hpp>

namespace io {
namespace swagger {
namespace client {
namespace api {

using namespace io::swagger::client::model;

class  AllianceApi
{
public:
    AllianceApi( std::shared_ptr<ApiClient> apiClient );
    virtual ~AllianceApi();
    /// <summary>
    /// List all alliances
    /// </summary>
    /// <remarks>
    /// List all active player alliances  --- Alternate route: &#x60;/dev/alliances/&#x60;  Alternate route: &#x60;/legacy/alliances/&#x60;  Alternate route: &#x60;/v1/alliances/&#x60;  Alternate route: &#x60;/v2/alliances/&#x60;  --- This route is cached for up to 3600 seconds
    /// </remarks>
    /// <param name="datasource">The server name you would like data from (optional, default to tranquility)</param>
    /// <param name="ifNoneMatch">ETag from a previous request. A 304 will be returned if this matches the current ETag (optional)</param>
    pplx::task<std::vector<int32_t>> getAlliances(
        boost::optional<utility::string_t> datasource,
        boost::optional<utility::string_t> ifNoneMatch
    );
    /// <summary>
    /// Get alliance information
    /// </summary>
    /// <remarks>
    /// Public information about an alliance  --- Alternate route: &#x60;/dev/alliances/{alliance_id}/&#x60;  Alternate route: &#x60;/legacy/alliances/{alliance_id}/&#x60;  Alternate route: &#x60;/v3/alliances/{alliance_id}/&#x60;  Alternate route: &#x60;/v4/alliances/{alliance_id}/&#x60;  --- This route is cached for up to 3600 seconds
    /// </remarks>
    /// <param name="allianceId">An EVE alliance ID</param>
    /// <param name="datasource">The server name you would like data from (optional, default to tranquility)</param>
    /// <param name="ifNoneMatch">ETag from a previous request. A 304 will be returned if this matches the current ETag (optional)</param>
    pplx::task<std::shared_ptr<Object>> getAlliancesAllianceId(
        int32_t allianceId,
        boost::optional<utility::string_t> datasource,
        boost::optional<utility::string_t> ifNoneMatch
    );
    /// <summary>
    /// List alliance&#39;s corporations
    /// </summary>
    /// <remarks>
    /// List all current member corporations of an alliance  --- Alternate route: &#x60;/dev/alliances/{alliance_id}/corporations/&#x60;  Alternate route: &#x60;/legacy/alliances/{alliance_id}/corporations/&#x60;  Alternate route: &#x60;/v1/alliances/{alliance_id}/corporations/&#x60;  Alternate route: &#x60;/v2/alliances/{alliance_id}/corporations/&#x60;  --- This route is cached for up to 3600 seconds
    /// </remarks>
    /// <param name="allianceId">An EVE alliance ID</param>
    /// <param name="datasource">The server name you would like data from (optional, default to tranquility)</param>
    /// <param name="ifNoneMatch">ETag from a previous request. A 304 will be returned if this matches the current ETag (optional)</param>
    pplx::task<std::vector<int32_t>> getAlliancesAllianceIdCorporations(
        int32_t allianceId,
        boost::optional<utility::string_t> datasource,
        boost::optional<utility::string_t> ifNoneMatch
    );
    /// <summary>
    /// Get alliance icon
    /// </summary>
    /// <remarks>
    /// Get the icon urls for a alliance  --- Alternate route: &#x60;/legacy/alliances/{alliance_id}/icons/&#x60;  Alternate route: &#x60;/v1/alliances/{alliance_id}/icons/&#x60;  --- This route expires daily at 11:05  --- [Diff of the upcoming changes](https://esi.evetech.net/diff/latest/dev/#GET-/alliances/{alliance_id}/icons/)
    /// </remarks>
    /// <param name="allianceId">An EVE alliance ID</param>
    /// <param name="datasource">The server name you would like data from (optional, default to tranquility)</param>
    /// <param name="ifNoneMatch">ETag from a previous request. A 304 will be returned if this matches the current ETag (optional)</param>
    pplx::task<std::shared_ptr<Object>> getAlliancesAllianceIdIcons(
        int32_t allianceId,
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

#endif /* IO_SWAGGER_CLIENT_API_AllianceApi_H_ */
