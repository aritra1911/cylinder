#include <string>
#include "schema.hpp"

Schema::Schema(const std::string& name) : name(name) { }

std::string Schema::get_name(void) {
    return this->name;
}
