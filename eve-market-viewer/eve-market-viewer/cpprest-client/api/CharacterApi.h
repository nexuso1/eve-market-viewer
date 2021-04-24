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
 * CharacterApi.h
 *
 * 
 */

#ifndef IO_SWAGGER_CLIENT_API_CharacterApi_H_
#define IO_SWAGGER_CLIENT_API_CharacterApi_H_


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

class  CharacterApi
{
public:
    CharacterApi( std::shared_ptr<ApiClient> apiClient );
    virtual ~CharacterApi();
    /// <summary>
    /// Get character&#39;s public information
    /// </summary>
    /// <remarks>
    /// Public information about a character  --- Alternate route: &#x60;/dev/characters/{character_id}/&#x60;  Alternate route: &#x60;/v4/characters/{character_id}/&#x60;  --- This route is cached for up to 86400 seconds
    /// </remarks>
    /// <param name="characterId">An EVE character ID</param>
    /// <param name="datasource">The server name you would like data from (optional, default to tranquility)</param>
    /// <param name="ifNoneMatch">ETag from a previous request. A 304 will be returned if this matches the current ETag (optional)</param>
    pplx::task<std::shared_ptr<Object>> getCharactersCharacterId(
        int32_t characterId,
        boost::optional<utility::string_t> datasource,
        boost::optional<utility::string_t> ifNoneMatch
    );
    /// <summary>
    /// Get agents research
    /// </summary>
    /// <remarks>
    /// Return a list of agents research information for a character. The formula for finding the current research points with an agent is: currentPoints &#x3D; remainderPoints + pointsPerDay * days(currentTime - researchStartDate)  --- Alternate route: &#x60;/legacy/characters/{character_id}/agents_research/&#x60;  Alternate route: &#x60;/v1/characters/{character_id}/agents_research/&#x60;  --- This route is cached for up to 3600 seconds
    /// </remarks>
    /// <param name="characterId">An EVE character ID</param>
    /// <param name="datasource">The server name you would like data from (optional, default to tranquility)</param>
    /// <param name="ifNoneMatch">ETag from a previous request. A 304 will be returned if this matches the current ETag (optional)</param>
    /// <param name="token">Access token to use if unable to set a header (optional)</param>
    pplx::task<std::vector<std::shared_ptr<Object>>> getCharactersCharacterIdAgentsResearch(
        int32_t characterId,
        boost::optional<utility::string_t> datasource,
        boost::optional<utility::string_t> ifNoneMatch,
        boost::optional<utility::string_t> token
    );
    /// <summary>
    /// Get blueprints
    /// </summary>
    /// <remarks>
    /// Return a list of blueprints the character owns  --- Alternate route: &#x60;/v2/characters/{character_id}/blueprints/&#x60;  --- This route is cached for up to 3600 seconds
    /// </remarks>
    /// <param name="characterId">An EVE character ID</param>
    /// <param name="datasource">The server name you would like data from (optional, default to tranquility)</param>
    /// <param name="ifNoneMatch">ETag from a previous request. A 304 will be returned if this matches the current ETag (optional)</param>
    /// <param name="page">Which page of results to return (optional, default to 1)</param>
    /// <param name="token">Access token to use if unable to set a header (optional)</param>
    pplx::task<std::vector<std::shared_ptr<Object>>> getCharactersCharacterIdBlueprints(
        int32_t characterId,
        boost::optional<utility::string_t> datasource,
        boost::optional<utility::string_t> ifNoneMatch,
        boost::optional<int32_t> page,
        boost::optional<utility::string_t> token
    );
    /// <summary>
    /// Get corporation history
    /// </summary>
    /// <remarks>
    /// Get a list of all the corporations a character has been a member of  --- Alternate route: &#x60;/legacy/characters/{character_id}/corporationhistory/&#x60;  Alternate route: &#x60;/v1/characters/{character_id}/corporationhistory/&#x60;  --- This route is cached for up to 86400 seconds
    /// </remarks>
    /// <param name="characterId">An EVE character ID</param>
    /// <param name="datasource">The server name you would like data from (optional, default to tranquility)</param>
    /// <param name="ifNoneMatch">ETag from a previous request. A 304 will be returned if this matches the current ETag (optional)</param>
    pplx::task<std::vector<std::shared_ptr<Object>>> getCharactersCharacterIdCorporationhistory(
        int32_t characterId,
        boost::optional<utility::string_t> datasource,
        boost::optional<utility::string_t> ifNoneMatch
    );
    /// <summary>
    /// Get jump fatigue
    /// </summary>
    /// <remarks>
    /// Return a character&#39;s jump activation and fatigue information  --- Alternate route: &#x60;/legacy/characters/{character_id}/fatigue/&#x60;  Alternate route: &#x60;/v1/characters/{character_id}/fatigue/&#x60;  --- This route is cached for up to 300 seconds
    /// </remarks>
    /// <param name="characterId">An EVE character ID</param>
    /// <param name="datasource">The server name you would like data from (optional, default to tranquility)</param>
    /// <param name="ifNoneMatch">ETag from a previous request. A 304 will be returned if this matches the current ETag (optional)</param>
    /// <param name="token">Access token to use if unable to set a header (optional)</param>
    pplx::task<std::shared_ptr<Object>> getCharactersCharacterIdFatigue(
        int32_t characterId,
        boost::optional<utility::string_t> datasource,
        boost::optional<utility::string_t> ifNoneMatch,
        boost::optional<utility::string_t> token
    );
    /// <summary>
    /// Get medals
    /// </summary>
    /// <remarks>
    /// Return a list of medals the character has  --- Alternate route: &#x60;/legacy/characters/{character_id}/medals/&#x60;  Alternate route: &#x60;/v1/characters/{character_id}/medals/&#x60;  --- This route is cached for up to 3600 seconds
    /// </remarks>
    /// <param name="characterId">An EVE character ID</param>
    /// <param name="datasource">The server name you would like data from (optional, default to tranquility)</param>
    /// <param name="ifNoneMatch">ETag from a previous request. A 304 will be returned if this matches the current ETag (optional)</param>
    /// <param name="token">Access token to use if unable to set a header (optional)</param>
    pplx::task<std::vector<std::shared_ptr<Object>>> getCharactersCharacterIdMedals(
        int32_t characterId,
        boost::optional<utility::string_t> datasource,
        boost::optional<utility::string_t> ifNoneMatch,
        boost::optional<utility::string_t> token
    );
    /// <summary>
    /// Get character notifications
    /// </summary>
    /// <remarks>
    /// Return character notifications  --- Alternate route: &#x60;/dev/characters/{character_id}/notifications/&#x60;  Alternate route: &#x60;/v5/characters/{character_id}/notifications/&#x60;  Alternate route: &#x60;/v6/characters/{character_id}/notifications/&#x60;  --- This route is cached for up to 600 seconds
    /// </remarks>
    /// <param name="characterId">An EVE character ID</param>
    /// <param name="datasource">The server name you would like data from (optional, default to tranquility)</param>
    /// <param name="ifNoneMatch">ETag from a previous request. A 304 will be returned if this matches the current ETag (optional)</param>
    /// <param name="token">Access token to use if unable to set a header (optional)</param>
    pplx::task<std::vector<std::shared_ptr<Object>>> getCharactersCharacterIdNotifications(
        int32_t characterId,
        boost::optional<utility::string_t> datasource,
        boost::optional<utility::string_t> ifNoneMatch,
        boost::optional<utility::string_t> token
    );
    /// <summary>
    /// Get new contact notifications
    /// </summary>
    /// <remarks>
    /// Return notifications about having been added to someone&#39;s contact list  --- Alternate route: &#x60;/legacy/characters/{character_id}/notifications/contacts/&#x60;  Alternate route: &#x60;/v1/characters/{character_id}/notifications/contacts/&#x60;  --- This route is cached for up to 600 seconds
    /// </remarks>
    /// <param name="characterId">An EVE character ID</param>
    /// <param name="datasource">The server name you would like data from (optional, default to tranquility)</param>
    /// <param name="ifNoneMatch">ETag from a previous request. A 304 will be returned if this matches the current ETag (optional)</param>
    /// <param name="token">Access token to use if unable to set a header (optional)</param>
    pplx::task<std::vector<std::shared_ptr<Object>>> getCharactersCharacterIdNotificationsContacts(
        int32_t characterId,
        boost::optional<utility::string_t> datasource,
        boost::optional<utility::string_t> ifNoneMatch,
        boost::optional<utility::string_t> token
    );
    /// <summary>
    /// Get character portraits
    /// </summary>
    /// <remarks>
    /// Get portrait urls for a character  --- Alternate route: &#x60;/dev/characters/{character_id}/portrait/&#x60;  Alternate route: &#x60;/v2/characters/{character_id}/portrait/&#x60;  Alternate route: &#x60;/v3/characters/{character_id}/portrait/&#x60;  --- This route expires daily at 11:05
    /// </remarks>
    /// <param name="characterId">An EVE character ID</param>
    /// <param name="datasource">The server name you would like data from (optional, default to tranquility)</param>
    /// <param name="ifNoneMatch">ETag from a previous request. A 304 will be returned if this matches the current ETag (optional)</param>
    pplx::task<std::shared_ptr<Object>> getCharactersCharacterIdPortrait(
        int32_t characterId,
        boost::optional<utility::string_t> datasource,
        boost::optional<utility::string_t> ifNoneMatch
    );
    /// <summary>
    /// Get character corporation roles
    /// </summary>
    /// <remarks>
    /// Returns a character&#39;s corporation roles  --- Alternate route: &#x60;/v2/characters/{character_id}/roles/&#x60;  --- This route is cached for up to 3600 seconds
    /// </remarks>
    /// <param name="characterId">An EVE character ID</param>
    /// <param name="datasource">The server name you would like data from (optional, default to tranquility)</param>
    /// <param name="ifNoneMatch">ETag from a previous request. A 304 will be returned if this matches the current ETag (optional)</param>
    /// <param name="token">Access token to use if unable to set a header (optional)</param>
    pplx::task<std::shared_ptr<Object>> getCharactersCharacterIdRoles(
        int32_t characterId,
        boost::optional<utility::string_t> datasource,
        boost::optional<utility::string_t> ifNoneMatch,
        boost::optional<utility::string_t> token
    );
    /// <summary>
    /// Get standings
    /// </summary>
    /// <remarks>
    /// Return character standings from agents, NPC corporations, and factions  --- Alternate route: &#x60;/legacy/characters/{character_id}/standings/&#x60;  Alternate route: &#x60;/v1/characters/{character_id}/standings/&#x60;  --- This route is cached for up to 3600 seconds
    /// </remarks>
    /// <param name="characterId">An EVE character ID</param>
    /// <param name="datasource">The server name you would like data from (optional, default to tranquility)</param>
    /// <param name="ifNoneMatch">ETag from a previous request. A 304 will be returned if this matches the current ETag (optional)</param>
    /// <param name="token">Access token to use if unable to set a header (optional)</param>
    pplx::task<std::vector<std::shared_ptr<Object>>> getCharactersCharacterIdStandings(
        int32_t characterId,
        boost::optional<utility::string_t> datasource,
        boost::optional<utility::string_t> ifNoneMatch,
        boost::optional<utility::string_t> token
    );
    /// <summary>
    /// Get character corporation titles
    /// </summary>
    /// <remarks>
    /// Returns a character&#39;s titles  --- Alternate route: &#x60;/legacy/characters/{character_id}/titles/&#x60;  Alternate route: &#x60;/v1/characters/{character_id}/titles/&#x60;  --- This route is cached for up to 3600 seconds
    /// </remarks>
    /// <param name="characterId">An EVE character ID</param>
    /// <param name="datasource">The server name you would like data from (optional, default to tranquility)</param>
    /// <param name="ifNoneMatch">ETag from a previous request. A 304 will be returned if this matches the current ETag (optional)</param>
    /// <param name="token">Access token to use if unable to set a header (optional)</param>
    pplx::task<std::vector<std::shared_ptr<Object>>> getCharactersCharacterIdTitles(
        int32_t characterId,
        boost::optional<utility::string_t> datasource,
        boost::optional<utility::string_t> ifNoneMatch,
        boost::optional<utility::string_t> token
    );
    /// <summary>
    /// Character affiliation
    /// </summary>
    /// <remarks>
    /// Bulk lookup of character IDs to corporation, alliance and faction  --- Alternate route: &#x60;/legacy/characters/affiliation/&#x60;  Alternate route: &#x60;/v1/characters/affiliation/&#x60;  --- This route is cached for up to 3600 seconds  --- [Diff of the upcoming changes](https://esi.evetech.net/diff/latest/dev/#POST-/characters/affiliation/)
    /// </remarks>
    /// <param name="characters">The character IDs to fetch affiliations for. All characters must exist, or none will be returned</param>
    /// <param name="datasource">The server name you would like data from (optional, default to tranquility)</param>
    pplx::task<std::vector<std::shared_ptr<Object>>> postCharactersAffiliation(
        std::vector<int32_t> characters,
        boost::optional<utility::string_t> datasource
    );
    /// <summary>
    /// Calculate a CSPA charge cost
    /// </summary>
    /// <remarks>
    /// Takes a source character ID in the url and a set of target character ID&#39;s in the body, returns a CSPA charge cost  --- Alternate route: &#x60;/v4/characters/{character_id}/cspa/&#x60; 
    /// </remarks>
    /// <param name="characterId">An EVE character ID</param>
    /// <param name="characters">The target characters to calculate the charge for</param>
    /// <param name="datasource">The server name you would like data from (optional, default to tranquility)</param>
    /// <param name="token">Access token to use if unable to set a header (optional)</param>
    pplx::task<float> postCharactersCharacterIdCspa(
        int32_t characterId,
        std::vector<int32_t> characters,
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

#endif /* IO_SWAGGER_CLIENT_API_CharacterApi_H_ */
