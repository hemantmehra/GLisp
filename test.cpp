#include <Interpreter/Assertion.h>
#include <Interpreter/Scaler.h>
#include <Interpreter/Symbol.h>
#include <Interpreter/Cons.h>

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
    std::shared_ptr<LISP::Object> s1 = std::static_pointer_cast<LISP::Object>(std::make_shared<LISP::Scaler>(42));
    std::shared_ptr<LISP::Object> s2 = std::static_pointer_cast<LISP::Object>(std::make_shared<LISP::Scaler>(33));

    LISP::Cons c1(s1);
    TEST(c1.to_string() == "(42, nil)");

    LISP::Cons c2(s1, s2);
    TEST(c2.to_string() == "(42, 33)");
}

int main()
{
    test_scaler();
    test_symbol();
    test_cons();
    return 0;
}
