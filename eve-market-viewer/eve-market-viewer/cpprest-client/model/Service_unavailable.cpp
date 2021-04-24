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



#include "Service_unavailable.h"

namespace io {
namespace swagger {
namespace client {
namespace model {

Service_unavailable::Service_unavailable()
{
    m_Error = utility::conversions::to_string_t("");
}

Service_unavailable::~Service_unavailable()
{
}

void Service_unavailable::validate()
{
    // TODO: implement validation
}

web::json::value Service_unavailable::toJson() const
{
    web::json::value val = web::json::value::object();

    val[utility::conversions::to_string_t("error")] = ModelBase::toJson(m_Error);

    return val;
}

void Service_unavailable::fromJson(web::json::value& val)
{
    setError(ModelBase::stringFromJson(val[utility::conversions::to_string_t("error")]));
}

void Service_unavailable::toMultipart(std::shared_ptr<MultipartFormData> multipart, const utility::string_t& prefix) const
{
    utility::string_t namePrefix = prefix;
    if(namePrefix.size() > 0 && namePrefix.substr(namePrefix.size() - 1) != utility::conversions::to_string_t("."))
    {
        namePrefix += utility::conversions::to_string_t(".");
    }

    multipart->add(ModelBase::toHttpContent(namePrefix + utility::conversions::to_string_t("error"), m_Error));
}

void Service_unavailable::fromMultiPart(std::shared_ptr<MultipartFormData> multipart, const utility::string_t& prefix)
{
    utility::string_t namePrefix = prefix;
    if(namePrefix.size() > 0 && namePrefix.substr(namePrefix.size() - 1) != utility::conversions::to_string_t("."))
    {
        namePrefix += utility::conversions::to_string_t(".");
    }

    setError(ModelBase::stringFromHttpContent(multipart->getContent(utility::conversions::to_string_t("error"))));
}

utility::string_t Service_unavailable::getError() const
{
    return m_Error;
}


void Service_unavailable::setError(utility::string_t value)
{
    m_Error = value;
    
}
}
}
}
}
