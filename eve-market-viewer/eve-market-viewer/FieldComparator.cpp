#include "Interface.h"

using namespace io::swagger::client::api;
using namespace std;
using namespace utility::conversions;

long convert_to_number(const web::json::value& field) {
	// Converts a json number to value, if possible
	try {
		return field.as_number().to_int64();
	}

	catch (web::json::json_exception e) {
		auto temp = to_utf8string(field.as_string());
		try {
			// Might still be a number
			return std::stol(temp);
		}

		catch (exception e) {
			throw(e);
		}
	}
}

bool FieldComparator::operator()(const std::shared_ptr<web::json::value>& val1, const std::shared_ptr<web::json::value>& val2) {
	// Compare 2 fields in a json

	bool result = false;
	if (field_t_ == field_type::alphabetical) {
		auto field1 = to_utf8string(val1->at(field_).as_string());
		auto field2 = to_utf8string(val2->at(field_).as_string());
		int temp = (field1.compare(field2));
		if (temp == 0) {
			return false;
		}

		else if (temp > 0) {
			return (sort_t_ == sort_type::ascending) ? false : true;
		}

		else {
			return (sort_t_ == sort_type::ascending) ? false : true;
		}
	}

	else if (field_t_ == field_type::numerical) {
		auto field1 = convert_to_number(val1->at(field_));
		auto field2 = convert_to_number(val2->at(field_));
		return (sort_t_ == sort_type::ascending) ? field1 < field2 : field1 > field2;
	}

	else if (field_t_ == field_type::range) {
		string field_str1;
		string field_str2;
		int64_t field1;
		int64_t field2;

		try {
			field1 = convert_to_number(val1->at(field_));
			try {
				field2 = convert_to_number(val2->at(field_));
				return (sort_t_ == sort_type::ascending) ? field1 < field2 : field1 > field2;
			}

			catch (exception e) {
				// first is a number, second is "station"/"region"
				field_str2 = to_utf8string(val2->at(field_).as_string());
				if (field_str2 == "station") {
					// smallest range
					return (sort_t_ == sort_type::ascending) ? false : true;
				}

				else if (field_str2 == "region") {
					// max range
					return (sort_t_ == sort_type::ascending) ? true : false;
				}
			}
		}
		catch (exception e) {
			// It's a string, which means its range is "station" or "region", and this is the lowest range
			field_str1 = to_utf8string(val1->at(field_).as_string());
			try {
				// second field number
				field2 = convert_to_number(val2->at(field_));

				if (field_str1 == "station") {
					// smallest range
					return (sort_t_ == sort_type::ascending) ? true : false;
				}

				else if (field_str1 == "region") {
					// max range
					return (sort_t_ == sort_type::ascending) ? false : true;
				}
			}

			catch (exception e) {
				// Both strings
				field_str2 = to_utf8string(val2->at(field_).as_string());
				if (field_str2 == field_str1) {
					return false;
				}

				else if (field_str1 == "station" && field_str2 == "region") {
					// station smaller than region
					return (sort_t_ == sort_type::ascending) ? true : false;
				}

				else {
					// first is "region", second "station"
					return (sort_t_ == sort_type::ascending) ? false : true;
				}
			}
		}
	}
}