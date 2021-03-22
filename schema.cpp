#include <iostream>
#include "schema.hpp"

Schema::Schema(const std::string& name) : name(name) { }

std::string Schema::get_name(void) {
    return this->name;
}

int Schema::create(void) {
    /* Note: This function only creates the schema, but doesn't load it. */
    std::fstream f;

    /* Check if schema already exists */
    f.open(DATABASE_DIR + this->name, std::ios::in);
    if (f.is_open()) {
        /* We were able to open the schema, therefore it exists. So return error. */
        std::cerr << "Schema already exists!\n";
        f.close();
        return -1;
    }

    /* Now that we know for sure that it doesn't exist, create it */
    f.open(DATABASE_DIR + this->name, std::ios::out);
    if (!f.is_open()) {
        /* Something went wrong, maybe file create permissions? */
        std::cerr << "Couldn't create schema\n";
        return -1;
    }

    /* Things went as intended. Now close the open output file and return. */
    f.close();
    return 0;
}

Schema::~Schema(void) {
    std::cout << "Schema destructor called\n";
    if (file.is_open()) {
        std::cout << "File closed\n";
        file.close();
    }
}
