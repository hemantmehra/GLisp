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
    LISP::Object_Type obj_type = LISP::Object_Type::T_Float;
    LISP::Integer int_a(42), int_b(10);
    LISP::Cons cons_a(int_a, int_b);
    
    std::cout << "LISP Interpreter" << std::endl;
    assert(int_a.get_type() == LISP::T_Integer);
    assert(int_a.to_val() == 42);

    LISP::Object* o1 = cons_a.get_car();
    LISP::Integer* i1 = (LISP::Integer*) o1;
    std::cout << cons_a.to_string() << std::endl;
    std::cout << i1->to_val() << std::endl;
    return 0;
}

