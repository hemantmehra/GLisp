#include <cassert>
#include <iostream>
#include <string>
#include <Environment.h>
#include <Object.h>
#include <GObject.h>
#include <eval_apply.h>

#define INTEGER LISP::Integer
#define CONS LISP::Cons

std::string LISP::Object::to_string()
{
    return "[OBJECT]";
}

int main()
{
    LISP::Interpreter interpreter;
    LISP::GObject ob1(42), ob2(17);
    LISP::Environment env;
    env.set("a1", &ob1);

    LISP::GObject ob3(&ob1, &ob2);
    LISP::GObject ob4(LISP::GObject::Primitive_Proc::ADD_OP);

    LISP::GObject ob5(&ob4, &ob3);
    assert(ob5.is_cons());
    LISP::GObject* result = interpreter.eval(&ob5, &env);

    std::cout << result->as_integer() << std::endl;
    
    return 0;
}

