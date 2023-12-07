#ifndef GOBJECT_H
#define GOBJECT_H

#include <cassert>
#include <string>

namespace LISP {    
    class GObject
    {
    public:
        enum class Type
        {
            Integer,
            Float,
            NIL,
            String,
            Cons,
            Symbol,
            Boolean
        };

        bool is_integer() const { return m_type == Type::Integer; }
        bool is_float() const { return m_type == Type::Float; }
        bool is_nil() const { return m_type == Type::NIL; }
        bool is_string() const { return m_type == Type::String; }
        bool is_cons() const { return m_type == Type::Cons; }
        bool is_symbol() const { return m_type == Type::Symbol; }
        bool is_boolean() const { return m_type == Type::Boolean; }
        
        GObject(int32_t i) : m_type(Type::Integer)
        {
            m_value.as_integer = i;
        }

        GObject(GObject* v_car, GObject* v_cdr) : m_type(Type::Cons)
        {
            m_value.as_cons[0] = v_car;
            m_value.as_cons[1] = v_cdr;
        }
        
        Type type() const { return m_type; }

        int32_t as_integer() const
        {
            assert(type() == Type::Integer);
            return m_value.as_integer;
        }

        GObject* as_cons_car() const
        {
            assert(type() == Type::Cons);
            return m_value.as_cons[0];
        }

        GObject* as_cons_cdr() const
        {
            assert(type() == Type::Cons);
            return m_value.as_cons[1];
        }

    private:
        Type m_type{Type::NIL};

        union
        {
            int32_t as_integer;
            double as_float;
            std::string* as_string;
            GObject* as_cons[2];
            std::string* as_symbol;
            bool as_bool;
        } m_value;
    };
}

#endif

