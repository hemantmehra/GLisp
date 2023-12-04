#ifndef OBJECT_H
#define OBJECT_H

#include <string>

namespace LISP {
    enum Object_Type
    {
        T_Integer,
        T_FLOAT,
        T_NIL
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

    private:
        int m_val;
    };

    class Cons: public Object
    {
    public:
        Cons(const Object*, const Object*);
        Object_Type get_type();
        std::string to_string();
        Object* get_car();
        Object* get_cdr();

    private:
        Object* m_car;
        Object* m_cdr;
    };
}

#endif

