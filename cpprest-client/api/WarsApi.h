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
 * WarsApi.h
 *
 * 
 */

#ifndef IO_SWAGGER_CLIENT_API_WarsApi_H_
#define IO_SWAGGER_CLIENT_API_WarsApi_H_


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

class  WarsApi
{
public:
    WarsApi( std::shared_ptr<ApiClient> apiClient );
    virtual ~WarsApi();
    /// <summary>
    /// List wars
    /// </summary>
    /// <remarks>
    /// Return a list of wars  --- Alternate route: &#x60;/dev/wars/&#x60;  Alternate route: &#x60;/legacy/wars/&#x60;  Alternate route: &#x60;/v1/wars/&#x60;  --- This route is cached for up to 3600 seconds
    /// </remarks>
    /// <param name="datasource">The server name you would like data from (optional, default to tranquility)</param>
    /// <param name="ifNoneMatch">ETag from a previous request. A 304 will be returned if this matches the current ETag (optional)</param>
    /// <param name="maxWarId">Only return wars with ID smaller than this (optional)</param>
    pplx::task<std::vector<int32_t>> getWars(
        boost::optional<utility::string_t> datasource,
        boost::optional<utility::string_t> ifNoneMatch,
        boost::optional<int32_t> maxWarId
    );
    /// <summary>
    /// Get war information
    /// </summary>
    /// <remarks>
    /// Return details about a war  --- Alternate route: &#x60;/dev/wars/{war_id}/&#x60;  Alternate route: &#x60;/legacy/wars/{war_id}/&#x60;  Alternate route: &#x60;/v1/wars/{war_id}/&#x60;  --- This route is cached for up to 3600 seconds
    /// </remarks>
    /// <param name="warId">ID for a war</param>
    /// <param name="datasource">The server name you would like data from (optional, default to tranquility)</param>
    /// <param name="ifNoneMatch">ETag from a previous request. A 304 will be returned if this matches the current ETag (optional)</param>
    pplx::task<std::shared_ptr<Object>> getWarsWarId(
        int32_t warId,
        boost::optional<utility::string_t> datasource,
        boost::optional<utility::string_t> ifNoneMatch
    );
    /// <summary>
    /// List kills for a war
    /// </summary>
    /// <remarks>
    /// Return a list of kills related to a war  --- Alternate route: &#x60;/dev/wars/{war_id}/killmails/&#x60;  Alternate route: &#x60;/legacy/wars/{war_id}/killmails/&#x60;  Alternate route: &#x60;/v1/wars/{war_id}/killmails/&#x60;  --- This route is cached for up to 3600 seconds
    /// </remarks>
    /// <param name="warId">A valid war ID</param>
    /// <param name="datasource">The server name you would like data from (optional, default to tranquility)</param>
    /// <param name="ifNoneMatch">ETag from a previous request. A 304 will be returned if this matches the current ETag (optional)</param>
    /// <param name="page">Which page of results to return (optional, default to 1)</param>
    pplx::task<std::vector<std::shared_ptr<Object>>> getWarsWarIdKillmails(
        int32_t warId,
        boost::optional<utility::string_t> datasource,
        boost::optional<utility::string_t> ifNoneMatch,
        boost::optional<int32_t> page
    );

protected:
    std::shared_ptr<ApiClient> m_ApiClient;
};

}
}
}
}

#endif /* IO_SWAGGER_CLIENT_API_WarsApi_H_ */

