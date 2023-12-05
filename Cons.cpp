#include <cassert>
#include <Object.h>

namespace LISP {
    Cons::Cons(Object& a, Object& b)
        : m_car(&a), m_cdr(&b) {}

    std::string Cons::to_string()
    {
        return "[Cons] " + m_car->to_string() + " " + m_cdr->to_string();
    }

    Object_Type Cons::get_type() const
    {
        return Object_Type::T_Cons;
    }

    Object* Cons::get_car()
    {
        return m_car;
    }
}

