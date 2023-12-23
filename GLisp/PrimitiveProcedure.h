#ifndef PRIMITIVE_PROCEDURE_H
#define PRIMITIVE_PROCEDURE_H

#include <string>
#include <memory>
#include <GLisp/Object.h>

namespace LISP {
    class PrimitiveProcedure : public Object
    {
    public:
        enum class Type
        {
            Add,
            Mul,
            If,
            Else,
            EndIf
        };

        PrimitiveProcedure(Type);
        PrimitiveProcedure(Type, int);
        PrimitiveProcedure(Type, int, int);
        Type type();
        virtual bool is_primitive_procedure() const override { return true; }
        std::string to_string() override;

        int data_1() { return m_data_1; }
        int data_2() { return m_data_2; }

    private:
        Type m_type;
        int m_data_1;
        int m_data_2;
    };
}

#endif
