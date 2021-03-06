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
 * SearchApi.h
 *
 * 
 */

#ifndef IO_SWAGGER_CLIENT_API_SearchApi_H_
#define IO_SWAGGER_CLIENT_API_SearchApi_H_


#include "../ApiClient.h"

#include "../model/Bad_request.h"
#include "../model//Error_limited.h"
#include "../model//Forbidden.h"
#include "../model/Gateway_timeout.h"
#include "../model/Internal_server_error.h"
#include "../Object.h"
#include "../model/Service_unavailable.h"
#include "../model/Unauthorized.h"
#include <cpprest/details/basic_types.h>

#include <boost/optional.hpp>

namespace io {
namespace swagger {
namespace client {
namespace api {

using namespace io::swagger::client::model;

class  SearchApi
{
public:
    SearchApi( std::shared_ptr<ApiClient> apiClient );
    virtual ~SearchApi();
    /// <summary>
    /// Search on a string
    /// </summary>
    /// <remarks>
    /// Search for entities that match a given sub-string.  --- Alternate route: &#x60;/dev/characters/{character_id}/search/&#x60;  Alternate route: &#x60;/legacy/characters/{character_id}/search/&#x60;  Alternate route: &#x60;/v3/characters/{character_id}/search/&#x60;  --- This route is cached for up to 3600 seconds
    /// </remarks>
    /// <param name="categories">Type of entities to search for</param>
    /// <param name="characterId">An EVE character ID</param>
    /// <param name="search">The string to search on</param>
    /// <param name="acceptLanguage">Language to use in the response (optional, default to en)</param>
    /// <param name="datasource">The server name you would like data from (optional, default to tranquility)</param>
    /// <param name="ifNoneMatch">ETag from a previous request. A 304 will be returned if this matches the current ETag (optional)</param>
    /// <param name="language">Language to use in the response, takes precedence over Accept-Language (optional, default to en)</param>
    /// <param name="strict">Whether the search should be a strict match (optional, default to false)</param>
    /// <param name="token">Access token to use if unable to set a header (optional)</param>
    pplx::task<std::shared_ptr<Object>> getCharactersCharacterIdSearch(
        std::vector<utility::string_t> categories,
        int32_t characterId,
        utility::string_t search,
        boost::optional<utility::string_t> acceptLanguage,
        boost::optional<utility::string_t> datasource,
        boost::optional<utility::string_t> ifNoneMatch,
        boost::optional<utility::string_t> language,
        boost::optional<bool> strict,
        boost::optional<utility::string_t> token
    );
    /// <summary>
    /// Search on a string
    /// </summary>
    /// <remarks>
    /// Search for entities that match a given sub-string.  --- Alternate route: &#x60;/dev/search/&#x60;  Alternate route: &#x60;/legacy/search/&#x60;  Alternate route: &#x60;/v2/search/&#x60;  --- This route is cached for up to 3600 seconds
    /// </remarks>
    /// <param name="categories">Type of entities to search for</param>
    /// <param name="search">The string to search on</param>
    /// <param name="acceptLanguage">Language to use in the response (optional, default to en)</param>
    /// <param name="datasource">The server name you would like data from (optional, default to tranquility)</param>
    /// <param name="ifNoneMatch">ETag from a previous request. A 304 will be returned if this matches the current ETag (optional)</param>
    /// <param name="language">Language to use in the response, takes precedence over Accept-Language (optional, default to en)</param>
    /// <param name="strict">Whether the search should be a strict match (optional, default to false)</param>
    pplx::task<std::shared_ptr<Object>> getSearch(
        std::vector<utility::string_t> categories,
        utility::string_t search,
        boost::optional<utility::string_t> acceptLanguage,
        boost::optional<utility::string_t> datasource,
        boost::optional<utility::string_t> ifNoneMatch,
        boost::optional<utility::string_t> language,
        boost::optional<bool> strict
    );

protected:
    std::shared_ptr<ApiClient> m_ApiClient;
};

}
}
}
}

#endif /* IO_SWAGGER_CLIENT_API_SearchApi_H_ */

