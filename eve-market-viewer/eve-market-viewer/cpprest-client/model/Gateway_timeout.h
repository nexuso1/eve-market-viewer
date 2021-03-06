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
 * Gateway_timeout.h
 *
 * Gateway timeout model
 */

#ifndef IO_SWAGGER_CLIENT_MODEL_Gateway_timeout_H_
#define IO_SWAGGER_CLIENT_MODEL_Gateway_timeout_H_


#include "../ModelBase.h"

#include <cpprest/details/basic_types.h>

namespace io {
namespace swagger {
namespace client {
namespace model {

/// <summary>
/// Gateway timeout model
/// </summary>
class  Gateway_timeout
    : public ModelBase
{
public:
    Gateway_timeout();
    virtual ~Gateway_timeout();

    /////////////////////////////////////////////
    /// ModelBase overrides

    void validate() override;

    web::json::value toJson() const override;
    void fromJson(web::json::value& json) override;

    void toMultipart(std::shared_ptr<MultipartFormData> multipart, const utility::string_t& namePrefix) const override;
    void fromMultiPart(std::shared_ptr<MultipartFormData> multipart, const utility::string_t& namePrefix) override;

    /////////////////////////////////////////////
    /// Gateway_timeout members

    /// <summary>
    /// Gateway timeout message
    /// </summary>
    utility::string_t getError() const;
        void setError(utility::string_t value);
    /// <summary>
    /// number of seconds the request was given
    /// </summary>
    int32_t getTimeout() const;
    bool timeoutIsSet() const;
    void unsetTimeout();
    void setTimeout(int32_t value);

protected:
    utility::string_t m_Error;
        int32_t m_Timeout;
    bool m_TimeoutIsSet;
};

}
}
}
}

#endif /* IO_SWAGGER_CLIENT_MODEL_Gateway_timeout_H_ */
