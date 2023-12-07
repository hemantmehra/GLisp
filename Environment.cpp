#include <string>
#include <Environment.h>

namespace LISP {
    GObject* Environment::get(const std::string k)
    {
        return m_env.find(k)->second;
    }

    void Environment::set(const std::string k, GObject* v)
    {
        m_env[k] = v;
    }

    bool Environment::find(const std::string k)
    {
        return m_env.find(k) != m_env.end();
    }
}

