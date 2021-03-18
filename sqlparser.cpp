#include <iostream>
#include "sqlparser.hpp"
#include "schema.hpp"

std::string head(const std::string& s) {
    size_t pos = s.find(' ');  // TODO: Include all whitespaces

    if (pos != std::string::npos)
        return s.substr(0, pos);

    return "";
}

std::string tail(const std::string& s) {
    size_t pos = s.find(' ');  // TODO: Include all whitespaces

    if (pos != std::string::npos)
        return s.substr(pos + 1);

    return "";
}

/* TODO: Return an integer based on success / failure */
Schema parse(const std::string& query) {
    if (head(query) == "CREATE") {
        /* TODO: CREATE doesn't just create Schemas */
        Schema new_schema(tail(query));
        std::cout << "Schema created.\n";
        return new_schema;

    } else {
        std::cerr << "Couldn't parse query\n";
        return Schema("nul");  /* Failure */
    }
}
