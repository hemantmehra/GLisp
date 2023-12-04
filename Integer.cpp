#include <cassert>
#include <Object.h>

namespace LISP {
    Integer::Integer(const int i) : m_val(i) {}

    std::string Integer::to_string()
    {
        return "[INTEGER] " + std::to_string(m_val);
    }

    Object_Type Integer::get_type()
    {
        return T_Integer;
    }

    int Integer::to_val()
    {
        return m_val;
    }
}

