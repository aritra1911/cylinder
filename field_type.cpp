#include <string>
#include "field_type.hpp"

AbstractField::AbstractField(const FieldType& type, const std::string& name) : type(type), name(name) { }

/* Since ~AbstractField() is declared as a pure virtual function, it needs a definition outside the `struct
 * AbstractField' anyway since there is no way to override a destructor. */
AbstractField::~AbstractField() { }
