#include <cassert>
#include <iostream>
#include <string>
#include <Environment.h>
#include <Object.h>
#include <GObject.h>
#include <eval_apply.h>

#define GObj LISP::GObject

std::string LISP::Object::to_string()
{
    return "[OBJECT]";
}

int main()
{
    LISP::Interpreter interpreter;
    LISP::Environment env;
    
    GObj ob1(42), ob2(17);
    
    std::string s("add"), s2("mul");
    GObj sym_add(&s);
    GObj sym_mul(&s2);

    GObj ob3(&ob1, &ob2);
    GObj ob4(GObj::Primitive_Proc::ADD);
    GObj op_mul(GObj::Primitive_Proc::MUL);

    env.set(&sym_add, &ob4);
    env.set(&sym_mul, &op_mul);
    GObj ob5(&sym_mul, &ob3);
    assert(ob5.is_cons());
    GObj* result = interpreter.eval(&ob5, &env);

    std::cout << result->as_integer() << std::endl;
    
    return 0;
}

