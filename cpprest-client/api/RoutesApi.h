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
 * RoutesApi.h
 *
 * 
 */

#ifndef IO_SWAGGER_CLIENT_API_RoutesApi_H_
#define IO_SWAGGER_CLIENT_API_RoutesApi_H_


#include "../ApiClient.h"

#include "Bad_request.h"
#include "Error_limited.h"
#include "Gateway_timeout.h"
#include "Internal_server_error.h"
#include "Object.h"
#include "Service_unavailable.h"
#include <vector>
#include <cpprest/details/basic_types.h>

#include <boost/optional.hpp>

namespace io {
namespace swagger {
namespace client {
namespace api {

using namespace io::swagger::client::model;

class  RoutesApi
{
public:
    RoutesApi( std::shared_ptr<ApiClient> apiClient );
    virtual ~RoutesApi();
    /// <summary>
    /// Get route
    /// </summary>
    /// <remarks>
    /// Get the systems between origin and destination  --- Alternate route: &#x60;/dev/route/{origin}/{destination}/&#x60;  Alternate route: &#x60;/legacy/route/{origin}/{destination}/&#x60;  Alternate route: &#x60;/v1/route/{origin}/{destination}/&#x60;  --- This route is cached for up to 86400 seconds
    /// </remarks>
    /// <param name="destination">destination solar system ID</param>
    /// <param name="origin">origin solar system ID</param>
    /// <param name="avoid">avoid solar system ID(s) (optional)</param>
    /// <param name="connections">connected solar system pairs (optional)</param>
    /// <param name="datasource">The server name you would like data from (optional, default to tranquility)</param>
    /// <param name="flag">route security preference (optional, default to shortest)</param>
    /// <param name="ifNoneMatch">ETag from a previous request. A 304 will be returned if this matches the current ETag (optional)</param>
    pplx::task<std::vector<int32_t>> getRouteOriginDestination(
        int32_t destination,
        int32_t origin,
        boost::optional<std::vector<int32_t>> avoid,
        boost::optional<std::vector<std::vector<int32_t>>> connections,
        boost::optional<utility::string_t> datasource,
        boost::optional<utility::string_t> flag,
        boost::optional<utility::string_t> ifNoneMatch
    );

protected:
    std::shared_ptr<ApiClient> m_ApiClient;
};

}
}
}
}

#endif /* IO_SWAGGER_CLIENT_API_RoutesApi_H_ */

