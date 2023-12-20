#ifndef OBJECT_H
#define OBJECT_H

#include <string>

namespace LISP {
    class Object
    {
    public:
        virtual ~Object() = default;
        virtual bool is_nil() const { return true; }
        virtual bool is_scaler() const { return false; }
        virtual bool is_symbol() const { return false; }
        virtual bool is_cons() const { return false; }
        virtual bool is_primitive_procedure() const {return false; }

        virtual std::string to_string() = 0;
    };
}

#endif
