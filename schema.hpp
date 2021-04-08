#ifndef _SCHEMA_HPP
# define _SCHEMA_HPP

# include <fstream>
# include "field_type.hpp"

# define DATABASE_DIR "db/"  /* TODO: Create if doesn't exist */
# define SCHEMA_FILE(x) (DATABASE_DIR + x)

class Schema {
    std::string name;
    std::fstream file;

    public:
    /* Exceptions */
    class DoesntExistException { };

    Schema(const std::string&);
    std::string get_name(void);
    static int create(const std::string&);
    static void drop( const std::string& );
    void create_table(const std::string&, AbstractField**, const size_t&);
    void describe( const std::string& );
    ~Schema(void);
};

#endif  /* _SCHEMA_HPP */
