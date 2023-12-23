#include <GLisp/PrimitiveProcedure.h>

namespace LISP {
    PrimitiveProcedure::PrimitiveProcedure(PrimitiveProcedure::Type type)
        : m_type(type) {}

    PrimitiveProcedure::Type PrimitiveProcedure::type() { return m_type; }

    std::string PrimitiveProcedure::to_string()
    {
        return "[Proc]";
    }
}
