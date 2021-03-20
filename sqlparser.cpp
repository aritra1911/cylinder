#include <iostream>
#include "sqlparser.hpp"
#include "schema.hpp"

std::string head(const std::string& s) {
    size_t pos = s.find(' ');  // TODO: Include all whitespaces

    if (pos != std::string::npos)
        return s.substr(0, pos);

    /* if there are no spaces, then `s' is a single word and hence it's its own head */
    return s;
}

std::string tail(const std::string& s) {
    size_t pos = s.find(' ');  // TODO: Include all whitespaces

    if (pos != std::string::npos)
        return s.substr(pos + 1);

    /* if there are no spaces, `s' is a single word and nothing follows it */
    return "";
}

/* TODO: Return an integer based on success / failure */
Schema parse(const std::string& sql_query) {
    std::string query = sql_query;  // Create a copy so we don't modify the original one

    if (head(query) == "CREATE") {
        query = tail(query);
        if (head(query) == "SCHEMA") {
            Schema new_schema(tail(query));
            std::cout << "Schema created.\n";
            return new_schema;
        } else {
            std::cerr << "What's " << head(query) << "? - rest of the line ignored!\n";
            return Schema("nul");  /* Failure */
        }
    } else {
        std::cerr << "Couldn't parse query\n";
        return Schema("nul");  /* Failure */
    }
}
