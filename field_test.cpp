#include <iostream>
#include <string>
#include <vector>
#include "field_type.hpp"

int main(void) {
    int n;
    std::cout << "How many fields? ";
    std::cin >> n;

    std::vector<AbstractField*> record;
    std::vector<std::string> field_names;

    std::cout << "\nEnter space separated field names: ";
    for (int i=0; i<n; i++) {
        std::string name;
        std::cin >> name;
        field_names.push_back(name);
    }

    std::cout << "\nNUMBER = 0\nVARCHAR = 1\nEnter space separated field types: ";

    FieldType type;
    for (int i=0; i<n; i++) {
        std::cin >> (int&)type;
        switch (type) {
            case NUMBER:
                record.push_back(new Field<int>(type, field_names[i]));
                break;

            default:
                record.push_back(new Field<std::string>(type, field_names[i]));
        }
    }

    std::cout << "Enter space separated values: ";
    for (int i = 0; i < n; i++) {
        switch (record[i]->type) {
            case NUMBER:
                std::cin >> static_cast<Field<int>*>(record[i])->value;
                break;

            default:
                std::cin >> static_cast<Field<std::string>*>(record[i])->value;
        }
    }

    std::cout << std::endl;

    for (int i=0; i<n; i++) {
        std::cout << record[i]->name << " : ";
        switch (record[i]->type) {
            case NUMBER:
                std::cout << static_cast<Field<int>*>(record[i])->value;
                break;

            default:
                std::cout << static_cast<Field<std::string>*>(record[i])->value;
        }
        std::cout << std::endl;
    }

    for (int i=0; i<n; i++)
        delete record[i];

    record.clear();

    return 0;
}
