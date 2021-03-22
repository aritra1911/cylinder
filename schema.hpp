#ifndef _SCHEMA_HPP
# define _SCHEMA_HPP

# include <fstream>

# define DATABASE_DIR "db/"

class Schema {
    std::string name;
    std::fstream file;

    public:
    Schema(const std::string&);
    std::string get_name(void);
    int create(void);
    ~Schema(void);
};

#endif  /* _SCHEMA_HPP */
