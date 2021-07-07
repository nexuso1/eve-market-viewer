#include "Interface.h"

void History::sort(const utility::string_t& field, sort_type sort_t, field_type field_t) {
	FieldComparator cmp(field, field_t, sort_t);
	std::sort(type_history_.begin(), type_history_.end(), cmp);
}

void History::print(int width) {
	main_interface_.printer_->print_head(descriptions_, width);
	main_interface_.printer_->print_line(descriptions_, width);
	main_interface_.printer_->print_json_vector(type_history_, descriptions_, {}, width);
}