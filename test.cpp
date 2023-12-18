#include <Interpreter/Assertion.h>
#include <Interpreter/Scaler.h>
#include <Interpreter/Symbol.h>
#include <Interpreter/Cons.h>

#define OBJECT_CAST(x) std::static_pointer_cast<LISP::Object>(x)
#define MAKE_SCALER(x) std::make_shared<LISP::Scaler>(x)
#define MAKE_SYMBOL(x) std::make_shared<LISP::Symbol>(x)
#define MAKE_CONS1(x) std::make_shared<LISP::Cons>(x)
#define MAKE_CONS2(x, y) std::make_shared<LISP::Cons>(x, y)

void test_scaler()
{
    LISP::Scaler s1;
    TEST(s1.type() == LISP::Scaler::Type::Nil);

    LISP::Scaler s2(42);
    TEST(s2.type() == LISP::Scaler::Type::Integer);
    TEST(s2.as_integer() == 42);
    TEST(s2.to_string() == "42");
}

void test_symbol()
{
    LISP::Symbol s1("add");
    TEST(s1.name() == "add");
}

void test_cons()
{
    std::shared_ptr<LISP::Object> s1 = OBJECT_CAST(MAKE_SCALER(42));
    std::shared_ptr<LISP::Object> s2 = OBJECT_CAST(MAKE_SCALER(33));

    LISP::Cons c1(s1);
    TEST(c1.to_string() == "(42, nil)");

    LISP::Cons c2(s1, s2);
    TEST(c2.to_string() == "(42, 33)");
}

void test_cons2()
{
    std::shared_ptr<LISP::Object> s1 = OBJECT_CAST(MAKE_SYMBOL("add"));
    std::shared_ptr<LISP::Object> s2 = OBJECT_CAST(MAKE_SCALER(42));
    std::shared_ptr<LISP::Object> s3 = OBJECT_CAST(MAKE_SCALER(33));

    std::shared_ptr<LISP::Object> c2 = OBJECT_CAST(MAKE_CONS2(s2, s3));

    LISP::Cons c3(s1, c2);
    TEST(c3.to_string() == "(add, (42, 33))");
}

int main()
{
    test_scaler();
    test_symbol();
    test_cons();
    test_cons2();
    return 0;
}
