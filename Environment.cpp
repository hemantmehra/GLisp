#include <cassert>
#include <string>
#include <Environment.h>

namespace LISP {
    GObject* Environment::get(GObject* k)
    {
        assert(k->is_symbol());
        assert(find(k));
        return m_env.find(k->as_symbol())->second;
    }

    void Environment::set(GObject* k, GObject* v)
    {
        assert(k->is_symbol());
        m_env[k->as_symbol()] = v;
    }

    bool Environment::find(GObject* k)
    {
        assert(k->is_symbol());
        return m_env.find(k->as_symbol()) != m_env.end();
    }
}

