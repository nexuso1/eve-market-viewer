#include<string>
#include<utility>
#include<iostream>
#include<cpprest/json.h>
#include<set>

using namespace utility::conversions;

class ItemInfo {
public:
	inline ItemInfo(std::shared_ptr<web::json::value> info) : info_(info_) {};
	void print(int width = 18);

private:
	std::shared_ptr<web::json::value> info_;
};
