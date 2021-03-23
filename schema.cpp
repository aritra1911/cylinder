#include <iostream>
#include <cstdio>
#include <cerrno>
#include <cstring>
#include "schema.hpp"

Schema::Schema(const std::string& name) : name(name) { }

std::string Schema::get_name(void) {
    return this->name;
}

int Schema::create(void) {
    /* Creates file for the schema (this->name) */

    /* If schema has an open file, close it */
    if (file.is_open())
        file.close();

    return this->create(this->name);
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

int Schema::drop(void) {
    /* Deletes the file for the schema (this->name) */

    /* If schema has open file, close it */
    if (file.is_open())
        file.close();

    return this->drop(this->name);

    /* if object is pointed, it's a good idea to delete that pointer now, thereby calling the destructor. Also a
     * pointer is easier to check if the Schema is open or not. A null pointer signifies that it's not. */
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
    std::cout << "Schema destructor called\n";
    if (file.is_open()) {
        std::cout << "File closed\n";
        file.close();
    }
}
