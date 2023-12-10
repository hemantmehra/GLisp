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
            Boolean,
            Primitive_Proc
        };

        enum class Primitive_Proc
        {
            ADD,
            MUL
        };
        

        bool is_integer() const { return m_type == Type::Integer; }
        bool is_float() const { return m_type == Type::Float; }
        bool is_nil() const { return m_type == Type::NIL; }
        bool is_string() const { return m_type == Type::String; }
        bool is_cons() const { return m_type == Type::Cons; }
        bool is_symbol() const { return m_type == Type::Symbol; }
        bool is_boolean() const { return m_type == Type::Boolean; }
        bool is_primitive_proc() const { return m_type == Type::Primitive_Proc; }

        bool is_self_eval() const {
            if (m_type == Type::Integer) return true;
            // if (m_type == Type::Primitive_Proc) return true;
            return false;
        }

        GObject() : m_type(Type::NIL) {}

        GObject(int32_t i) : m_type(Type::Integer)
        {
            m_value.as_integer = i;
        }

        GObject(Primitive_Proc p) : m_type(Type::Primitive_Proc)
        {
            m_value.as_primitive_proc = p;
        }

        GObject(GObject* v_car, GObject* v_cdr) : m_type(Type::Cons)
        {
            m_value.as_cons[0] = v_car;
            m_value.as_cons[1] = v_cdr;
        }

        GObject(std::string *sym) : m_type(Type::Symbol)
        {
            m_value.as_symbol = sym;
        }
        
        Type type() const { return m_type; }

        int32_t as_integer() const
        {
            assert(type() == Type::Integer);
            return m_value.as_integer;
        }

        Primitive_Proc as_primitive_proc() const
        {
            assert(type() == Type::Primitive_Proc);
            return m_value.as_primitive_proc;
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

        void set_cons_car(GObject *a)
        {
            assert(type() == Type::Cons);
            m_value.as_cons[0] = a;
        }

        
        void set_cons_cdr(GObject *a)
        {
            assert(type() == Type::Cons);
            m_value.as_cons[1] = a;
        }

        std::string* as_symbol() const
        {
            assert(type() == Type::Symbol);
            return m_value.as_symbol;
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
            Primitive_Proc as_primitive_proc;
        } m_value;
    };
}

#endif

