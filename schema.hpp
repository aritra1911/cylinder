#ifndef _SCHEMA_HPP
# define _SCHEMA_HPP

class Schema {
    std::string name;

    public:
    Schema(const std::string&);
    std::string get_name(void);
};

#endif  /* _SCHEMA_HPP */
