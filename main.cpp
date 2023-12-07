#include <cassert>
#include <iostream>
#include <string>
#include <Environment.h>
#include <Object.h>
#include <GObject.h>

#define INTEGER LISP::Integer
#define CONS LISP::Cons

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

    LISP::Environment env;
    env.set("a1", &cons_a);

    std::cout << "Environment" << std::endl;
    std::cout << env.get("a1")->to_string() << std::endl;

    LISP::GObject ob1(42);
    std::cout << ob1.is_integer() << std::endl;
    std::cout << ob1.is_nil() << std::endl;
    std::cout << ob1.as_integer() << std::endl;
    return 0;
}

