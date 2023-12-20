#include <Interpreter/Assertion.h>
#include <Interpreter/Environment.h>
#include <Interpreter/Symbol.h>

#define SYMBOL_PTR_CAST(x) std::dynamic_pointer_cast<Symbol>(x)

namespace LISP {
    std::shared_ptr<Object> Environment::get(std::shared_ptr<Object> k)
    {
        CHECK(find(k));
        return m_env.find(SYMBOL_PTR_CAST(k)->name())->second;
    }

    void Environment::set(std::shared_ptr<Object> k, std::shared_ptr<Object> v)
    {
        m_env[SYMBOL_PTR_CAST(k)->name()] = v;
    }

    void Environment::set_using_string(std::string s, std::shared_ptr<Object> v)
    {
        m_env[s] = v;
    }

    bool Environment::find(std::shared_ptr<Object> k)
    {
        return m_env.find(SYMBOL_PTR_CAST(k)->name()) != m_env.end();
    }
}
