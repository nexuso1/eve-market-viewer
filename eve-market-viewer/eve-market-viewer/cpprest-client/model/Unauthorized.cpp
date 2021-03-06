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



#include "Unauthorized.h"

namespace io {
namespace swagger {
namespace client {
namespace model {

Unauthorized::Unauthorized()
{
    m_Error = utility::conversions::to_string_t("");
}

Unauthorized::~Unauthorized()
{
}

void Unauthorized::validate()
{
    // TODO: implement validation
}

web::json::value Unauthorized::toJson() const
{
    web::json::value val = web::json::value::object();

    val[utility::conversions::to_string_t("error")] = ModelBase::toJson(m_Error);

    return val;
}

void Unauthorized::fromJson(web::json::value& val)
{
    setError(ModelBase::stringFromJson(val[utility::conversions::to_string_t("error")]));
}

void Unauthorized::toMultipart(std::shared_ptr<MultipartFormData> multipart, const utility::string_t& prefix) const
{
    utility::string_t namePrefix = prefix;
    if(namePrefix.size() > 0 && namePrefix.substr(namePrefix.size() - 1) != utility::conversions::to_string_t("."))
    {
        namePrefix += utility::conversions::to_string_t(".");
    }

    multipart->add(ModelBase::toHttpContent(namePrefix + utility::conversions::to_string_t("error"), m_Error));
}

void Unauthorized::fromMultiPart(std::shared_ptr<MultipartFormData> multipart, const utility::string_t& prefix)
{
    utility::string_t namePrefix = prefix;
    if(namePrefix.size() > 0 && namePrefix.substr(namePrefix.size() - 1) != utility::conversions::to_string_t("."))
    {
        namePrefix += utility::conversions::to_string_t(".");
    }

    setError(ModelBase::stringFromHttpContent(multipart->getContent(utility::conversions::to_string_t("error"))));
}

utility::string_t Unauthorized::getError() const
{
    return m_Error;
}


void Unauthorized::setError(utility::string_t value)
{
    m_Error = value;
    
}
}
}
}
}

