#include <iostream>
#include "schema.hpp"
#include "sqlparser.hpp"

const std::string PROMPT = "SQL> ";

int main(void) {
    std::string query;
    Schema* schema = nullptr;
    SQL sql;

    while (1) {
        std::cout << PROMPT;
        std::getline(std::cin, query);

        /* EXIT on EOF (aka ^D) */
        if (std::cin.eof()) {
            /* Hitting ^D exits abruptly, so here we print nicely, the cause of exit i.e. EOF along with a newline so it
             * doesn't mess up shell prompts and then gracefully exit */
            std::cout << "EOF\n";
            break;
        }

        if (query == "EXIT" || query == "QUIT")
            break;

        if (sql.parse(query) == -1)
            continue;  /* Bad query */

        /* TODO: This works on a particular schema, but should we mutate a global schema? */
        sql.execute(schema);
    }

    return EXIT_SUCCESS;
}
