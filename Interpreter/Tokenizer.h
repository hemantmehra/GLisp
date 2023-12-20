#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <string>
#include <memory>
#include <vector>

namespace LISP {
    class Token
    {
    public:
        enum class Type
        {
            LP,
            RP,
            Symbol,
            Scaler
        };

        Token(Type);
        Token(Type, int);
        Token(Type, std::string);
        int as_scaler_value();
        std::string as_symbol_value();
    
    private:
        Type m_type;
        int m_scaler_value;
        std::string m_string_value;
    };

    class Tokenizer
    {
    public:
        std::vector<Token> tokenize(std::string);
        std::vector<std::string> split_to_words(std::string code);
        bool is_number(const std::string);
    };
}

#endif
