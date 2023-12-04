#ifndef OBJECT_H
#define OBJECT_H

#include <string>

namespace LISP {
    enum Object_Type
    {
        T_Integer,
        T_FLOAT
    };

    class Object
    {
    public:
        std::string to_string();
        virtual Object_Type get_type() = 0;
    };

    class Integer: public Object
    {
    public:
        Integer(const int i);
        Object_Type get_type();
        std::string to_string();
        int to_val();
        Integer add(const Integer);

    private:
        int m_val;
    };
}

#endif

