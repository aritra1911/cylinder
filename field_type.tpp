/* Context behind creating this file:
   https://stackoverflow.com/questions/495021/why-can-templates-only-be-implemented-in-the-header-file */

template <class T>
Field<T>::Field(const FieldType& type, const std::string& name) : AbstractField(type, name) { }

template <class T>
Field<T>::Field(const FieldType& type, const std::string& name, const T& value) :
    AbstractField(type, name), value(value) { }
