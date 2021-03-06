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
 * SovereigntyApi.h
 *
 * 
 */

#ifndef IO_SWAGGER_CLIENT_API_SovereigntyApi_H_
#define IO_SWAGGER_CLIENT_API_SovereigntyApi_H_


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

class  SovereigntyApi
{
public:
    SovereigntyApi( std::shared_ptr<ApiClient> apiClient );
    virtual ~SovereigntyApi();
    /// <summary>
    /// List sovereignty campaigns
    /// </summary>
    /// <remarks>
    /// Shows sovereignty data for campaigns.  --- Alternate route: &#x60;/dev/sovereignty/campaigns/&#x60;  Alternate route: &#x60;/legacy/sovereignty/campaigns/&#x60;  Alternate route: &#x60;/v1/sovereignty/campaigns/&#x60;  --- This route is cached for up to 5 seconds
    /// </remarks>
    /// <param name="datasource">The server name you would like data from (optional, default to tranquility)</param>
    /// <param name="ifNoneMatch">ETag from a previous request. A 304 will be returned if this matches the current ETag (optional)</param>
    pplx::task<std::vector<std::shared_ptr<Object>>> getSovereigntyCampaigns(
        boost::optional<utility::string_t> datasource,
        boost::optional<utility::string_t> ifNoneMatch
    );
    /// <summary>
    /// List sovereignty of systems
    /// </summary>
    /// <remarks>
    /// Shows sovereignty information for solar systems  --- Alternate route: &#x60;/dev/sovereignty/map/&#x60;  Alternate route: &#x60;/legacy/sovereignty/map/&#x60;  Alternate route: &#x60;/v1/sovereignty/map/&#x60;  --- This route is cached for up to 3600 seconds
    /// </remarks>
    /// <param name="datasource">The server name you would like data from (optional, default to tranquility)</param>
    /// <param name="ifNoneMatch">ETag from a previous request. A 304 will be returned if this matches the current ETag (optional)</param>
    pplx::task<std::vector<std::shared_ptr<Object>>> getSovereigntyMap(
        boost::optional<utility::string_t> datasource,
        boost::optional<utility::string_t> ifNoneMatch
    );
    /// <summary>
    /// List sovereignty structures
    /// </summary>
    /// <remarks>
    /// Shows sovereignty data for structures.  --- Alternate route: &#x60;/dev/sovereignty/structures/&#x60;  Alternate route: &#x60;/legacy/sovereignty/structures/&#x60;  Alternate route: &#x60;/v1/sovereignty/structures/&#x60;  --- This route is cached for up to 120 seconds
    /// </remarks>
    /// <param name="datasource">The server name you would like data from (optional, default to tranquility)</param>
    /// <param name="ifNoneMatch">ETag from a previous request. A 304 will be returned if this matches the current ETag (optional)</param>
    pplx::task<std::vector<std::shared_ptr<Object>>> getSovereigntyStructures(
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

#endif /* IO_SWAGGER_CLIENT_API_SovereigntyApi_H_ */

