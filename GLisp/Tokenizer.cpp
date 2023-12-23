#include <GLisp/Tokenizer.h>

namespace LISP {
    Token::Token(Type type) : m_type(type) {}

    Token::Token(Type type, int x) : m_type(type), m_scaler_value(x) {}

    Token::Token(Type type, std::string x) : m_type(type), m_string_value(x) {}

    int Token::as_scaler_value() { return m_scaler_value; }

    std::string Token::as_symbol_value() { return m_string_value; }

    std::string Token::to_string()
    {
        switch (m_type)
        {
        case Type::LP:
            return "[Token] LP";
            break;
        case Type::RP:
            return "[Token] RP";
            break;
        case Type::Symbol:
            return "[Token] " + as_symbol_value();
            break;
        case Type::Scaler:
            return "[Token] " + std::to_string(as_scaler_value());
            break;
        default:
            break;
        }
        return "";
    }

    std::vector<std::string> Tokenizer::split_to_words(std::string code)
    {
        std::vector<std::string> words;
        std::string current_word = "";

        auto it = code.begin();
        while (it != code.end())
        {
            if (std::isspace(*it) && current_word.length() != 0) {
                words.push_back(current_word);
                current_word = "";
            }

            else if (*it == '(') {
                if (current_word.length() > 0) words.push_back(current_word);
                words.push_back("(");
                current_word = "";
            }

            else if (*it == ')') {
                if (current_word.length() > 0) words.push_back(current_word);
                words.push_back(")");
                current_word = "";
            }

            else if (std::isspace(*it)) {}

            else {
                current_word += *it;
            }

            it++;
        }

        if (current_word.length() > 0)
            words.push_back(current_word);

        return words;
    }

    bool Tokenizer::is_number(const std::string s)
    {
        std::string::const_iterator it = s.begin();
        while (it != s.end() && std::isdigit(*it)) ++it;
        return !s.empty() && it == s.end();
    }

    std::vector<Token> Tokenizer::tokenize(std::string code)
    {
        std::vector<Token> tokens;
        std::vector<std::string> words = split_to_words(code);

        for(auto it: words) {
            if (it == "(") {
                tokens.push_back(Token(Token::Type::LP));
            }

            else if (it == ")") {
                tokens.push_back(Token(Token::Type::RP));
            }

            else if (is_number(it)) {
                tokens.push_back(Token(Token::Type::Scaler, stoi(it)));
            }

            else {
                tokens.push_back(Token(Token::Type::Symbol, it));
            }
        }

        return tokens;
    }
}
