#ifndef SCALER_H
#define SCALER_H

#include <string>
#include <Interpreter/Object.h>

namespace LISP {
    class Scaler : Object
    {
    public:
        enum class Type
        {
            Integer,
            Float,
            Boolean,
            Char,
            Nil
        };

        Type type() const;
        int as_integer() const;
        float as_float() const;
        bool as_boolean() const;
        char as_char() const;

        Scaler();
        Scaler(int);
        Scaler(float);
        Scaler(bool);
        Scaler(char);

        std::string to_string() override;

    private:
        Type m_type;

        union {
            int as_integer;
            float as_float;
            bool as_boolean;
            char as_char;
        } m_data;
    };
}

#endif