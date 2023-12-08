#include <cassert>
#include <string>
#include <Environment.h>

namespace LISP {
    GObject* Environment::get(GObject* k)
    {
        assert(k->is_symbol());
        return m_env.find(k)->second;
    }

    void Environment::set(GObject* k, GObject* v)
    {
        assert(k->is_symbol());
        m_env[k] = v;
    }

    bool Environment::find(GObject* k)
    {
        assert(k->is_symbol());
        return m_env.find(k) != m_env.end();
    }
}

