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

    /* if there are no spaces, `s' is a single word and hence nothing follows it */
    return "";
}

int SQL::parse(const std::string& _query) {
    std::string query = _query;  // Create a copy so we don't modify the original one

    /* TODO: SQL is case-insensitive */
    if (head(query) == "CREATE") {
        query = tail(query);  // Chop off head, we won't need that anymore!
        this->statement = CREATE;

        if (head(query) == "SCHEMA") {
            this->substatement = SCHEMA;
            this->name = tail(query);
                /* TODO: SQL statements may end with a semi-colon which is not a part of the name itself. */

        //} else if (head(query) == "TABLE") {
        //    /* TODO */
        } else {
            std::cerr << "What's " << head(query) << "? - rest of the line ignored!\n";
            return -1;
        }
    } else if (head(query) == "DROP") {
        query = tail(query);  // Chop off head, we won't need that anymore!
        this->statement = DROP;

        if (head(query) == "SCHEMA") {
            this->substatement = SCHEMA;
            this->name = tail(query);

        } else {
            std::cerr << "What's " << head(query) << "? - rest of the line ignored!\n";
            return -1;
        }
    } else if (head(query) == "SELECT") {
        query = tail(query);  // Chop off head, we won't need that anymore!
        this->statement = SELECT;

        if (head(query) == "SCHEMA") {
            this->substatement = SCHEMA;
            this->name = tail(query);

        } else {
            std::cerr << "What's " << head(query) << "? - rest of the line ignored!\n";
            return -1;
        }
    } else {
        std::cerr << "Couldn't parse query\n";
        return -1;
    }

    return 0;
}

void SQL::execute(Schema*& schema) {  /* TODO: Should `schema' be mutable? */
    switch (statement) {
        case CREATE:
            switch (substatement) {
                case SCHEMA:
                    if (Schema::create(name) == -1)
                        std::cerr << "Couldn't create schema!\n";
                    else
                        std::cout << "Schema created.\n";
                    break;

                case TABLE:
                    /* TODO */
                    break;

                default:
                    /* If the parse() works correctly, and provided no break statements were missed above, this case
                     * should never be reached. */
                    std::cerr << "You shouldn't be seeing this!\n";

            }
            break;

        case DROP:
            switch (substatement) {
                case SCHEMA:
                    if (Schema::drop(name) == -1)
                        std::cerr << "Couldn't drop schema!\n";
                    else
                        std::cout << "Schema dropped!\n";
                    break;

                default:
                    /* If the parse() works correctly, and provided no break statements were missed above, this case
                     * should never be reached. */
                    std::cerr << "You shouldn't be seeing this!\n";
            }
            break;

        case SELECT:
            switch (substatement) {
                case SCHEMA:
                    /* If we've selected another schema that's not pointed by `schema' */
                    if (schema && schema->get_name() != name) {
                        delete schema;
                        schema = nullptr;  /* This should happen automatically after a delete */
                    }

                    if (!schema)
                        schema = new Schema(name);

                    if (schema->select() == -1)
                        std::cerr << "Couldn't select schema!\n";
                    else
                        std::cout << "Schema selected.\n";
                    break;

                default:
                    /* If the parse() works correctly, and provided no break statements were missed above, this case
                     * should never be reached. */
                    std::cerr << "You shouldn't be seeing this!\n";
            }
            break;

        default:
            /* If the parse() works correctly, and provided no break statements were missed above, this case should
             * never be reached. */
            std::cerr << "You shouldn't be seeing this!\n";
    }
}
