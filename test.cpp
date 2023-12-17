#include <Interpreter/Assertion.h>
#include <Interpreter/Scaler.h>

void test1()
{
    LISP::Scaler s1;
    TEST(s1.type() == LISP::Scaler::Type::Nil);

    LISP::Scaler s2(42);
    TEST(s2.type() == LISP::Scaler::Type::Integer);
    TEST(s2.as_integer() == 42);
    TEST(s2.to_string() == "42");
}

int main()
{
    test1();
    return 0;
}
