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

    file.open( SCHEMA_FILE(this->name), std::ios::in | std::ios::out | std::ios::binary );//| std::ios::app);
    //file.open( SCHEMA_FILE(this->name), std::ios::in | std::ios::out | std::ios::binary | std::ios::trunc );//| std::ios::app);
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

void Schema::create_table(const std::string& table_name, AbstractField** fields, const size_t& num_fields) {
    /* Now we have to serialize the table header in the file. It should be something like this:
     *
     * Table_name\n
     * <DATA_TYPE><Field_name><DATA_TYPE><Field_name> ...num_field times... <DATA_TYPE><Field_name>\n
     * ...Records follow here...\n
     * \n
     * Table_name\n
     * ...same as above...
     */

    /* Write the table name on the first line */
    file << table_name << std::endl;

    /* Then print slowly i.e. one by one, the field details i.e. field types and field names */
    for ( size_t i = 0; i < num_fields; i++ ) {
        file.write( reinterpret_cast< char* >( &fields[i]->type ), 1 );
        file << fields[i]->name << ' ';
    }

    /* Add an empty line which will serve as tables separatator */
    file << std::endl;
}

void Schema::describe( const std::string& table_name ) {
    /* TODO: Needs to be implemented actually under a Table class */

    /* Get to begining 'cause that's where table header is */
    file.seekg(0, std::ios::beg);

    /* The first line contains the table name */
    std::string name;
    file >> name;

    /* TODO: Check if this is the table the user wants to be described, i.e. check if ( table_name == name )
     *       Currently, we are testing only 1 table, so it's okay to ignore the `table_name' argument. */

    std::cout << table_name << std::endl;
    file.seekg(1, std::ios::cur);  /* Skip reading the newline character */

    /* The second line contains the field details. It goes something like this:
     * <DATA_TYPE><Field_name> <DATA_TYPE><Field_name> ...num_field times... <DATA_TYPE><Field_name> \n
     */

    FieldType type = NUMBER;

    char ch;
    while ( !file.eof() ) {
        /* Read the datatype, followed by the name of the field */
        file.read( reinterpret_cast< char* >( &type ), 1 );
        file >> name;

        /* Show them (nicely) TODO: Be nicer */
        std::cout << name << '\t' << ( type ? "VARCHAR" : "NUMBER" ) << std::endl;

        file.seekg( 1, std::ios::cur );  /* Skip reading the space character */

        /* Is this the end of the field details of this table? */
        file.get(ch);
        if ( ch == '\n' ) break;  /* If so, get out of here */
        file.putback( ch );  /* If not, put things back into place and continue */
    }
}

Schema::~Schema(void) {
    if (file.is_open())
        file.close();
}
