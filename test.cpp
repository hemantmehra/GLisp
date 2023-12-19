#include <Interpreter/Assertion.h>
#include <Interpreter/Scaler.h>
#include <Interpreter/Symbol.h>
#include <Interpreter/Cons.h>
#include <Interpreter/Environment.h>
#include <Interpreter/Interpreter.h>

#define OBJECT_PTR std::shared_ptr<LISP::Object>
#define OBJECT_PTR_CAST(x) std::static_pointer_cast<LISP::Object>(x)
#define MAKE_SCALER(x) std::make_shared<LISP::Scaler>(x)
#define MAKE_SYMBOL(x) std::make_shared<LISP::Symbol>(x)
#define MAKE_CONS1(x) std::make_shared<LISP::Cons>(x)
#define MAKE_CONS2(x, y) std::make_shared<LISP::Cons>(x, y)

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

void test_interpreter()
{
    LISP::Interpreter interpreter;
    std::shared_ptr<LISP::Environment> env = std::make_shared<LISP::Environment>();
    OBJECT_PTR s1 = OBJECT_PTR_CAST(MAKE_SCALER(42));

    OBJECT_PTR s2 = interpreter.eval(s1, env);

    TEST(s1->is_scaler());
    TEST(s2->is_scaler());
    TEST(s2->to_string() == "42");
}

int main()
{
    test_scaler();
    test_symbol();
    test_cons();
    test_cons2();
    test_environment();
    test_interpreter();
    return 0;
}
