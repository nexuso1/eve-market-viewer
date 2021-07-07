#include <string>
#include <utility>
#include "cpprest-client/ApiClient.h"
#include "cpprest-client/ApiConfiguration.h"
#include "cpprest-client/api/CharacterApi.h"
#include "cpprest-client/api/MarketApi.h"
#include "cpprest-client/api/AssetsApi.h"
#include "cpprest-client/api/UniverseApi.h"
#include "Interface.h"

#define PROGRAM_VERSION "0.0.1"

using namespace io::swagger::client::api;
using namespace utility::conversions;
using namespace std;

void print_welcome(ostream& out) {
	out << "Eve Market Viewer ver " << PROGRAM_VERSION << endl;
	out << "For usage type help" << endl;
}

void run(int argc, char* argv[], ostream& out, istream& in) {
	auto main_interface = MainInterface(out);
	bool end = false;
	if (argc < 2) {
		print_welcome(out);
		while (!end) {
			string line;
			getline(in, line);
			stringstream stream(line);
			main_interface.parse_command(stream, line);
		}
	}
}


int main(int argc, char* argv[]) {
	run(argc, argv, cout, cin);
}