#include <iostream>
#include <filesystem>
#include "schema.hpp"
#include "field_type.hpp"

Schema::Schema(const std::string& name) : name(name) {
    /* Instantiating a Schema, selects it. */

    /* Check if it exists */
    std::ifstream f(SCHEMA_FILE(this->name));
    if (!f.is_open())
        throw DoesntExistException();

    f.close();  /* Close if opened */

    file.open(SCHEMA_FILE(this->name), std::ios::in | std::ios::out );//| std::ios::app);
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

void Schema::drop( const std::string& name ) {
    /* Is able to delete file for any schema given a name */

    std::filesystem::path p = SCHEMA_FILE( name );

    if ( !std::filesystem::remove( p ) )
        throw DoesntExistException();
}

void Schema::create_table(const std::string& name, AbstractField** fields, const size_t& num_fields) {
    /* Now we have to serialize the table header in the file. It should be something like this:
     *
     * Table_name\n
     * <DATA_TYPE><Field_name><DATA_TYPE><Field_name> ...num_field times... <DATA_TYPE><Field_name>\n
     * ...Records follow here...\n
     * \n
     * Table_name\n
     * ...same as above...
     */
    file << name << std::endl;
    for (size_t i=0; i<num_fields; i++)
        file << fields[i]->type << fields[i]->name;
    file << std::endl;
}

Schema::~Schema(void) {
    if (file.is_open())
        file.close();
}
