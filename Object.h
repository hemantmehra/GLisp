#ifndef OBJECT_H
#define OBJECT_H

#include <string>

namespace LISP {
    enum Object_Type
    {
        T_Integer,
        T_Float,
        T_Cons,
        T_NIL
    };

    class Object
    {
    public:
        virtual std::string to_string();
        virtual Object_Type get_type() const = 0;
    };

    class Integer: public Object
    {
    public:
        Integer(const int i);
        Object_Type get_type() const;
        std::string to_string();
        int to_val();

    private:
        int m_val;
    };

    class Cons: public Object
    {
    public:
        Cons(Object&, Object&);
        Object_Type get_type() const;
        std::string to_string();
        Object* get_car();
        Object* get_cdr();

    private:
        Object* m_car;
        Object* m_cdr;
    };
}

#endif

