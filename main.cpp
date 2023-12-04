#include <cassert>
#include <iostream>
#include <string>
#include <Object.h>

std::string LISP::Object::to_string()
{
    return "[OBJECT]";
}

int main()
{
    LISP::Object_Type obj_type = LISP::T_Integer;
    LISP::Integer int_a(42), int_b(10);
    
    std::cout << "LISP Interpreter" << std::endl;
    assert(int_a.get_type() == LISP::T_Integer);
    assert(int_a.to_val() == 42);
    return 0;
}

