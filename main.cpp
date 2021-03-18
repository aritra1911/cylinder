#include <iostream>
#include "schema.hpp"
#include "sqlparser.hpp"

const std::string PROMPT = "SQL> ";

int main(void) {
    std::string query;

    std::cout << PROMPT;
    std::getline(std::cin, query);

    do {
        Schema temp_schema = parse(query);

        std::cout << "Schema Name : \"" << temp_schema.get_name() << "\"\n";

        std::cout << PROMPT;
        std::getline(std::cin, query);

    } while (query != "EXIT" && query != "QUIT");

    return EXIT_SUCCESS;
}
