#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <cassert>
#include <string>
#include <vector>

namespace LISP {
    class Token
    {
    public:
        enum class Type
        {
            Open,
            Close,
            Symbol,
            String,
            Integer
        };

        bool is_open() const { return m_type == Type::Open; }
        bool is_close() const { return m_type == Type::Close; }
        bool is_integer()  const { return m_type == Type::Integer; }
        bool is_symbol() const { return m_type == Type::Symbol; }

        std::string to_string();
        
        int32_t as_integer() const
        {
            return m_value.as_integer;
        }

        std::string* as_symbol() const
        {
            return m_value.as_symbol;
        }

        Token(Type type) : m_type(type)
        {
            assert(type == Type::Open || type == Type::Close);
        }

        Token(Type type, int32_t a) : m_type(type)
        {
            assert(type == Type::Integer);
            m_value.as_integer = a;
        }

        Token(Type type, std::string* s) : m_type(type)
        {
            assert(type == Type::Symbol || type == Type::String);
            m_value.as_symbol = s;
            m_value.as_string = s;
        }
    
    private:
        Type m_type;
        
        union {
            std::string* as_symbol;
            std::string* as_string;
            int32_t as_integer;
        } m_value;
    };

    class Tokenizer
    {
    public:
        enum class State
        {
            Begin,
            BeginList,
            Symbol,
            Integer,
            End
        };
        
        void tokenize(std::string);
        std::vector<Token>* get_tokens();
    private:
        std::vector<Token> m_tokens;
        bool is_number(const std::string& s);
    };
}

#endif
