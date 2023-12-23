#include <GLisp/PrimitiveProcedure.h>

namespace LISP {
    PrimitiveProcedure::PrimitiveProcedure(PrimitiveProcedure::Type type)
        : m_type(type) {}
    
    PrimitiveProcedure::PrimitiveProcedure(PrimitiveProcedure::Type type, int data)
        : m_type(type), m_data_1(data) {}
    
    PrimitiveProcedure::PrimitiveProcedure(PrimitiveProcedure::Type type, int data1, int data2)
        : m_type(type), m_data_1(data1), m_data_2(data2) {}

    PrimitiveProcedure::Type PrimitiveProcedure::type() { return m_type; }

    std::string PrimitiveProcedure::to_string()
    {
        return "[Proc]";
    }
}
