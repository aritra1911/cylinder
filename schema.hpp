#ifndef _SCHEMA_HPP
# define _SCHEMA_HPP

# include <fstream>

# define DATABASE_DIR "db/"
# define SCHEMA_FILE(x) (DATABASE_DIR + x)

class Schema {
    std::string name;
    std::fstream file;

    public:
    Schema(const std::string&);
    std::string get_name(void);
    int create(void);
    int drop(void);
    static int drop(const std::string&);
    ~Schema(void);
};

#endif  /* _SCHEMA_HPP */
