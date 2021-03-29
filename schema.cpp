#include <iostream>
#include <cstdio>
#include <cerrno>
#include <cstring>
#include "schema.hpp"

Schema::Schema(const std::string& name) : name(name) {
    /* Instantiating a Schema, selects it. */

    /* Check if it exists */
    std::ifstream f(SCHEMA_FILE(this->name));
    if (!f.is_open())
        throw DoesntExistException();

    f.close();  /* Close if opened */

    file.open(SCHEMA_FILE(this->name), std::ios::in | std::ios::out | std::ios::app);
}

std::string Schema::get_name(void) {
    return this->name;
}

int Schema::create(const std::string& name) {
    /* Note: This function only creates the schema, but doesn't load it. */
    std::fstream f;

    /* Check if schema already exists */
    f.open(SCHEMA_FILE(name), std::ios::in);
    if (f.is_open()) {
        /* We were able to open the schema, therefore it exists. So return error. */
        std::cerr << "Schema already exists!\n";
        f.close();
        return -1;
    }

    /* Now that we know for sure that it doesn't exist, so create it */
    f.open(SCHEMA_FILE(name), std::ios::out);
    if (!f.is_open()) {
        /* Something went wrong, maybe file create permissions? */
        std::cerr << "Couldn't create schema\n";
        return -1;
    }

    /* Things went as intended. Now close the open output file and return. */
    f.close();
    return 0;
}

int Schema::drop(const std::string& name) {
    /* Is able to delete file for any schema given a name */

    /* Try to open schema file and if we're not successful, then it doesn't exist. */
    std::ifstream f(SCHEMA_FILE(name));
    if (!f.is_open()) {
        std::cerr << "Schema doesn't exist\n";
        return -1;
    }
    f.close();  /* It opened, so close it */

    errno = 0;  /* Make sure `errno' is reset */
    if (std::remove(SCHEMA_FILE(name).c_str()) == -1) {
        std::cerr << SCHEMA_FILE(name) << ": " << std::strerror(errno);
        errno = 0;
        return -1;
    }

    return 0;
}

Schema::~Schema(void) {
    if (file.is_open())
        file.close();
}
