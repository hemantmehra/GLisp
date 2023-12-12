#include <cassert>
#include <iostream>
#include <string>
#include <Environment.h>
#include <Object.h>
#include <GObject.h>
#include <eval_apply.h>
#include <Tokenizer.h>
#include <vector>
#include <Parser.h>

#define GObj LISP::GObject

std::string LISP::Object::to_string()
{
    return "[OBJECT]";
}

int main()
{
    LISP::Interpreter interpreter;
    LISP::Environment env;
    LISP::Parser parser;
    
    GObj ob1(42), ob2(17);
    std::cout << ob1.to_string() << std::endl;
    
    std::string s("add"), s2("mul"), s3("THE_NUMBER");
    GObj sym_add(&s);
    GObj sym_mul(&s2);
    GObj sym_num(&s3);

    GObj ob3(&ob1, new GObj(&ob2, new GObj()));
    GObj ob4(GObj::Primitive_Proc::ADD);
    GObj op_mul(GObj::Primitive_Proc::MUL);

    env.set(&sym_add, &ob4);
    env.set(&sym_mul, &op_mul);
    // env.set(&sym_num, new GObj(42));
    
    GObj ob5(&sym_mul, &ob3);
    assert(ob5.is_cons());

    
    GObj* result = interpreter.eval(&ob5, &env);

    std::cout << result->as_integer() << std::endl;

    LISP::Token t1(LISP::Token::Type::Open);
    LISP::Token t4(LISP::Token::Type::Symbol, &s);
    LISP::Token t2(LISP::Token::Type::Integer, 5);
    LISP::Token t5(LISP::Token::Type::Integer, 6);
    LISP::Token t3(LISP::Token::Type::Close);
    LISP::Token t6(LISP::Token::Type::Symbol, &s3);

    std::vector<LISP::Token> stream;
    stream.push_back(t1);
    stream.push_back(t4);
    stream.push_back(t2);
    stream.push_back(t5);
    // stream.push_back(t6);
    stream.push_back(t3);

    LISP::GObject *out = parser.parse(stream);
    LISP::GObject *result2 = interpreter.eval(out, &env);

    std::cout << result2->as_integer() << std::endl;

    std::cout << out->to_string() << std::endl;
    
    return 0;
}

