#include <iostream>
#include <string>
#include <l_object.h>

std::string LISP::Object::to_string()
{
    return "[OBJECT]";
}

LISP::Integer::Integer(const int i) : m_val(i) {}

std::string LISP::Integer::to_string()
{
    return "[INTEGER] " + std::to_string(m_val);
}

LISP::Object_Type LISP::Integer::get_type()
{
    return LISP::T_Integer;
}

int LISP::Integer::to_val()
{
    return m_val;
}

LISP::Integer LISP::Integer::add(const LISP::Integer a)
{
    return LISP::Integer(m_val + a.m_val);
}

int main()
{
    LISP::Object_Type obj_type = LISP::T_Integer;
    LISP::Integer int_a(42), int_b(10);
    
    std::cout << "LISP Interpreter" << std::endl;
    std::cout << int_a.to_string() << std::endl;
    std::cout << int_a.add(int_b).to_string() << std::endl;
    return 0;
}

