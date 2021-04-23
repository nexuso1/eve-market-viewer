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
 * ContactsApi.h
 *
 * 
 */

#ifndef IO_SWAGGER_CLIENT_API_ContactsApi_H_
#define IO_SWAGGER_CLIENT_API_ContactsApi_H_


#include "../ApiClient.h"

#include "Bad_request.h"
#include "Error_limited.h"
#include "Forbidden.h"
#include "Gateway_timeout.h"
#include "Internal_server_error.h"
#include "Object.h"
#include "Service_unavailable.h"
#include "Unauthorized.h"
#include <vector>
#include <cpprest/details/basic_types.h>

#include <boost/optional.hpp>

namespace io {
namespace swagger {
namespace client {
namespace api {

using namespace io::swagger::client::model;

class  ContactsApi
{
public:
    ContactsApi( std::shared_ptr<ApiClient> apiClient );
    virtual ~ContactsApi();
    /// <summary>
    /// Delete contacts
    /// </summary>
    /// <remarks>
    /// Bulk delete contacts  --- Alternate route: &#x60;/dev/characters/{character_id}/contacts/&#x60;  Alternate route: &#x60;/v2/characters/{character_id}/contacts/&#x60; 
    /// </remarks>
    /// <param name="characterId">An EVE character ID</param>
    /// <param name="contactIds">A list of contacts to delete</param>
    /// <param name="datasource">The server name you would like data from (optional, default to tranquility)</param>
    /// <param name="token">Access token to use if unable to set a header (optional)</param>
    pplx::task<void> deleteCharactersCharacterIdContacts(
        int32_t characterId,
        std::vector<int32_t> contactIds,
        boost::optional<utility::string_t> datasource,
        boost::optional<utility::string_t> token
    );
    /// <summary>
    /// Get alliance contacts
    /// </summary>
    /// <remarks>
    /// Return contacts of an alliance  --- Alternate route: &#x60;/dev/alliances/{alliance_id}/contacts/&#x60;  Alternate route: &#x60;/v2/alliances/{alliance_id}/contacts/&#x60;  --- This route is cached for up to 300 seconds
    /// </remarks>
    /// <param name="allianceId">An EVE alliance ID</param>
    /// <param name="datasource">The server name you would like data from (optional, default to tranquility)</param>
    /// <param name="ifNoneMatch">ETag from a previous request. A 304 will be returned if this matches the current ETag (optional)</param>
    /// <param name="page">Which page of results to return (optional, default to 1)</param>
    /// <param name="token">Access token to use if unable to set a header (optional)</param>
    pplx::task<std::vector<std::shared_ptr<Object>>> getAlliancesAllianceIdContacts(
        int32_t allianceId,
        boost::optional<utility::string_t> datasource,
        boost::optional<utility::string_t> ifNoneMatch,
        boost::optional<int32_t> page,
        boost::optional<utility::string_t> token
    );
    /// <summary>
    /// Get alliance contact labels
    /// </summary>
    /// <remarks>
    /// Return custom labels for an alliance&#39;s contacts  --- Alternate route: &#x60;/dev/alliances/{alliance_id}/contacts/labels/&#x60;  Alternate route: &#x60;/legacy/alliances/{alliance_id}/contacts/labels/&#x60;  Alternate route: &#x60;/v1/alliances/{alliance_id}/contacts/labels/&#x60;  --- This route is cached for up to 300 seconds
    /// </remarks>
    /// <param name="allianceId">An EVE alliance ID</param>
    /// <param name="datasource">The server name you would like data from (optional, default to tranquility)</param>
    /// <param name="ifNoneMatch">ETag from a previous request. A 304 will be returned if this matches the current ETag (optional)</param>
    /// <param name="token">Access token to use if unable to set a header (optional)</param>
    pplx::task<std::vector<std::shared_ptr<Object>>> getAlliancesAllianceIdContactsLabels(
        int32_t allianceId,
        boost::optional<utility::string_t> datasource,
        boost::optional<utility::string_t> ifNoneMatch,
        boost::optional<utility::string_t> token
    );
    /// <summary>
    /// Get contacts
    /// </summary>
    /// <remarks>
    /// Return contacts of a character  --- Alternate route: &#x60;/dev/characters/{character_id}/contacts/&#x60;  Alternate route: &#x60;/v2/characters/{character_id}/contacts/&#x60;  --- This route is cached for up to 300 seconds
    /// </remarks>
    /// <param name="characterId">An EVE character ID</param>
    /// <param name="datasource">The server name you would like data from (optional, default to tranquility)</param>
    /// <param name="ifNoneMatch">ETag from a previous request. A 304 will be returned if this matches the current ETag (optional)</param>
    /// <param name="page">Which page of results to return (optional, default to 1)</param>
    /// <param name="token">Access token to use if unable to set a header (optional)</param>
    pplx::task<std::vector<std::shared_ptr<Object>>> getCharactersCharacterIdContacts(
        int32_t characterId,
        boost::optional<utility::string_t> datasource,
        boost::optional<utility::string_t> ifNoneMatch,
        boost::optional<int32_t> page,
        boost::optional<utility::string_t> token
    );
    /// <summary>
    /// Get contact labels
    /// </summary>
    /// <remarks>
    /// Return custom labels for a character&#39;s contacts  --- Alternate route: &#x60;/dev/characters/{character_id}/contacts/labels/&#x60;  Alternate route: &#x60;/legacy/characters/{character_id}/contacts/labels/&#x60;  Alternate route: &#x60;/v1/characters/{character_id}/contacts/labels/&#x60;  --- This route is cached for up to 300 seconds
    /// </remarks>
    /// <param name="characterId">An EVE character ID</param>
    /// <param name="datasource">The server name you would like data from (optional, default to tranquility)</param>
    /// <param name="ifNoneMatch">ETag from a previous request. A 304 will be returned if this matches the current ETag (optional)</param>
    /// <param name="token">Access token to use if unable to set a header (optional)</param>
    pplx::task<std::vector<std::shared_ptr<Object>>> getCharactersCharacterIdContactsLabels(
        int32_t characterId,
        boost::optional<utility::string_t> datasource,
        boost::optional<utility::string_t> ifNoneMatch,
        boost::optional<utility::string_t> token
    );
    /// <summary>
    /// Get corporation contacts
    /// </summary>
    /// <remarks>
    /// Return contacts of a corporation  --- Alternate route: &#x60;/dev/corporations/{corporation_id}/contacts/&#x60;  Alternate route: &#x60;/v2/corporations/{corporation_id}/contacts/&#x60;  --- This route is cached for up to 300 seconds
    /// </remarks>
    /// <param name="corporationId">An EVE corporation ID</param>
    /// <param name="datasource">The server name you would like data from (optional, default to tranquility)</param>
    /// <param name="ifNoneMatch">ETag from a previous request. A 304 will be returned if this matches the current ETag (optional)</param>
    /// <param name="page">Which page of results to return (optional, default to 1)</param>
    /// <param name="token">Access token to use if unable to set a header (optional)</param>
    pplx::task<std::vector<std::shared_ptr<Object>>> getCorporationsCorporationIdContacts(
        int32_t corporationId,
        boost::optional<utility::string_t> datasource,
        boost::optional<utility::string_t> ifNoneMatch,
        boost::optional<int32_t> page,
        boost::optional<utility::string_t> token
    );
    /// <summary>
    /// Get corporation contact labels
    /// </summary>
    /// <remarks>
    /// Return custom labels for a corporation&#39;s contacts  --- Alternate route: &#x60;/dev/corporations/{corporation_id}/contacts/labels/&#x60;  Alternate route: &#x60;/legacy/corporations/{corporation_id}/contacts/labels/&#x60;  Alternate route: &#x60;/v1/corporations/{corporation_id}/contacts/labels/&#x60;  --- This route is cached for up to 300 seconds
    /// </remarks>
    /// <param name="corporationId">An EVE corporation ID</param>
    /// <param name="datasource">The server name you would like data from (optional, default to tranquility)</param>
    /// <param name="ifNoneMatch">ETag from a previous request. A 304 will be returned if this matches the current ETag (optional)</param>
    /// <param name="token">Access token to use if unable to set a header (optional)</param>
    pplx::task<std::vector<std::shared_ptr<Object>>> getCorporationsCorporationIdContactsLabels(
        int32_t corporationId,
        boost::optional<utility::string_t> datasource,
        boost::optional<utility::string_t> ifNoneMatch,
        boost::optional<utility::string_t> token
    );
    /// <summary>
    /// Add contacts
    /// </summary>
    /// <remarks>
    /// Bulk add contacts with same settings  --- Alternate route: &#x60;/dev/characters/{character_id}/contacts/&#x60;  Alternate route: &#x60;/v2/characters/{character_id}/contacts/&#x60; 
    /// </remarks>
    /// <param name="characterId">An EVE character ID</param>
    /// <param name="contactIds">A list of contacts</param>
    /// <param name="standing">Standing for the contact</param>
    /// <param name="datasource">The server name you would like data from (optional, default to tranquility)</param>
    /// <param name="labelIds">Add custom labels to the new contact (optional)</param>
    /// <param name="token">Access token to use if unable to set a header (optional)</param>
    /// <param name="watched">Whether the contact should be watched, note this is only effective on characters (optional, default to false)</param>
    pplx::task<std::vector<int32_t>> postCharactersCharacterIdContacts(
        int32_t characterId,
        std::vector<int32_t> contactIds,
        float standing,
        boost::optional<utility::string_t> datasource,
        boost::optional<std::vector<int64_t>> labelIds,
        boost::optional<utility::string_t> token,
        boost::optional<bool> watched
    );
    /// <summary>
    /// Edit contacts
    /// </summary>
    /// <remarks>
    /// Bulk edit contacts with same settings  --- Alternate route: &#x60;/dev/characters/{character_id}/contacts/&#x60;  Alternate route: &#x60;/v2/characters/{character_id}/contacts/&#x60; 
    /// </remarks>
    /// <param name="characterId">An EVE character ID</param>
    /// <param name="contactIds">A list of contacts</param>
    /// <param name="standing">Standing for the contact</param>
    /// <param name="datasource">The server name you would like data from (optional, default to tranquility)</param>
    /// <param name="labelIds">Add custom labels to the contact (optional)</param>
    /// <param name="token">Access token to use if unable to set a header (optional)</param>
    /// <param name="watched">Whether the contact should be watched, note this is only effective on characters (optional, default to false)</param>
    pplx::task<void> putCharactersCharacterIdContacts(
        int32_t characterId,
        std::vector<int32_t> contactIds,
        float standing,
        boost::optional<utility::string_t> datasource,
        boost::optional<std::vector<int64_t>> labelIds,
        boost::optional<utility::string_t> token,
        boost::optional<bool> watched
    );

protected:
    std::shared_ptr<ApiClient> m_ApiClient;
};

}
}
}
}

#endif /* IO_SWAGGER_CLIENT_API_ContactsApi_H_ */

