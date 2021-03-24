#ifndef _SQLPARSER_HPP
# define _SQLPARSER_HPP

# include <string>
# include <vector>
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

enum DataType {
    NUMBER,  /* Int, TODO: Include Float */
    VARCHAR,  /* std::string, Don't think(TODO) too much right now */
};

struct Column {
    std::string name;
    DataType type;
    /* TODO: Add constraints */
};

struct SQL {
    Clause statement;
    Clause substatement;
    std::string name;
    std::vector<Column> table_columns;

    int parse(const std::string&);
    void execute(Schema*&);
};

/* After splitting the given string using the first encountered whitespace as a delimeter, the head() and tail()
 * functions do as their name implies */
std::string head(const std::string&);
std::string tail(const std::string&);

std::string strip_parenthesis(const std::string&);
std::vector<std::string> split(const std::string&);

#endif  /* _SQLPARSER_HPP */
