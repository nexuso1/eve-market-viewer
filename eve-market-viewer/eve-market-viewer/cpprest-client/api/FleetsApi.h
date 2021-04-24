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
 * FleetsApi.h
 *
 * 
 */

#ifndef IO_SWAGGER_CLIENT_API_FleetsApi_H_
#define IO_SWAGGER_CLIENT_API_FleetsApi_H_


#include "../ApiClient.h"

#include "Bad_request.h"
#include "Error_limited.h"
#include "Forbidden.h"
#include "Gateway_timeout.h"
#include "Internal_server_error.h"
#include "Invitation.h"
#include "Movement.h"
#include "Naming.h"
#include "New_settings.h"
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

class  FleetsApi
{
public:
    FleetsApi( std::shared_ptr<ApiClient> apiClient );
    virtual ~FleetsApi();
    /// <summary>
    /// Kick fleet member
    /// </summary>
    /// <remarks>
    /// Kick a fleet member  --- Alternate route: &#x60;/dev/fleets/{fleet_id}/members/{member_id}/&#x60;  Alternate route: &#x60;/legacy/fleets/{fleet_id}/members/{member_id}/&#x60;  Alternate route: &#x60;/v1/fleets/{fleet_id}/members/{member_id}/&#x60; 
    /// </remarks>
    /// <param name="fleetId">ID for a fleet</param>
    /// <param name="memberId">The character ID of a member in this fleet</param>
    /// <param name="datasource">The server name you would like data from (optional, default to tranquility)</param>
    /// <param name="token">Access token to use if unable to set a header (optional)</param>
    pplx::task<void> deleteFleetsFleetIdMembersMemberId(
        int64_t fleetId,
        int32_t memberId,
        boost::optional<utility::string_t> datasource,
        boost::optional<utility::string_t> token
    );
    /// <summary>
    /// Delete fleet squad
    /// </summary>
    /// <remarks>
    /// Delete a fleet squad, only empty squads can be deleted  --- Alternate route: &#x60;/dev/fleets/{fleet_id}/squads/{squad_id}/&#x60;  Alternate route: &#x60;/legacy/fleets/{fleet_id}/squads/{squad_id}/&#x60;  Alternate route: &#x60;/v1/fleets/{fleet_id}/squads/{squad_id}/&#x60; 
    /// </remarks>
    /// <param name="fleetId">ID for a fleet</param>
    /// <param name="squadId">The squad to delete</param>
    /// <param name="datasource">The server name you would like data from (optional, default to tranquility)</param>
    /// <param name="token">Access token to use if unable to set a header (optional)</param>
    pplx::task<void> deleteFleetsFleetIdSquadsSquadId(
        int64_t fleetId,
        int64_t squadId,
        boost::optional<utility::string_t> datasource,
        boost::optional<utility::string_t> token
    );
    /// <summary>
    /// Delete fleet wing
    /// </summary>
    /// <remarks>
    /// Delete a fleet wing, only empty wings can be deleted. The wing may contain squads, but the squads must be empty  --- Alternate route: &#x60;/dev/fleets/{fleet_id}/wings/{wing_id}/&#x60;  Alternate route: &#x60;/legacy/fleets/{fleet_id}/wings/{wing_id}/&#x60;  Alternate route: &#x60;/v1/fleets/{fleet_id}/wings/{wing_id}/&#x60; 
    /// </remarks>
    /// <param name="fleetId">ID for a fleet</param>
    /// <param name="wingId">The wing to delete</param>
    /// <param name="datasource">The server name you would like data from (optional, default to tranquility)</param>
    /// <param name="token">Access token to use if unable to set a header (optional)</param>
    pplx::task<void> deleteFleetsFleetIdWingsWingId(
        int64_t fleetId,
        int64_t wingId,
        boost::optional<utility::string_t> datasource,
        boost::optional<utility::string_t> token
    );
    /// <summary>
    /// Get character fleet info
    /// </summary>
    /// <remarks>
    /// Return the fleet ID the character is in, if any.  --- Alternate route: &#x60;/legacy/characters/{character_id}/fleet/&#x60;  Alternate route: &#x60;/v1/characters/{character_id}/fleet/&#x60;  --- This route is cached for up to 60 seconds  --- Warning: This route has an upgrade available  --- [Diff of the upcoming changes](https://esi.evetech.net/diff/latest/dev/#GET-/characters/{character_id}/fleet/)
    /// </remarks>
    /// <param name="characterId">An EVE character ID</param>
    /// <param name="datasource">The server name you would like data from (optional, default to tranquility)</param>
    /// <param name="ifNoneMatch">ETag from a previous request. A 304 will be returned if this matches the current ETag (optional)</param>
    /// <param name="token">Access token to use if unable to set a header (optional)</param>
    pplx::task<std::shared_ptr<Object>> getCharactersCharacterIdFleet(
        int32_t characterId,
        boost::optional<utility::string_t> datasource,
        boost::optional<utility::string_t> ifNoneMatch,
        boost::optional<utility::string_t> token
    );
    /// <summary>
    /// Get fleet information
    /// </summary>
    /// <remarks>
    /// Return details about a fleet  --- Alternate route: &#x60;/dev/fleets/{fleet_id}/&#x60;  Alternate route: &#x60;/legacy/fleets/{fleet_id}/&#x60;  Alternate route: &#x60;/v1/fleets/{fleet_id}/&#x60;  --- This route is cached for up to 5 seconds
    /// </remarks>
    /// <param name="fleetId">ID for a fleet</param>
    /// <param name="datasource">The server name you would like data from (optional, default to tranquility)</param>
    /// <param name="ifNoneMatch">ETag from a previous request. A 304 will be returned if this matches the current ETag (optional)</param>
    /// <param name="token">Access token to use if unable to set a header (optional)</param>
    pplx::task<std::shared_ptr<Object>> getFleetsFleetId(
        int64_t fleetId,
        boost::optional<utility::string_t> datasource,
        boost::optional<utility::string_t> ifNoneMatch,
        boost::optional<utility::string_t> token
    );
    /// <summary>
    /// Get fleet members
    /// </summary>
    /// <remarks>
    /// Return information about fleet members  --- Alternate route: &#x60;/dev/fleets/{fleet_id}/members/&#x60;  Alternate route: &#x60;/legacy/fleets/{fleet_id}/members/&#x60;  Alternate route: &#x60;/v1/fleets/{fleet_id}/members/&#x60;  --- This route is cached for up to 5 seconds
    /// </remarks>
    /// <param name="fleetId">ID for a fleet</param>
    /// <param name="acceptLanguage">Language to use in the response (optional, default to en)</param>
    /// <param name="datasource">The server name you would like data from (optional, default to tranquility)</param>
    /// <param name="ifNoneMatch">ETag from a previous request. A 304 will be returned if this matches the current ETag (optional)</param>
    /// <param name="language">Language to use in the response, takes precedence over Accept-Language (optional, default to en)</param>
    /// <param name="token">Access token to use if unable to set a header (optional)</param>
    pplx::task<std::vector<std::shared_ptr<Object>>> getFleetsFleetIdMembers(
        int64_t fleetId,
        boost::optional<utility::string_t> acceptLanguage,
        boost::optional<utility::string_t> datasource,
        boost::optional<utility::string_t> ifNoneMatch,
        boost::optional<utility::string_t> language,
        boost::optional<utility::string_t> token
    );
    /// <summary>
    /// Get fleet wings
    /// </summary>
    /// <remarks>
    /// Return information about wings in a fleet  --- Alternate route: &#x60;/dev/fleets/{fleet_id}/wings/&#x60;  Alternate route: &#x60;/legacy/fleets/{fleet_id}/wings/&#x60;  Alternate route: &#x60;/v1/fleets/{fleet_id}/wings/&#x60;  --- This route is cached for up to 5 seconds
    /// </remarks>
    /// <param name="fleetId">ID for a fleet</param>
    /// <param name="acceptLanguage">Language to use in the response (optional, default to en)</param>
    /// <param name="datasource">The server name you would like data from (optional, default to tranquility)</param>
    /// <param name="ifNoneMatch">ETag from a previous request. A 304 will be returned if this matches the current ETag (optional)</param>
    /// <param name="language">Language to use in the response, takes precedence over Accept-Language (optional, default to en)</param>
    /// <param name="token">Access token to use if unable to set a header (optional)</param>
    pplx::task<std::vector<std::shared_ptr<Object>>> getFleetsFleetIdWings(
        int64_t fleetId,
        boost::optional<utility::string_t> acceptLanguage,
        boost::optional<utility::string_t> datasource,
        boost::optional<utility::string_t> ifNoneMatch,
        boost::optional<utility::string_t> language,
        boost::optional<utility::string_t> token
    );
    /// <summary>
    /// Create fleet invitation
    /// </summary>
    /// <remarks>
    /// Invite a character into the fleet. If a character has a CSPA charge set it is not possible to invite them to the fleet using ESI  --- Alternate route: &#x60;/dev/fleets/{fleet_id}/members/&#x60;  Alternate route: &#x60;/legacy/fleets/{fleet_id}/members/&#x60;  Alternate route: &#x60;/v1/fleets/{fleet_id}/members/&#x60; 
    /// </remarks>
    /// <param name="fleetId">ID for a fleet</param>
    /// <param name="invitation">Details of the invitation</param>
    /// <param name="datasource">The server name you would like data from (optional, default to tranquility)</param>
    /// <param name="token">Access token to use if unable to set a header (optional)</param>
    pplx::task<void> postFleetsFleetIdMembers(
        int64_t fleetId,
        std::shared_ptr<Invitation> invitation,
        boost::optional<utility::string_t> datasource,
        boost::optional<utility::string_t> token
    );
    /// <summary>
    /// Create fleet wing
    /// </summary>
    /// <remarks>
    /// Create a new wing in a fleet  --- Alternate route: &#x60;/dev/fleets/{fleet_id}/wings/&#x60;  Alternate route: &#x60;/legacy/fleets/{fleet_id}/wings/&#x60;  Alternate route: &#x60;/v1/fleets/{fleet_id}/wings/&#x60; 
    /// </remarks>
    /// <param name="fleetId">ID for a fleet</param>
    /// <param name="datasource">The server name you would like data from (optional, default to tranquility)</param>
    /// <param name="token">Access token to use if unable to set a header (optional)</param>
    pplx::task<std::shared_ptr<Object>> postFleetsFleetIdWings(
        int64_t fleetId,
        boost::optional<utility::string_t> datasource,
        boost::optional<utility::string_t> token
    );
    /// <summary>
    /// Create fleet squad
    /// </summary>
    /// <remarks>
    /// Create a new squad in a fleet  --- Alternate route: &#x60;/dev/fleets/{fleet_id}/wings/{wing_id}/squads/&#x60;  Alternate route: &#x60;/legacy/fleets/{fleet_id}/wings/{wing_id}/squads/&#x60;  Alternate route: &#x60;/v1/fleets/{fleet_id}/wings/{wing_id}/squads/&#x60; 
    /// </remarks>
    /// <param name="fleetId">ID for a fleet</param>
    /// <param name="wingId">The wing_id to create squad in</param>
    /// <param name="datasource">The server name you would like data from (optional, default to tranquility)</param>
    /// <param name="token">Access token to use if unable to set a header (optional)</param>
    pplx::task<std::shared_ptr<Object>> postFleetsFleetIdWingsWingIdSquads(
        int64_t fleetId,
        int64_t wingId,
        boost::optional<utility::string_t> datasource,
        boost::optional<utility::string_t> token
    );
    /// <summary>
    /// Update fleet
    /// </summary>
    /// <remarks>
    /// Update settings about a fleet  --- Alternate route: &#x60;/dev/fleets/{fleet_id}/&#x60;  Alternate route: &#x60;/legacy/fleets/{fleet_id}/&#x60;  Alternate route: &#x60;/v1/fleets/{fleet_id}/&#x60; 
    /// </remarks>
    /// <param name="fleetId">ID for a fleet</param>
    /// <param name="newSettings">What to update for this fleet</param>
    /// <param name="datasource">The server name you would like data from (optional, default to tranquility)</param>
    /// <param name="token">Access token to use if unable to set a header (optional)</param>
    pplx::task<void> putFleetsFleetId(
        int64_t fleetId,
        std::shared_ptr<New_settings> newSettings,
        boost::optional<utility::string_t> datasource,
        boost::optional<utility::string_t> token
    );
    /// <summary>
    /// Move fleet member
    /// </summary>
    /// <remarks>
    /// Move a fleet member around  --- Alternate route: &#x60;/dev/fleets/{fleet_id}/members/{member_id}/&#x60;  Alternate route: &#x60;/legacy/fleets/{fleet_id}/members/{member_id}/&#x60;  Alternate route: &#x60;/v1/fleets/{fleet_id}/members/{member_id}/&#x60; 
    /// </remarks>
    /// <param name="fleetId">ID for a fleet</param>
    /// <param name="memberId">The character ID of a member in this fleet</param>
    /// <param name="movement">Details of the invitation</param>
    /// <param name="datasource">The server name you would like data from (optional, default to tranquility)</param>
    /// <param name="token">Access token to use if unable to set a header (optional)</param>
    pplx::task<void> putFleetsFleetIdMembersMemberId(
        int64_t fleetId,
        int32_t memberId,
        std::shared_ptr<Movement> movement,
        boost::optional<utility::string_t> datasource,
        boost::optional<utility::string_t> token
    );
    /// <summary>
    /// Rename fleet squad
    /// </summary>
    /// <remarks>
    /// Rename a fleet squad  --- Alternate route: &#x60;/dev/fleets/{fleet_id}/squads/{squad_id}/&#x60;  Alternate route: &#x60;/legacy/fleets/{fleet_id}/squads/{squad_id}/&#x60;  Alternate route: &#x60;/v1/fleets/{fleet_id}/squads/{squad_id}/&#x60; 
    /// </remarks>
    /// <param name="fleetId">ID for a fleet</param>
    /// <param name="naming">New name of the squad</param>
    /// <param name="squadId">The squad to rename</param>
    /// <param name="datasource">The server name you would like data from (optional, default to tranquility)</param>
    /// <param name="token">Access token to use if unable to set a header (optional)</param>
    pplx::task<void> putFleetsFleetIdSquadsSquadId(
        int64_t fleetId,
        std::shared_ptr<Naming> naming,
        int64_t squadId,
        boost::optional<utility::string_t> datasource,
        boost::optional<utility::string_t> token
    );
    /// <summary>
    /// Rename fleet wing
    /// </summary>
    /// <remarks>
    /// Rename a fleet wing  --- Alternate route: &#x60;/dev/fleets/{fleet_id}/wings/{wing_id}/&#x60;  Alternate route: &#x60;/legacy/fleets/{fleet_id}/wings/{wing_id}/&#x60;  Alternate route: &#x60;/v1/fleets/{fleet_id}/wings/{wing_id}/&#x60; 
    /// </remarks>
    /// <param name="fleetId">ID for a fleet</param>
    /// <param name="naming">New name of the wing</param>
    /// <param name="wingId">The wing to rename</param>
    /// <param name="datasource">The server name you would like data from (optional, default to tranquility)</param>
    /// <param name="token">Access token to use if unable to set a header (optional)</param>
    pplx::task<void> putFleetsFleetIdWingsWingId(
        int64_t fleetId,
        std::shared_ptr<Naming> naming,
        int64_t wingId,
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

#endif /* IO_SWAGGER_CLIENT_API_FleetsApi_H_ */
