#ifndef _SQLPARSER_HPP
# define _SQLPARSER_HPP

# include "schema.hpp"

/* After splitting the given string using the first encountered whitespace as a delimeter, the head() and tail()
 * functions do as their name implies */
std::string head(const std::string&);
std::string tail(const std::string&);

Schema parse(const std::string&);

#endif  /* _SQLPARSER_HPP */
