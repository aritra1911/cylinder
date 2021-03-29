#ifndef _FIELD_TYPE_HPP
# define _FIELD_TYPE_HPP

# include <string>

enum FieldType {
    NUMBER,  /* Int, TODO: Include Float */
    VARCHAR,  /* std::string, Don't think(TODO) too much right now */
};

/* AbstractField serves as a base for multiple fields of different types, i.e. a collection of AbstractField* in an
 * array can point to multiple Fields of different types. This is how a database record shall be maintained since we
 * don't know prior to user input, what type of Fields we'll be needing and how many of them. FieldType is helpful in
 * determining what type of Field we'll be casting the AbstractField* to.
 *
 * P.S. I'm new to this world of C++ casts and I don't quite know the difference between them. I've experimented with
 * dynamic_cast and static_cast and static_cast seems to be working fine.
 */

struct AbstractField {
    FieldType type;
    std::string name;

    AbstractField(const FieldType&, const std::string&);
    virtual ~AbstractField() = 0;
};

template<class T>
struct Field : AbstractField {
    T value;

    Field(const FieldType&, const std::string&);

    Field(const FieldType&, const std::string&, const T&);
};

# include "field_type.tpp"

#endif
