#include <string>
#include <Environment.h>

namespace LISP {
    Object* Environment::get(const std::string k)
    {
        return m_env.find(k)->second;
    }

    void Environment::set(const std::string k, Object* v)
    {
        m_env[k] = v;
    }

    bool Environment::find(const std::string k)
    {
        return m_env.find(k) != m_env.end();
    }
}

