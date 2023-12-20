#include <iostream>
#include <Interpreter/Assertion.h>
#include <Interpreter/Scaler.h>
#include <Interpreter/Symbol.h>
#include <Interpreter/Cons.h>
#include <Interpreter/Environment.h>
#include <Interpreter/Interpreter.h>
#include <Interpreter/PrimitiveProcedure.h>
#include <Interpreter/Tokenizer.h>

#define OBJECT_PTR std::shared_ptr<LISP::Object>
#define OBJECT_PTR_CAST(x) std::static_pointer_cast<LISP::Object>(x)
#define MAKE_SCALER(x) std::make_shared<LISP::Scaler>(x)
#define MAKE_SYMBOL(x) std::make_shared<LISP::Symbol>(x)
#define MAKE_CONS1(x) std::make_shared<LISP::Cons>(x)
#define MAKE_CONS2(x, y) std::make_shared<LISP::Cons>(x, y)
#define MAKE_PRIMITVE_PROCEDURE(x) std::make_shared<LISP::PrimitiveProcedure>(x)

void test_scaler()
{
    LISP::Scaler s1;
    TEST(s1.type() == LISP::Scaler::Type::Nil);
    TEST(s1.is_scaler());

    LISP::Scaler s2(42);
    TEST(s2.is_scaler());
    TEST(s2.type() == LISP::Scaler::Type::Integer);
    TEST(s2.as_integer() == 42);
    TEST(s2.to_string() == "42");
}

void test_symbol()
{
    LISP::Symbol s1("add");
    TEST(s1.is_symbol());
    TEST(s1.name() == "add");
}

void test_cons()
{
    OBJECT_PTR s1 = OBJECT_PTR_CAST(MAKE_SCALER(42));
    OBJECT_PTR s2 = OBJECT_PTR_CAST(MAKE_SCALER(33));

    LISP::Cons c1(s1);
    TEST(c1.is_cons());
    TEST(c1.to_string() == "(42, nil)");

    LISP::Cons c2(s1, s2);
    TEST(c2.to_string() == "(42, 33)");
}

void test_cons2()
{
    OBJECT_PTR s1 = OBJECT_PTR_CAST(MAKE_SYMBOL("add"));
    OBJECT_PTR s2 = OBJECT_PTR_CAST(MAKE_SCALER(42));
    OBJECT_PTR s3 = OBJECT_PTR_CAST(MAKE_SCALER(33));

    OBJECT_PTR c3 = OBJECT_PTR_CAST(MAKE_CONS1(s3));
    OBJECT_PTR c2 = OBJECT_PTR_CAST(MAKE_CONS2(s2, c3));
    OBJECT_PTR c1 = OBJECT_PTR_CAST(MAKE_CONS2(s1, c2));

    TEST(c1->to_string() == "(add, (42, (33, nil)))");
}

void test_environment()
{
    LISP::Environment env;
    
    OBJECT_PTR s1 = OBJECT_PTR_CAST(MAKE_SYMBOL("add"));
    OBJECT_PTR s2 = OBJECT_PTR_CAST(MAKE_SCALER(42));

    env.set(s1, s2);
    CHECK(env.find(s1));
    CHECK(env.get(s1)->to_string() == "42");
}

void test_interpreter_eval_scaler()
{
    LISP::Interpreter interpreter;
    std::shared_ptr<LISP::Environment> env = std::make_shared<LISP::Environment>();
    OBJECT_PTR s1 = OBJECT_PTR_CAST(MAKE_SCALER(42));

    OBJECT_PTR s2 = interpreter.eval(s1, env);

    TEST(s1->is_scaler());
    TEST(s2->is_scaler());
    TEST(s2->to_string() == "42");
}

void test_interpreter_eval_symbol()
{
    LISP::Interpreter interpreter;
    std::shared_ptr<LISP::Environment> env = std::make_shared<LISP::Environment>();
    OBJECT_PTR s1 = OBJECT_PTR_CAST(MAKE_SYMBOL("abc"));
    OBJECT_PTR s2 = OBJECT_PTR_CAST(MAKE_SCALER(42));

    env->set(s1, s2);

    OBJECT_PTR s3 = interpreter.eval(s1, env);

    TEST(s3->is_scaler());
    TEST(s3->to_string() == "42");
}

void test_interpreter_add()
{
    LISP::Interpreter interpreter;
    std::shared_ptr<LISP::Environment> env = std::make_shared<LISP::Environment>();
    OBJECT_PTR s_add = OBJECT_PTR_CAST(MAKE_SYMBOL("add"));
    OBJECT_PTR p_add = OBJECT_PTR_CAST(MAKE_PRIMITVE_PROCEDURE(LISP::PrimitiveProcedure::Type::Add));

    env->set(s_add, p_add);

    OBJECT_PTR s2 = OBJECT_PTR_CAST(MAKE_SCALER(42));
    OBJECT_PTR s3 = OBJECT_PTR_CAST(MAKE_SCALER(33));

    OBJECT_PTR c3 = OBJECT_PTR_CAST(MAKE_CONS1(s3));
    OBJECT_PTR c2 = OBJECT_PTR_CAST(MAKE_CONS2(s2, c3));
    OBJECT_PTR c1 = OBJECT_PTR_CAST(MAKE_CONS2(s_add, c2));
    
    OBJECT_PTR res = interpreter.eval(c1, env);

    TEST(res->is_scaler());
    TEST(res->to_string() == "75");
}

void test_interpreter_mul()
{
    LISP::Interpreter interpreter;
    std::shared_ptr<LISP::Environment> env = std::make_shared<LISP::Environment>();
    OBJECT_PTR s_add = OBJECT_PTR_CAST(MAKE_SYMBOL("mul"));
    OBJECT_PTR p_add = OBJECT_PTR_CAST(MAKE_PRIMITVE_PROCEDURE(LISP::PrimitiveProcedure::Type::Mul));

    env->set(s_add, p_add);

    OBJECT_PTR s2 = OBJECT_PTR_CAST(MAKE_SCALER(13));
    OBJECT_PTR s3 = OBJECT_PTR_CAST(MAKE_SCALER(41));

    OBJECT_PTR c3 = OBJECT_PTR_CAST(MAKE_CONS1(s3));
    OBJECT_PTR c2 = OBJECT_PTR_CAST(MAKE_CONS2(s2, c3));
    OBJECT_PTR c1 = OBJECT_PTR_CAST(MAKE_CONS2(s_add, c2));
    
    OBJECT_PTR res = interpreter.eval(c1, env);

    TEST(res->is_scaler());
    TEST(res->to_string() == "533");
    TEST(res->to_string() != "54");
}

void test_tokenizer()
{
    LISP::Tokenizer tokenizer;
    TEST(tokenizer.is_number("4345656"));

    std::string code = "(add 23 67)";
    std::vector<std::string> words = tokenizer.split_to_words(code);
    TEST(words.size() == 5);

    std::vector<LISP::Token> tokens = tokenizer.tokenize(code);
    TEST(tokens.size() == 5);

    // for(auto i: words) {
    //     std::cout << '[' << i << ']' << ' ';
    // }
    // std::cout << std::endl;
}

int main()
{
    test_scaler();
    test_symbol();
    test_cons();
    test_cons2();
    test_environment();
    test_interpreter_eval_scaler();
    test_interpreter_eval_symbol();
    test_interpreter_add();
    test_interpreter_mul();
    test_tokenizer();
    return 0;
}
