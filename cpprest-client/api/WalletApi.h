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
 * WalletApi.h
 *
 * 
 */

#ifndef IO_SWAGGER_CLIENT_API_WalletApi_H_
#define IO_SWAGGER_CLIENT_API_WalletApi_H_


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

class  WalletApi
{
public:
    WalletApi( std::shared_ptr<ApiClient> apiClient );
    virtual ~WalletApi();
    /// <summary>
    /// Get a character&#39;s wallet balance
    /// </summary>
    /// <remarks>
    /// Returns a character&#39;s wallet balance  --- Alternate route: &#x60;/legacy/characters/{character_id}/wallet/&#x60;  Alternate route: &#x60;/v1/characters/{character_id}/wallet/&#x60;  --- This route is cached for up to 120 seconds  --- [Diff of the upcoming changes](https://esi.evetech.net/diff/latest/dev/#GET-/characters/{character_id}/wallet/)
    /// </remarks>
    /// <param name="characterId">An EVE character ID</param>
    /// <param name="datasource">The server name you would like data from (optional, default to tranquility)</param>
    /// <param name="ifNoneMatch">ETag from a previous request. A 304 will be returned if this matches the current ETag (optional)</param>
    /// <param name="token">Access token to use if unable to set a header (optional)</param>
    pplx::task<double> getCharactersCharacterIdWallet(
        int32_t characterId,
        boost::optional<utility::string_t> datasource,
        boost::optional<utility::string_t> ifNoneMatch,
        boost::optional<utility::string_t> token
    );
    /// <summary>
    /// Get character wallet journal
    /// </summary>
    /// <remarks>
    /// Retrieve the given character&#39;s wallet journal going 30 days back  --- Alternate route: &#x60;/dev/characters/{character_id}/wallet/journal/&#x60;  Alternate route: &#x60;/v6/characters/{character_id}/wallet/journal/&#x60;  --- This route is cached for up to 3600 seconds
    /// </remarks>
    /// <param name="characterId">An EVE character ID</param>
    /// <param name="datasource">The server name you would like data from (optional, default to tranquility)</param>
    /// <param name="ifNoneMatch">ETag from a previous request. A 304 will be returned if this matches the current ETag (optional)</param>
    /// <param name="page">Which page of results to return (optional, default to 1)</param>
    /// <param name="token">Access token to use if unable to set a header (optional)</param>
    pplx::task<std::vector<std::shared_ptr<Object>>> getCharactersCharacterIdWalletJournal(
        int32_t characterId,
        boost::optional<utility::string_t> datasource,
        boost::optional<utility::string_t> ifNoneMatch,
        boost::optional<int32_t> page,
        boost::optional<utility::string_t> token
    );
    /// <summary>
    /// Get wallet transactions
    /// </summary>
    /// <remarks>
    /// Get wallet transactions of a character  --- Alternate route: &#x60;/dev/characters/{character_id}/wallet/transactions/&#x60;  Alternate route: &#x60;/legacy/characters/{character_id}/wallet/transactions/&#x60;  Alternate route: &#x60;/v1/characters/{character_id}/wallet/transactions/&#x60;  --- This route is cached for up to 3600 seconds
    /// </remarks>
    /// <param name="characterId">An EVE character ID</param>
    /// <param name="datasource">The server name you would like data from (optional, default to tranquility)</param>
    /// <param name="fromId">Only show transactions happened before the one referenced by this id (optional)</param>
    /// <param name="ifNoneMatch">ETag from a previous request. A 304 will be returned if this matches the current ETag (optional)</param>
    /// <param name="token">Access token to use if unable to set a header (optional)</param>
    pplx::task<std::vector<std::shared_ptr<Object>>> getCharactersCharacterIdWalletTransactions(
        int32_t characterId,
        boost::optional<utility::string_t> datasource,
        boost::optional<int64_t> fromId,
        boost::optional<utility::string_t> ifNoneMatch,
        boost::optional<utility::string_t> token
    );
    /// <summary>
    /// Returns a corporation&#39;s wallet balance
    /// </summary>
    /// <remarks>
    /// Get a corporation&#39;s wallets  --- Alternate route: &#x60;/dev/corporations/{corporation_id}/wallets/&#x60;  Alternate route: &#x60;/legacy/corporations/{corporation_id}/wallets/&#x60;  Alternate route: &#x60;/v1/corporations/{corporation_id}/wallets/&#x60;  --- This route is cached for up to 300 seconds  --- Requires one of the following EVE corporation role(s): Accountant, Junior_Accountant 
    /// </remarks>
    /// <param name="corporationId">An EVE corporation ID</param>
    /// <param name="datasource">The server name you would like data from (optional, default to tranquility)</param>
    /// <param name="ifNoneMatch">ETag from a previous request. A 304 will be returned if this matches the current ETag (optional)</param>
    /// <param name="token">Access token to use if unable to set a header (optional)</param>
    pplx::task<std::vector<std::shared_ptr<Object>>> getCorporationsCorporationIdWallets(
        int32_t corporationId,
        boost::optional<utility::string_t> datasource,
        boost::optional<utility::string_t> ifNoneMatch,
        boost::optional<utility::string_t> token
    );
    /// <summary>
    /// Get corporation wallet journal
    /// </summary>
    /// <remarks>
    /// Retrieve the given corporation&#39;s wallet journal for the given division going 30 days back  --- Alternate route: &#x60;/dev/corporations/{corporation_id}/wallets/{division}/journal/&#x60;  Alternate route: &#x60;/v4/corporations/{corporation_id}/wallets/{division}/journal/&#x60;  --- This route is cached for up to 3600 seconds  --- Requires one of the following EVE corporation role(s): Accountant, Junior_Accountant 
    /// </remarks>
    /// <param name="corporationId">An EVE corporation ID</param>
    /// <param name="division">Wallet key of the division to fetch journals from</param>
    /// <param name="datasource">The server name you would like data from (optional, default to tranquility)</param>
    /// <param name="ifNoneMatch">ETag from a previous request. A 304 will be returned if this matches the current ETag (optional)</param>
    /// <param name="page">Which page of results to return (optional, default to 1)</param>
    /// <param name="token">Access token to use if unable to set a header (optional)</param>
    pplx::task<std::vector<std::shared_ptr<Object>>> getCorporationsCorporationIdWalletsDivisionJournal(
        int32_t corporationId,
        int32_t division,
        boost::optional<utility::string_t> datasource,
        boost::optional<utility::string_t> ifNoneMatch,
        boost::optional<int32_t> page,
        boost::optional<utility::string_t> token
    );
    /// <summary>
    /// Get corporation wallet transactions
    /// </summary>
    /// <remarks>
    /// Get wallet transactions of a corporation  --- Alternate route: &#x60;/dev/corporations/{corporation_id}/wallets/{division}/transactions/&#x60;  Alternate route: &#x60;/legacy/corporations/{corporation_id}/wallets/{division}/transactions/&#x60;  Alternate route: &#x60;/v1/corporations/{corporation_id}/wallets/{division}/transactions/&#x60;  --- This route is cached for up to 3600 seconds  --- Requires one of the following EVE corporation role(s): Accountant, Junior_Accountant 
    /// </remarks>
    /// <param name="corporationId">An EVE corporation ID</param>
    /// <param name="division">Wallet key of the division to fetch journals from</param>
    /// <param name="datasource">The server name you would like data from (optional, default to tranquility)</param>
    /// <param name="fromId">Only show journal entries happened before the transaction referenced by this id (optional)</param>
    /// <param name="ifNoneMatch">ETag from a previous request. A 304 will be returned if this matches the current ETag (optional)</param>
    /// <param name="token">Access token to use if unable to set a header (optional)</param>
    pplx::task<std::vector<std::shared_ptr<Object>>> getCorporationsCorporationIdWalletsDivisionTransactions(
        int32_t corporationId,
        int32_t division,
        boost::optional<utility::string_t> datasource,
        boost::optional<int64_t> fromId,
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

#endif /* IO_SWAGGER_CLIENT_API_WalletApi_H_ */

