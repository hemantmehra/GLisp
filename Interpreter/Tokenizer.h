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
    
    private:
        Type m_type;
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
