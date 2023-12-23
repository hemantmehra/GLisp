#include <iostream>
#include <fstream>
#include <GLisp/Object.h>
#include <GLisp/Compiler.h>
#include <GLisp/PrimitiveProcedure.h>
#include <GLisp/Tokenizer.h>
#include <GLisp/Parser.h>

#define OBJECT_PTR std::shared_ptr<LISP::Object>
#define OBJECT_PTR_CAST(x) std::static_pointer_cast<LISP::Object>(x)
#define MAKE_PRIMITVE_PROCEDURE(x) std::make_shared<LISP::PrimitiveProcedure>(x)

int main()
{
    LISP::Compiler compiler;
    std::shared_ptr<LISP::Environment> env = std::make_shared<LISP::Environment>();
    OBJECT_PTR p_add = OBJECT_PTR_CAST(MAKE_PRIMITVE_PROCEDURE(LISP::PrimitiveProcedure::Type::Add));
    OBJECT_PTR p_if = OBJECT_PTR_CAST(MAKE_PRIMITVE_PROCEDURE(LISP::PrimitiveProcedure::Type::If));
    OBJECT_PTR p_else = OBJECT_PTR_CAST(MAKE_PRIMITVE_PROCEDURE(LISP::PrimitiveProcedure::Type::Else));
    OBJECT_PTR p_endif = OBJECT_PTR_CAST(MAKE_PRIMITVE_PROCEDURE(LISP::PrimitiveProcedure::Type::EndIf));

    env->set_using_string("add", p_add);
    env->set_using_string("if", p_if);

    LISP::Tokenizer tokenizer;
    LISP::Parser parser;

    std::string code = "(if 1 42 33)";
    std::vector<LISP::Token> tokens = tokenizer.tokenize(code);

    std::shared_ptr<LISP::Object> obj = parser.parse(tokens);
    std::string out_code = compiler.compile(obj, env);

    std::ofstream out_asm("out.asm");
    out_asm << out_code;
    out_asm.close();

    return 0;
}
