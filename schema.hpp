#ifndef _SCHEMA_HPP
# define _SCHEMA_HPP

# include <fstream>

# define DATABASE_DIR "db/"  /* TODO: Create if doesn't exist */
# define SCHEMA_FILE(x) (DATABASE_DIR + x)

class Schema {
    std::string name;
    std::fstream file;

    public:
    Schema(const std::string&);
    std::string get_name(void);
    int create(void);  // Create self
    int drop(void);  // Drop self
    static int create(const std::string&);
    static int drop(const std::string&);
    ~Schema(void);
};

#endif  /* _SCHEMA_HPP */
