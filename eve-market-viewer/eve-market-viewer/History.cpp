#include "Interface.h"

void History::print(int width) {
	main_interface_.printer_->print_head(descriptions_, width);
	main_interface_.printer_->print_line(descriptions_, width);
	main_interface_.printer_->print_json_vector(type_history_, descriptions_, {}, width);
}