#ifndef _SQLPARSER_HPP
# define _SQLPARSER_HPP

# include "schema.hpp"

enum Clause {
    /* A SQL query begins with one of these */
    CREATE,
    DROP,
    ALTER,
    DESCRIBE,
    SELECT,
    INSERT,
    UPDATE,
    DELETE,

    /* These are mentioned somewhere in the middle of a SQL query */
    SCHEMA,
    TABLE,
    SET,
    INTO,
    VALUES,
    FROM,
    WHERE,
};

struct SQL {
    Clause statement;
    Clause substatement;
    std::string name;

    int parse(const std::string&);
    void execute(Schema*&);
};

/* After splitting the given string using the first encountered whitespace as a delimeter, the head() and tail()
 * functions do as their name implies */
std::string head(const std::string&);
std::string tail(const std::string&);

#endif  /* _SQLPARSER_HPP */
