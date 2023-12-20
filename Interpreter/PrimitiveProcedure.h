#ifndef PRIMITIVE_PROCEDURE_H
#define PRIMITIVE_PROCEDURE_H

#include <string>
#include <memory>
#include <Interpreter/Object.h>

namespace LISP {
    class PrimitiveProcedure : public Object
    {
    public:
        enum class Type
        {
            Add,
            Mul
        };

        PrimitiveProcedure(Type);
        Type type();
        virtual bool is_primitive_procedure() const override { return true; }
        std::string to_string() override;

    private:
        Type m_type;
    };
}

#endif
