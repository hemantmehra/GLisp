#include <GLisp/Symbol.h>

namespace LISP {
    std::string Symbol::name() const
    {
        return m_name;
    }

    std::string Symbol::to_string()
    {
        return m_name;
    }
}
